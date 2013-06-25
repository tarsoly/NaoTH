/**
* @file NeoVision.cpp
*
* @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
* Implementation of class NeoVision
*/

#include "NeoVision.h"

// Debug

NeoVision::NeoVision()
{
  DEBUG_REQUEST_REGISTER("NeoVision:FieldColorClassifierFull:execute", " ", false);
  theFieldColorClassifierFull = registerModule<FieldColorClassifierFull>("FieldColorClassifierFull");
  theFieldColorClassifierFull->setEnabled(true);

  DEBUG_REQUEST_REGISTER("NeoVision:SimpleFieldColorClassifier:execute", " ", true);
  theSimpleFieldColorClassifier = registerModule<SimpleFieldColorClassifier>("SimpleFieldColorClassifier");
  theSimpleFieldColorClassifier->setEnabled(true);

  DEBUG_REQUEST_REGISTER("NeoVision:SimpleGoalColorClassifier:execute", " ", true);
  theSimpleGoalColorClassifier = registerModule<SimpleGoalColorClassifier>("SimpleGoalColorClassifier");
  theSimpleGoalColorClassifier->setEnabled(true);

  DEBUG_REQUEST_REGISTER("NeoVision:SimpleBallColorClassifier:execute", " ", true);
  theSimpleBallColorClassifier = registerModule<SimpleBallColorClassifier>("SimpleBallColorClassifier");
  theSimpleBallColorClassifier->setEnabled(true);

  DEBUG_REQUEST_REGISTER("NeoVision:ScanLineEdgelDetectorDifferential:execute", " ", false);
  theScanLineEdgelDetectorDifferential = registerModule<ScanLineEdgelDetectorDifferential>("ScanLineEdgelDetectorDifferential");
  theScanLineEdgelDetectorDifferential->setEnabled(true);

  DEBUG_REQUEST_REGISTER("NeoVision:NeoLineDetector:execute", " ", false);
  theNeoLineDetector = registerModule<NeoLineDetector>("NeoLineDetector");
  theNeoLineDetector->setEnabled(true);

  DEBUG_REQUEST_REGISTER("NeoVision:MaximumRedBallDetector:execute", " ", true);
  theMaximumRedBallDetector = registerModule<MaximumRedBallDetector>("MaximumRedBallDetector");
  theMaximumRedBallDetector->setEnabled(true);
  
  DEBUG_REQUEST_REGISTER("NeoVision:GradientGoalDetector:execute", " ", true);
  theGradientGoalDetector = registerModule<GradientGoalDetector>("GradientGoalDetector");
  theGradientGoalDetector->setEnabled(true);
}//end constructor


void NeoVision::execute()
{
  DEBUG_REQUEST("NeoVision:FieldColorClassifierFull:execute",
    GT_TRACE("executing FieldColorClassifierFull");
    STOPWATCH_START("FieldColorClassifierFull");
    theFieldColorClassifierFull->execute();
    STOPWATCH_STOP("FieldColorClassifierFull");
  );

  DEBUG_REQUEST("NeoVision:SimpleFieldColorClassifier:execute",
    GT_TRACE("executing SimpleFieldColorClassifier");
    STOPWATCH_START("SimpleFieldColorClassifier");
    theSimpleFieldColorClassifier->execute();
    STOPWATCH_STOP("SimpleFieldColorClassifier");
  );

  DEBUG_REQUEST("NeoVision:SimpleGoalColorClassifier:execute",
    GT_TRACE("executing SimpleGoalColorClassifier");
    STOPWATCH_START("SimpleGoalColorClassifier");
    theSimpleGoalColorClassifier->execute();
    STOPWATCH_STOP("SimpleGoalColorClassifier");
  );

  DEBUG_REQUEST("NeoVision:SimpleBallColorClassifier:execute",
    GT_TRACE("executing SimpleBallColorClassifier");
    STOPWATCH_START("SimpleBallColorClassifier");
    theSimpleBallColorClassifier->execute();
    STOPWATCH_STOP("SimpleBallColorClassifier");
  );

  DEBUG_REQUEST("NeoVision:ScanLineEdgelDetectorDifferential:execute",
    GT_TRACE("executing ScanLineEdgelDetectorDifferential");
    STOPWATCH_START("ScanLineEdgelDetectorDifferential");
    theScanLineEdgelDetectorDifferential->execute();
    STOPWATCH_STOP("ScanLineEdgelDetectorDifferential");
  );

  DEBUG_REQUEST("NeoVision:NeoLineDetector:execute",
    GT_TRACE("executing NeoLineDetector");
    STOPWATCH_START("NeoLineDetector");
    theNeoLineDetector->execute();
    STOPWATCH_STOP("NeoLineDetector");
  );

  DEBUG_REQUEST("NeoVision:MaximumRedBallDetector:execute",
    GT_TRACE("executing MaximumRedBallDetector");
    STOPWATCH_START("MaximumRedBallDetector");
    theMaximumRedBallDetector->execute();
    STOPWATCH_STOP("MaximumRedBallDetector");
  );

  DEBUG_REQUEST("NeoVision:GradientGoalDetector:execute",
    GT_TRACE("executing GradientGoalDetector");
    STOPWATCH_START("GradientGoalDetector");
    theGradientGoalDetector->execute();
    STOPWATCH_STOP("GradientGoalDetector");
  );
}//end execute

