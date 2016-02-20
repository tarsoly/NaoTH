/**
* @file StandMotion.h
*
* @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
*
* the stand motion goes from current pose to the default stand pose.
* running - this motion is cyclic and there is allways running when the motion
*           request is set to stand
* stopped - the motion stopps when the motion request is not stand and the 
*           default stand pose has been reached
* 
*/

#ifndef _StandMotion_H
#define _StandMotion_H

#include "IKMotion.h"
#include "Tools/Debug/DebugPlot.h"

#include <ModuleFramework/Module.h>

// representations
#include <Representations/Infrastructure/RobotInfo.h>
#include "Representations/Motion/Request/MotionRequest.h"
#include "Representations/Modeling/GroundContactModel.h"
#include "Representations/Modeling/InertialModel.h"
#include <Representations/Infrastructure/JointData.h>
#include <Representations/Infrastructure/InertialSensorData.h>
#include <Representations/Infrastructure/GyrometerData.h>
#include <Representations/Infrastructure/CalibrationData.h>
#include "Representations/Modeling/KinematicChain.h"
#include "Representations/Infrastructure/CalibrationData.h"
#include "Representations/Infrastructure/FrameInfo.h"

BEGIN_DECLARE_MODULE(StandMotion)
  PROVIDE(DebugPlot)
  PROVIDE(DebugRequest)

  REQUIRE(FrameInfo)

  REQUIRE(RobotInfo)
  REQUIRE(MotionRequest)
  REQUIRE(GroundContactModel)
  REQUIRE(InertialModel)
  REQUIRE(InertialSensorData)
  REQUIRE(GyrometerData)
  REQUIRE(CalibrationData)
  REQUIRE(KinematicChainSensor)
  REQUIRE(MotionStatus)
  PROVIDE(SensorJointData)

  REQUIRE(InverseKinematicsMotionEngineService)

  PROVIDE(MotionLock)
  PROVIDE(MotorJointData)
END_DECLARE_MODULE(StandMotion)

class StandMotion : private StandMotionBase, public IKMotion
{
public:

  StandMotion()
  : IKMotion(getInverseKinematicsMotionEngineService(), motion::stand, getMotionLock()),
    totalTime(0),
    time(0),
    height(-1000),
    standardStand(true),
    relaxedPoseInitialized(false)

  {
    DEBUG_REQUEST_REGISTER("StandMotion:relax_joints", "set snsor joint data to motor joint data", false);
    DEBUG_REQUEST_REGISTER("StandMotion:relax_joints_loop", "set snsor joint data to motor joint data", false);
    DEBUG_REQUEST_REGISTER("StandMotion:relax_init", "set snsor joint data to motor joint data", false);
  }

  void calculateTrajectory(const MotionRequest& motionRequest)
  {
    // standing
    if ( isStopped()
        || height != motionRequest.standHeight // requested height changed
        || standardStand != motionRequest.standardStand ) 
    {
      standardStand = motionRequest.standardStand;
      height = motionRequest.standHeight;

      // init pose
      double comHeight = (height < 0.0) ? getEngine().getParameters().walk.hip.comHeight : motionRequest.standHeight;
      comHeight = Math::clamp(comHeight, 160.0, 270.0); // valid range
      
      startPose = getEngine().getCurrentCoMFeetPose();
      targetPose = getStandPose(comHeight, getEngine().getParameters().stand.hipOffsetX, getEngine().getParameters().stand.bodyPitchOffset, standardStand);

	    // HACK: don't do anything if after walk
      if(getMotionStatus().lastMotion == motion::walk) {
        targetPose = startPose;
      }

      targetPose.localInCoM();
      startPose.localInCoM();

      double speed = getEngine().getParameters().stand.speed;
      double distLeft = (targetPose.feet.left.translation - startPose.feet.left.translation).abs();
      double distRight = (targetPose.feet.right.translation - startPose.feet.right.translation).abs();
      double distMax = std::max(distLeft, distRight);
      totalTime = distMax / speed;
      time = 0;

      // set stiffness
      for( int i = naoth::JointData::RShoulderRoll; i<naoth::JointData::numOfJoint; i++) {
        getMotorJointData().stiffness[i] = getEngine().getParameters().stand.stiffness;
      }
      // HACK: turn off the hands
      getMotorJointData().stiffness[JointData::LHand] = -1;
      getMotorJointData().stiffness[JointData::RHand] = -1;
    }
  }//end calculateTrajectory


  void execute()
  {
    calculateTrajectory(getMotionRequest());

    time += getRobotInfo().basicTimeStep;

    double k = 1.0;
    if(totalTime > 0 && time < totalTime) {
      k = Math::clamp(0.5*(1.0-cos(time/totalTime*Math::pi)), 0.0, 1.0);
    }

    InverseKinematic::HipFeetPose c;

    if(time > totalTime + getRobotInfo().basicTimeStep*10) {

      if(!relaxedPoseInitialized) {
        relaxedPoseInitialized = true;
        relaxedPose = getEngine().getHipFeetPoseBasedOnSensor();
      }

      DEBUG_REQUEST("StandMotion:relax_init",
        relaxData = getSensorJointData();
        relaxedPose = getEngine().getHipFeetPoseBasedOnSensor();
        relaxedPoseInitialized = true;
      );

      c = relaxedPose;
    } else {
      InverseKinematic::CoMFeetPose p = getEngine().interpolate(startPose, targetPose, k);

      bool solved = false;
      c = getEngine().controlCenterOfMass(getMotorJointData(), p, solved, false);
    }
    
    /*
    InverseKinematic::HipFeetPose c;
    c.hip = p.com;
    c.hip.translation = Vector3d();
    c.feet = p.feet;

    getEngine().controlCenterOfMassCool(getMotorJointData(), p, c, true, solved, false);
    */

    if(getCalibrationData().calibrated && getEngine().getParameters().stand.enableStabilization)
    {
      /*
      getEngine().rotationStabilize(
        getRobotInfo(),
        getGroundContactModel(),
        getInertialSensorData(),
        c.hip);*/

      c.localInLeftFoot();
      getEngine().rotationStabilize(
        getInertialModel(),
        getGyrometerData(),
        getRobotInfo().getBasicTimeStepInSecond(),
        c);
    }

    getEngine().solveHipFeetIK(c);
    getEngine().copyLegJoints(getMotorJointData().position);
    

    DEBUG_REQUEST("StandMotion:relax_joints_loop",
      for( int i = naoth::JointData::RHipYawPitch; i<naoth::JointData::LAnkleRoll; i++) {
        getMotorJointData().position[i] = getSensorJointData().position[i];
      }
    );

    DEBUG_REQUEST("StandMotion:relax_joints",
      for( int i = naoth::JointData::RHipYawPitch; i<naoth::JointData::LAnkleRoll; i++) {
        getMotorJointData().position[i] = relaxData.position[i];
      }
    );


    /*
    getEngine().gotoArms(
        getMotionStatus(),
        getInertialModel(),
        getRobotInfo(),
        c, getMotorJointData().position);
    */
    PLOT("Stand:hip:x",c.hip.translation.x);
    PLOT("Stand:hip:y",c.hip.translation.y);
    PLOT("Stand:hip:z",c.hip.translation.z);


    turnOffStiffnessWhenJointIsOutOfRange();
    
    if ( time >= totalTime && getMotionRequest().id != getId() ) {
      setCurrentState(motion::stopped);
      return;
    } else {
      setCurrentState(motion::running);
    }
  }//end execute

private:
  void turnOffStiffnessWhenJointIsOutOfRange()
  {
    const double* pos = getMotorJointData().position;
    double* stiff = getMotorJointData().stiffness;
    // Knee pitch
    if ( pos[naoth::JointData::LKneePitch] > getMotorJointData().max[naoth::JointData::LKneePitch] ) {
      stiff[naoth::JointData::LKneePitch] = -1;
    } else {
      stiff[naoth::JointData::LKneePitch] = getEngine().getParameters().stand.stiffness;
    }
    if ( pos[naoth::JointData::RKneePitch] > getMotorJointData().max[naoth::JointData::RKneePitch] ) {
      stiff[naoth::JointData::RKneePitch] = -1;
    } else {
      stiff[naoth::JointData::RKneePitch] = getEngine().getParameters().stand.stiffness;
    }

    // Ankle pitch
    if ( pos[naoth::JointData::LAnklePitch] < getMotorJointData().min[naoth::JointData::LAnklePitch] ) {
      stiff[naoth::JointData::LAnklePitch] = -1;
    } else {
      stiff[naoth::JointData::LAnklePitch] = getEngine().getParameters().stand.stiffness;
    }
    if ( pos[naoth::JointData::RAnklePitch] < getMotorJointData().min[naoth::JointData::RAnklePitch] ) {
      stiff[naoth::JointData::RAnklePitch] = -1;
    } else {
      stiff[naoth::JointData::RAnklePitch] = getEngine().getParameters().stand.stiffness;
    }
  }//end turnOffStiffnessWhenJointIsOutOfRange

private:
  double totalTime;
  double time;
  double height;
  bool standardStand;
  InverseKinematic::CoMFeetPose targetPose;
  InverseKinematic::CoMFeetPose startPose;
  InverseKinematic::HipFeetPose relaxedPose;
  JointData relaxData;
  bool relaxedPoseInitialized;

};

#endif  /* _StandMotion_H */

