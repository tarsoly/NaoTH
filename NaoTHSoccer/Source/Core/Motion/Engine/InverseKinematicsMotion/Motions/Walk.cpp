/**
* @file Walk.cpp
*
* @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
*
*/

#include "Walk.h"

using namespace InverseKinematic;

Walk::Walk()
:IKMotion(motion::WALK),
theWalkParameters(theParameters.walk),
theWaitLandingCount(0),
theUnsupportedCount(0)
{
  
}
  
void Walk::execute(const MotionRequest& motionRequest, MotionStatus& motionStatus)
{
  if ( FSRProtection() ) return;
  
  if ( waitLanding() ) return;
  
  theCoMFeetPose = genCoMFeetTrajectory(motionRequest);
  
  HipFeetPose c = theEngine.controlCenterOfMass(theCoMFeetPose);
  
  theEngine.solveHipFeetIK(c);
  theEngine.copyLegJoints(theMotorJointData.position);

  currentState = running;
}

bool Walk::FSRProtection()
{
  // no foot on the ground, stop walking
  if ( theWalkParameters.enableFSRProtection &&
    theBlackBoard.theSupportPolygon.mode == SupportPolygon::NONE ) 
  {
    //TODO: clear walk?
    return true;
  }
  else
  {
    return false;
  }
}

bool Walk::waitLanding()
{
  bool raiseLeftFoot = theCoMFeetPose.lFoot.translation.z > 0;
  bool raiseRightFoot = theCoMFeetPose.rFoot.translation.z > 0;
  
  // don't raise two feet
  ASSERT( !(raiseLeftFoot && raiseRightFoot) );
  
  bool rightFootSupportable = theBlackBoard.theSupportPolygon.isLeftFootSupportable();
  bool leftFootSupportable = theBlackBoard.theSupportPolygon.isRightFootSupportable();

  bool unSupporting = (raiseLeftFoot && !rightFootSupportable)
                      || (raiseRightFoot && !leftFootSupportable);
                      
  if(unSupporting)
  {
    theUnsupportedCount++;
  }
  else
  {
    theUnsupportedCount = 0;
  }

  if ( theUnsupportedCount > theWalkParameters.maxUnsupportedCount
    && ( theWalkParameters.maxWaitLandingCount < 0 || theWaitLandingCount < theWalkParameters.maxWaitLandingCount) )
  {
    theWaitLandingCount++;
    return true;
  } else
  {
    theWaitLandingCount = 0;
    return false;
  }
}

CoMFeetPose Walk::genCoMFeetTrajectory(const MotionRequest& motionRequest)
{
  ZMPFeetPose zmp = genZMPFeetTrajectory(motionRequest);
  CoMFeetPose result = theEngine.controlZMP(zmp);
  return result;
}

ZMPFeetPose Walk::genZMPFeetTrajectory(const MotionRequest& motionRequest)
{
  ZMPFeetPose result;
  return result;
}