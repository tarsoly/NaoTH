#include "PlainKalmanFilterBallLocator.h"

#include <cmath>

PlainKalmanFilterBallLocator::PlainKalmanFilterBallLocator():
     epsilon(10e-6)
{
    DEBUG_REQUEST_REGISTER("PlainKalmanFilterBallLocator:draw_ball_on_field",        "draw the modelled ball on the field",                              false);
    DEBUG_REQUEST_REGISTER("PlainKalmanFilterBallLocator:draw_ball_on_field_before", "draw the modelled ball on the field before prediction and update",  true);
    DEBUG_REQUEST_REGISTER("PlainKalmanFilterBallLocator:draw_real_ball_percept",    "draw the real incomming ball percept",                              true);
    DEBUG_REQUEST_REGISTER("PlainKalmanFilterBallLocator:draw_final_ball",           "draws the final i.e. best model",                                   true);
    DEBUG_REQUEST_REGISTER("PlainKalmanFilterBallLocator:draw_assignment",           "draws the assignment of the ball percept to the filter",            true);
    DEBUG_REQUEST_REGISTER("PlainKalmanFilterBallLocator:reloadParameters",          "reloads the kalman filter parameters from the kfParameter object", false);

    getDebugParameterList().add(&kfParameters);

    reloadParameters();
}

PlainKalmanFilterBallLocator::~PlainKalmanFilterBallLocator()
{
    getDebugParameterList().remove(&kfParameters);
}

void PlainKalmanFilterBallLocator::execute()
{
    // apply odometry on the filter state, to keep it in the robot's local coordinate system
    for(std::vector<KalmanFilter4d>::iterator iter = filter.begin(); iter != filter.end(); iter++){
        applyOdometryOnFilterState(*iter);
    }

    doDebugRequestBeforPredictionAndUpdate();

    // prediction
    double dt = getFrameInfo().getTimeInSeconds() - lastFrameInfo.getTimeInSeconds();

    for(std::vector<KalmanFilter4d>::iterator iter = filter.begin(); iter != filter.end(); iter++){
        predict(*iter, dt);
    }

    // measurement
    if(getBallPercept().ballWasSeen)
    {
        Eigen::Vector2d z;
        z << getBallPercept().bearingBasedOffsetOnField.x,
             getBallPercept().bearingBasedOffsetOnField.y;

        if(filter.size() == 0)
        {
            Eigen::Vector4d newState;
            newState << z(0), 0, z(1), 0;
            filter.push_back(KalmanFilter4d(newState, processNoiseStdSingleDimension, measurementNoiseStd, initialStateStdSingleDimension));
        }
        else
        {
            // find best matching filter
            double dist = euclidianDistanceToState(filter[0],z);
            std::vector<KalmanFilter4d>::iterator bestPredictor = filter.begin();

            for(std::vector<KalmanFilter4d>::iterator iter = bestPredictor; iter != filter.end(); iter++){
                double temp = euclidianDistanceToState(*iter, z);
                if(temp < dist){
                    dist = temp;
                    bestPredictor = iter;
                }
            }

            if(dist > distanceThreshold)
            {
                Eigen::Vector4d newState;
                newState << z(0), 0, z(1), 0;
                filter.push_back(KalmanFilter4d(newState, processNoiseStdSingleDimension, measurementNoiseStd, initialStateStdSingleDimension));
            }
            else
            {
                DEBUG_REQUEST("PlainKalmanFilterBallLocator:draw_assignment",
                    FIELD_DRAWING_CONTEXT;
                    PEN("FF0000", 10);
                    const Eigen::Vector2d state = (*bestPredictor).getStateInMeasurementSpace();
                    LINE(z(0),z(1),state(0),state(1));
                    TEXT_DRAWING((z(0)+state(0))/2,(z(1)+state(1))/2,dist);
                );

                (*bestPredictor).update(z);
            }
        }
    }

    // delete some filter if they are to bad
    std::vector<KalmanFilter4d>::iterator iter = filter.begin();
    while(iter != filter.end()){
        double std_x = std::sqrt((*iter).getProcessCovariance()(0,0));
        double std_y = std::sqrt((*iter).getProcessCovariance()(2,2));
        if((std_x > stdThreshold) || (std_y > stdThreshold)){
            filter.erase(iter);
        } else {
            iter++;
        }
    }

    // find best model
    if(filter.size() > 0)
    {
        std::vector<KalmanFilter4d>::iterator model = filter.begin();
        double evalue = (*model).getProcessCovariance()(0,0)+(*model).getProcessCovariance()(2,2);

        for(std::vector<KalmanFilter4d>::iterator iter = model; iter != filter.end(); iter++){
            double temp = (*iter).getProcessCovariance()(0,0)+(*iter).getProcessCovariance()(2,2);
            if(temp < evalue){
                evalue = temp;
                model = iter;
            }
        }

        bestModel = &(*model);
        const Eigen::Vector4d& x = (*model).getState();

        // set ball model representation
        getBallModel().position.x = x(0);
        getBallModel().position.y = x(2);
        getBallModel().speed.x = x(1);
        getBallModel().speed.y = x(3);

        // TODO: decide whether model is valid depending on P or time
        // e.g. if (max, min, std)

        if(getBallPercept().ballWasSeen)
        {
            getBallModel().setFrameInfoWhenBallWasSeen(getFrameInfo());
        }


        if(getFrameInfo().getTimeSince(getBallModel().frameInfoWhenBallWasSeen.getTime()) > 10000.0) // 10s
        {
            //reset(newPercept);
            getBallModel().valid = false; // model is not valid enymore after 10s
        }
        else
        {
            getBallModel().valid = true;
        }
    }

    doDebugRequest();

    lastFrameInfo     = getFrameInfo();
    lastRobotOdometry = getOdometryData();
}

double PlainKalmanFilterBallLocator::euclidianDistanceToState(const KalmanFilter4d& filter, const Eigen::Vector2d& z) const
{
    return std::sqrt(((z-filter.getStateInMeasurementSpace()).transpose() * Eigen::Matrix2d::Identity() * (z-filter.getStateInMeasurementSpace()))(0,0));
}

double PlainKalmanFilterBallLocator::evaluatePredictionWithMeasurement(const KalmanFilter4d& filter, const Eigen::Vector2d& z) const
{
    return std::exp(((filter.getStateInMeasurementSpace()-z).transpose() * filter.getMeasurementCovariance().inverse() * (filter.getStateInMeasurementSpace()-z))(0,0) * (-0.5));
}

void PlainKalmanFilterBallLocator::predict(KalmanFilter4d& filter, double dt)
{
    /*
        rolling resistance = rolling resitance coefficient * normal force
        F_R = d / R * F_N

        F_N = g * weight
        g = 9.81
        weight = ballMass

        deceleration = F_R/ballMass
    */

    const Eigen::Vector4d& x = filter.getState();
    Eigen::Vector2d u; // control vector

    double deceleration = c_RR*9810;//[mm/s^2]

    // deceleration has to be in opposite direction of velocity
    u <<  -x(1), -x(3);

    // deceleration vector with "absoult deceleration" (length of vector) of deceleration
    if(u.norm() > 0){
        u.normalize();
    }
    u *= deceleration;

    double time_until_vel_x_zero = 0;
    double time_until_vel_y_zero = 0;

    if(fabs(u(0)) > epsilon){
        time_until_vel_x_zero = -x(1)/u(0);
    }
    if(fabs(u(1)) > epsilon){
        time_until_vel_y_zero = -x(3)/u(1);
    }

    if(time_until_vel_x_zero > dt && time_until_vel_y_zero > dt)
    {
        filter.prediction(u,dt);
        return;
    }

    if(time_until_vel_x_zero < epsilon && time_until_vel_y_zero < epsilon)
    {
        filter.prediction(Eigen::Vector2d::Zero(),dt);
        return;
    }

    if(time_until_vel_x_zero < time_until_vel_y_zero)
    {
        filter.prediction(u,time_until_vel_x_zero);
        u(0) = 0;
        dt -= time_until_vel_x_zero;

        if(time_until_vel_y_zero < dt)
        {
            double dt2 = time_until_vel_y_zero - time_until_vel_x_zero;
            filter.prediction(u, dt2);
            u(1) = 0;
            dt -= dt2;
        }

        filter.prediction(u,dt);
    } else {
        filter.prediction(u,time_until_vel_y_zero);
        u(1) = 0;
        dt -= time_until_vel_y_zero;

        if(time_until_vel_x_zero < dt)
        {
            double dt2 = time_until_vel_x_zero - time_until_vel_y_zero;
            filter.prediction(u, dt2);
            u(0) = 0;
            dt -= dt2;
        }

        filter.prediction(u,dt);
    }
}

void PlainKalmanFilterBallLocator::applyOdometryOnFilterState(KalmanFilter4d& filter)
{
    const Eigen::Vector4d& x = filter.getState();
    Pose2D odometryDelta = lastRobotOdometry - getOdometryData();

    //rotate and translate location part of the filter's state
    Vector2<double> location = Vector2<double>(x(0), x(2)); // translation of the model
    location = odometryDelta * location;

    //just rotate the velocity part of the filter's state
    Vector2<double> velocity = Vector2<double>(x(1), x(3)); // translation of the model
    velocity.rotate(odometryDelta.getAngle());

    Eigen::Vector4d newStateX;
    newStateX << location.x, velocity.x, location.y, velocity.y;

    filter.setState(newStateX);
}

void PlainKalmanFilterBallLocator::doDebugRequest()
{
    if(getBallPercept().ballWasSeen) {
        //to check correctness of the prediction
        DEBUG_REQUEST("PlainKalmanFilterBallLocator:draw_real_ball_percept",
          FIELD_DRAWING_CONTEXT;
          PEN("FF0000", 10);
          CIRCLE(getBallPercept().bearingBasedOffsetOnField.x, getBallPercept().bearingBasedOffsetOnField.y, getFieldInfo().ballRadius-5);
        );
    }

    DEBUG_REQUEST("PlainKalmanFilterBallLocator:draw_final_ball",
        FIELD_DRAWING_CONTEXT;
        PEN("FF9900", 10);
        CIRCLE( getBallModel().position.x, getBallModel().position.y, getFieldInfo().ballRadius-10);
    );

    DEBUG_REQUEST("PlainKalmanFilterBallLocator:draw_ball_on_field",
        drawFiltersOnField();
    );

    DEBUG_REQUEST("PlainKalmanFilterBallLocator:reloadParameters",
        reloadParameters();
    );
}

void PlainKalmanFilterBallLocator::doDebugRequestBeforPredictionAndUpdate()
{
    DEBUG_REQUEST("PlainKalmanFilterBallLocator:draw_ball_on_field_before",
        drawFiltersOnField();
    );
}

void PlainKalmanFilterBallLocator::drawFiltersOnField() {
    FIELD_DRAWING_CONTEXT;
    for(std::vector<KalmanFilter4d>::iterator iter = filter.begin(); iter != filter.end(); iter++)
    {
        if(getBallModel().valid)
        {
            if(bestModel == &(*iter))
            {
                if(getBallPercept().ballWasSeen)
                    PEN("FF9900", 20);
                else
                    PEN("0099FF", 20);
            } else {
                PEN("999999", 20);
            }
        }
        else
            PEN("999999", 20);

        const Eigen::Vector4d& state = (*iter).getState();

        CIRCLE( state(0), state(2), getFieldInfo().ballRadius-10);
        ARROW( state(0), state(2),
               state(0)+state(1),
               state(2)+state(3));

        const Eigen::Matrix4d& P = (*iter).getProcessCovariance();

        // draw the distribution
        PEN("00FFFF", 20); // türkis, location
        OVAL(state(0), state(2), std::sqrt(P(0,0)), std::sqrt(P(2,2)));
        PEN("FF00FF", 20); // pink, velocity
        OVAL(state(0), state(2), std::sqrt(P(1,1)), std::sqrt(P(3,3)));
    }
}

void PlainKalmanFilterBallLocator::reloadParameters()
{
    // parameters for initializing new filters
    processNoiseStdSingleDimension << kfParameters.processNoiseStdQ00, kfParameters.processNoiseStdQ01,
                                      kfParameters.processNoiseStdQ10, kfParameters.processNoiseStdQ11;

    measurementNoiseStd << kfParameters.measurementNoiseStdR00, 0,
                           0, kfParameters.measurementNoiseStdR11;

    initialStateStdSingleDimension << kfParameters.initialStateStdP00, kfParameters.initialStateStdP01,
                                      kfParameters.initialStateStdP10, kfParameters.initialStateStdP11;

    // filter unspecific parameters
    c_RR              = kfParameters.c_RR;
    distanceThreshold = kfParameters.distanceThreshold;
    stdThreshold      = kfParameters.stdThreshold;

    // update existing filters with new process and measurement noise
    Eigen::Matrix2d processNoiseCovariancesSingleDimension;
    processNoiseCovariancesSingleDimension = processNoiseStdSingleDimension.cwiseProduct(processNoiseStdSingleDimension);

    Eigen::Matrix2d measurementNoiseCovariances = Eigen::Matrix2d::Zero();
    measurementNoiseCovariances = measurementNoiseStd.cwiseProduct(measurementNoiseStd);

    for(std::vector<KalmanFilter4d>::iterator iter = filter.begin(); iter != filter.end(); iter++){
        (*iter).setCovarianceOfProcessNoise(processNoiseCovariancesSingleDimension);
        (*iter).setCovarianceOfMeasurementNoise(measurementNoiseCovariances);
    }
}
