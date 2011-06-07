/**
 * @file Motion.h
 *
 * @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
 * @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
 *
 */

#ifndef MOTION_H
#define	MOTION_H

#include <PlatformInterface/Callable.h>
#include <PlatformInterface/PlatformInterface.h>
#include "MotionBlackBoard.h"
#include "AbstractMotion.h"
#include "MorphologyProcessor/SupportPolygonGenerator.h"
#include "MorphologyProcessor/OdometryCalculator.h"
#include "Engine/HeadMotion/HeadMotionEngine.h"
#include "Engine/MotionFactory.h"

class Motion : public naoth::Callable
{
public:
  Motion();
  virtual ~Motion();

  virtual void call();

  void init(naoth::PlatformDataInterface& platformInterface);
  
  bool exit();
  
protected:
  
  void processSensorData();
  
  void postProcess();
  
  void selectMotion();
  
  void changeMotion(AbstractMotion* m);
  
private:
  MotionBlackBoard& theBlackBoard;

  EmptyMotion theEmptyMotion;
  
  SupportPolygonGenerator theSupportPolygonGenerator;
  OdometryCalculator theOdometryCalculator;
  
  HeadMotionEngine theHeadMotionEngine;
  std::list<MotionFactory*> theMotionFactories;
};

#endif	/* MOTION_H */

