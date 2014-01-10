/* 
 * File:   ImageCorrector.h
 * Author: claas
 *
 * Created on 22. November 2010, 19:37
 */

#ifndef IMAGECORRECTOR_H
#define	IMAGECORRECTOR_H

#include <string>

#include <ModuleFramework/Module.h>

// Representations
#include "Representations/Infrastructure/Image.h"
#include "Representations/Infrastructure/ShadingCorrection.h"
#include "PlatformInterface/Platform.h"

// Tools
#include "Tools/Math/Vector2.h"
#include "Tools/Math/Vector3.h"
#include "Tools/Math/Matrix_mxn.h"
#include "Tools/DataStructures/ParameterList.h"

// Debug
#include "Tools/Debug/DebugRequest.h"

#if defined(__GNUC__) && defined(_NAOTH_CHECK_CONVERSION_)
#if __GNUC__ > 3 && __GNUC_MINOR__ > 5
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wconversion"
#endif
#include  <opencv2/core/core.hpp>
#include  <opencv2/imgproc/imgproc.hpp>
#if defined(__GNUC__) && defined(_NAOTH_CHECK_CONVERSION_)
#if __GNUC__ > 3 && __GNUC_MINOR__ > 5
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic error "-Wconversion"
#endif

//////////////////// BEGIN MODULE INTERFACE DECLARATION ////////////////////

BEGIN_DECLARE_MODULE(ImageCorrector)
  PROVIDE(Image)
END_DECLARE_MODULE(ImageCorrector)

//////////////////// END MODULE INTERFACE DECLARATION //////////////////////



class ImageCorrector  : private  ImageCorrectorBase
{
public:
  ImageCorrector();
  ~ImageCorrector();

  /** executes the module */
  void execute();
  void correctBrightnessSimple();

private:
  unsigned int correctionCycle;
  bool correctorIsRunning;
  bool simpleBrighnessCorrectionRequestActive;

  ShadingCorrection shadingCorrection;
};

#endif	/* IMAGECORRECTOR_H */

