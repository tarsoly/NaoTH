/**
* @file IKParameters.cpp
*
* @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
* Implement of parameters for IK motion
*/

#include "IKParameters.h"


IKParameters::IKParameters()
:ParameterList("IKParameters")
{
  PARAMETER_REGISTER(footOffsetY) = 0;
  
  // stand parameter
  PARAMETER_REGISTER(stand.speed) = 0.04;
  PARAMETER_REGISTER(stand.enableStabilization) = false;
  PARAMETER_REGISTER(stand.stiffness) = 0.7;

  PARAMETER_REGISTER(stand.bodyPitchOffset) = 0.2;
  PARAMETER_REGISTER(stand.hipOffsetX) = 15;

  // relax
  PARAMETER_REGISTER(stand.relax.allowedDeviation)= 5;   // [mm]
  PARAMETER_REGISTER(stand.relax.timeBonusForCorrection) = 1000; // [ms]

  PARAMETER_REGISTER(stand.relax.jointOffsetTuning.deadTime)         = 1000;         // [ms]
  PARAMETER_REGISTER(stand.relax.jointOffsetTuning.currentThreshold) = 0.3;          // [A]
  PARAMETER_REGISTER(stand.relax.jointOffsetTuning.minimalJointStep) = 0.0013962634; // [rad]

  PARAMETER_REGISTER(stand.relax.stiffnessControl.minAngle)     = 0.08; // [°]
  PARAMETER_REGISTER(stand.relax.stiffnessControl.maxAngle)     = 2;    // [°]
  PARAMETER_REGISTER(stand.relax.stiffnessControl.minStiffness) = 0.3;
  PARAMETER_REGISTER(stand.relax.stiffnessControl.maxStiffness) = 1.0;

  // walk parameter:
  // General
  PARAMETER_REGISTER(walk.general.bodyPitchOffset) = 0.2;
  PARAMETER_REGISTER(walk.general.hipOffsetX) = 15;
  PARAMETER_REGISTER(walk.general.stiffness) = 0.7;
  PARAMETER_REGISTER(walk.general.useArm) = false;
  PARAMETER_REGISTER(walk.general.hipRollSingleSupFactorLeft) = 0.4;
  PARAMETER_REGISTER(walk.general.hipRollSingleSupFactorRight) = 0.4;

  // hip trajectory geometry
  PARAMETER_REGISTER(walk.hip.comHeight) = 260;
  PARAMETER_REGISTER(walk.hip.comHeightOffset) = 0.18;
  PARAMETER_REGISTER(walk.hip.comRotationOffsetX) = 0;
  PARAMETER_REGISTER(walk.hip.ZMPOffsetY) = 5;
  PARAMETER_REGISTER(walk.hip.ZMPOffsetYByCharacter) = 0;

  // step geometry
  PARAMETER_REGISTER(walk.step.duration) = 300;
  PARAMETER_REGISTER(walk.step.doubleSupportTime) = 40;

  PARAMETER_REGISTER(walk.step.stepHeight) = 10;

  // step limits
  PARAMETER_REGISTER(walk.limits.maxTurnInner) = 10;
  PARAMETER_REGISTER(walk.limits.maxStepTurn) = 30;
  PARAMETER_REGISTER(walk.limits.maxStepLength) = 50;
  PARAMETER_REGISTER(walk.limits.maxStepLengthBack) = 50;
  PARAMETER_REGISTER(walk.limits.maxStepWidth) = 50;
  PARAMETER_REGISTER(walk.limits.maxStepChange) = 0.5;

  // step control
  PARAMETER_REGISTER(walk.limits.maxCtrlTurn) = 30;
  PARAMETER_REGISTER(walk.limits.maxCtrlLength) = 80;
  PARAMETER_REGISTER(walk.limits.maxCtrlWidth) = 50;

  // Stabilization
  //PARAMETER_REGISTER(walk.stabilization.enableFSRProtection) = true;
  //PARAMETER_REGISTER(walk.stabilization.enableWaitLanding) = false;
  //PARAMETER_REGISTER(walk.stabilization.minFSRProtectionCount) = 0;
  //PARAMETER_REGISTER(walk.stabilization.maxUnsupportedCount) = 0;
  //PARAMETER_REGISTER(walk.stabilization.maxWaitLandingCount) = 20;

  PARAMETER_REGISTER(walk.stabilization.emergencyStopError) = 500;

  PARAMETER_REGISTER(walk.stabilization.rotationStabilize) = true;
  PARAMETER_REGISTER(walk.stabilization.rotationP.x) = 0;
  PARAMETER_REGISTER(walk.stabilization.rotationP.y) = 0;
  PARAMETER_REGISTER(walk.stabilization.rotationVelocityP.x) = 0;
  PARAMETER_REGISTER(walk.stabilization.rotationVelocityP.y) = 0;
  PARAMETER_REGISTER(walk.stabilization.rotationD.x) = 0;
  PARAMETER_REGISTER(walk.stabilization.rotationD.y) = 0;

  PARAMETER_REGISTER(walk.stabilization.stabilizeFeet) = true;
  PARAMETER_REGISTER(walk.stabilization.stabilizeFeetP.x) = 0.04;
  PARAMETER_REGISTER(walk.stabilization.stabilizeFeetP.y) = 0.035;
  PARAMETER_REGISTER(walk.stabilization.stabilizeFeetD.x) = -0.4;
  PARAMETER_REGISTER(walk.stabilization.stabilizeFeetD.y) = -0.3;

  PARAMETER_REGISTER(walk.stabilization.dynamicStepsize) = true;
  PARAMETER_REGISTER(walk.stabilization.dynamicStepsizeP) = -1;
  PARAMETER_REGISTER(walk.stabilization.dynamicStepsizeD) = 0.5;

  // rotation stabilize parameter
  PARAMETER_REGISTER(rotationStabilize.k.x) = -0.5;
  PARAMETER_REGISTER(rotationStabilize.k.y) = -0.2;
  PARAMETER_REGISTER(rotationStabilize.threshold.x) = 2;
  PARAMETER_REGISTER(rotationStabilize.threshold.y) = 3;

  // arm parameter
  PARAMETER_REGISTER(arm.shoulderPitchInterialSensorRate) = -10;
  PARAMETER_REGISTER(arm.shoulderRollInterialSensorRate) = -10;
  PARAMETER_REGISTER(arm.maxSpeed) = 60;
  PARAMETER_REGISTER(arm.alwaysEnabled)  = false;
  PARAMETER_REGISTER(arm.kickEnabled) = true;
  PARAMETER_REGISTER(arm.walkEnabled) = true;
  PARAMETER_REGISTER(arm.takeBack) = false;


  PARAMETER_REGISTER(balanceCoM.kP) = 0;
  PARAMETER_REGISTER(balanceCoM.kI) = 0;
  PARAMETER_REGISTER(balanceCoM.kD) = 0;
  PARAMETER_REGISTER(balanceCoM.threshold) = 10;

  syncWithConfig();

}

IKParameters::~IKParameters()
{
}
