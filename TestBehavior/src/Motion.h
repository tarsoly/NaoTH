/* 
 * File:   Motion.h
 * Author: thomas
 *
 * Created on 10. August 2010, 17:27
 */

#ifndef MOTION_H
#define	MOTION_H

#include <Interface/Representations/Infrastructure/JointData.h>
#include <Interface/PlatformInterface/Callable.h>

class Motion : public naorunner::Callable
{
public:
  Motion();
  virtual ~Motion();

  virtual void init(naorunner::PlatformInterface& platformInterface);
  virtual void call();

private:

  bool countUp;
  double pos;
  naorunner::SensorJointData theSensorJointData;
  naorunner::MotorJointData theMotorJointData;
};

#endif	/* MOTION_H */

