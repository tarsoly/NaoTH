/* 
 * File:   Cognition.h
 * Author: thomas
 *
 * Created on 10. August 2010, 17:27
 */

#ifndef COGNITION_H
#define	COGNITION_H

#include <iostream>
#include <Interface/PlatformInterface/Callable.h>

#include <Interface/Representations/Infrastructure/JointData.h>
#include <Interface/Representations/Infrastructure/VirtualVision.h>
#include <SimSpark/SimSparkGameInfo.h>

class Cognition : public naorunner::Callable
{
public:
  Cognition();
  virtual ~Cognition();


  template<class PlatformType>
  void init(PlatformType& platformInterface)
  {
    std::cout << "Cognition register start" << std::endl;
#define REGISTER_INPUT(R) platformInterface.registerCognitionInput(the##R, #R)
    REGISTER_INPUT(SensorJointData);
    REGISTER_INPUT(VirtualVision);
    REGISTER_INPUT(SimSparkGameInfo);

#undef REGISTER_INPUT
    std::cout << "Cognition register end" << std::endl;
  }


  virtual void call();

private:
  naorunner::SensorJointData theSensorJointData;
  naorunner::VirtualVision theVirtualVision;
  SimSparkGameInfo theSimSparkGameInfo;
};

#endif	/* COGNITION_H */

