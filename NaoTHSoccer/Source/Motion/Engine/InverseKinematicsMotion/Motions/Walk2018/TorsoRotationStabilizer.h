/**
 * @File:   FootTrajectoryGenerator.h
 *
 * @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
 * foot trajectory for walking
 */

#ifndef _TORSO_ROTATION_STABILIZER_H
#define _TORSO_ROTATION_STABILIZER_H

#include <ModuleFramework/Module.h>

#include "Representations/Motion/Walk2018/StepBuffer.h"
#include "Representations/Motion/Walk2018/TargetHipFeetPose.h"
#include "Representations/Infrastructure/CalibrationData.h"
#include "Representations/Modeling/InertialModel.h"
#include "Representations/Infrastructure/GyrometerData.h"
#include "Representations/Infrastructure/RobotInfo.h"

#include "Tools/Debug/DebugPlot.h"
#include "Tools/Debug/DebugRequest.h"
#include "Tools/Debug/DebugParameterList.h"

BEGIN_DECLARE_MODULE(TorsoRotationStabilizer)
    PROVIDE(DebugPlot)
    PROVIDE(DebugRequest)
    PROVIDE(DebugParameterList)

    REQUIRE(FrameInfo)
    REQUIRE(CalibrationData)
    REQUIRE(InertialModel)
    REQUIRE(GyrometerData)
    REQUIRE(RobotInfo)
    REQUIRE(StepBuffer)

    PROVIDE(TargetHipFeetPose)
END_DECLARE_MODULE(TorsoRotationStabilizer)

class TorsoRotationStabilizer : private TorsoRotationStabilizerBase
{
  public:
    TorsoRotationStabilizer(){
      getDebugParameterList().add(&parameters);
    }

    virtual ~TorsoRotationStabilizer(){
      getDebugParameterList().remove(&parameters);
    }

  virtual void execute(){
    if(getCalibrationData().calibrated && parameters.rotationStabilize) {
      if(getStepBuffer().first().footStep.liftingFoot() == FootStep::LEFT) {
        getTargetHipFeetPose().pose.localInRightFoot();
      } else if(getStepBuffer().first().footStep.liftingFoot() == FootStep::RIGHT) {
        getTargetHipFeetPose().pose.localInLeftFoot();
      } else {
        getTargetHipFeetPose().pose.localInHip();
      }

      rotationStabilize(
        getInertialModel(),
        getGyrometerData(),
        getRobotInfo().getBasicTimeStepInSecond(),
        parameters.rotation.P,
        parameters.rotation.VelocityP,
        parameters.rotation.D,
        getTargetHipFeetPose().pose
      );
    }
  }

  private:
      bool rotationStabilize(
        const InertialModel& theInertialModel,
        const GyrometerData& theGyrometerData,
        const double timeDelta,
        const Vector2d&  rotationP,
        const Vector2d&  rotationVelocityP,
        const Vector2d&  rotationD,
        InverseKinematic::HipFeetPose& p)
      {
        const double alpha = 0.5;
        Vector2d gyro = Vector2d(theGyrometerData.data.x, theGyrometerData.data.y);
        static Vector2d filteredGyro = gyro;
        filteredGyro = filteredGyro * (1.0f - alpha) + gyro * alpha;

        const double observerMeasurementDelay = 40;
        const int frameDelay = static_cast<int>(observerMeasurementDelay / (timeDelta*1000));

        static RingBuffer<Vector2d, 10> buffer;
        static Vector2d lastGyroError;
        static RotationMatrix lastBodyRotationMatrix = p.hip.rotation;

        const RotationMatrix relativeRotation = p.hip.rotation.invert() * lastBodyRotationMatrix;
        lastBodyRotationMatrix = p.hip.rotation;

        const double rotationY = atan2(relativeRotation.c[2].x, relativeRotation.c[2].z);
        buffer.add(Vector2d(relativeRotation.getXAngle(), rotationY));

        if(buffer.isFull() && frameDelay > 0 && frameDelay < buffer.size())
        {
          const Vector2d requestedVelocity = (buffer[frameDelay-1] - buffer[frameDelay]) / timeDelta;
          const Vector2d error = requestedVelocity - filteredGyro;
          const Vector2d errorDerivative = (error - lastGyroError) / timeDelta;

          double correctionY = rotationVelocityP.y * error.y +
                               rotationD.y * errorDerivative.y;

          double correctionX =rotationVelocityP.x * error.x +
                              rotationD.x * errorDerivative.x;

          const Vector2d& inertial = theInertialModel.orientation;
          correctionX += rotationP.x * inertial.x;
          correctionY += rotationP.y * inertial.y;

          p.localInHip();
          p.hip.rotateX(correctionX);
          p.hip.rotateY(correctionY);

          lastGyroError = error;
        }

        return true;
      }

    class Parameters: public ParameterList{
      public:
        Parameters() : ParameterList("TorsoRotationStabilizer")
        {
          PARAMETER_REGISTER(rotationStabilize) = true;

          PARAMETER_REGISTER(rotation.P.x) = -0.02;
          PARAMETER_REGISTER(rotation.P.y) = -0.03;
          PARAMETER_REGISTER(rotation.VelocityP.x) = 0.02;
          PARAMETER_REGISTER(rotation.VelocityP.x) = 0.02;
          PARAMETER_REGISTER(rotation.D.x) = 0;
          PARAMETER_REGISTER(rotation.D.y) = 0;

          syncWithConfig();
        }

        struct RotationStabilization{
            Vector2d P;
            Vector2d VelocityP;
            Vector2d D;
        } rotation;

        bool rotationStabilize;
    } parameters;
};

#endif  /* _TORSO_ROTATION_STABILIZER_H */
