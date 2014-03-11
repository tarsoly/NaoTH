/* 
 * File:   ScanLineEdgelDetector.cpp
 * Author: claas
 * Author: Heinrich Mellmann
 * 
 * Created on 14. march 2011, 14:22
 */

#include "ScanLineEdgelDetector.h"

// debug
#include "Tools/Debug/DebugModify.h"
#include "Tools/Debug/DebugRequest.h"
#include "Tools/Debug/DebugImageDrawings.h"
#include "Tools/Debug/DebugDrawings.h"
#include "Tools/Debug/Stopwatch.h"

// tools
#include "Tools/ImageProcessing/BresenhamLineScan.h"
#include "Tools/CameraGeometry.h"

ScanLineEdgelDetector::ScanLineEdgelDetector()
:
  cameraID(CameraInfo::Top)
{
  DEBUG_REQUEST_REGISTER("Vision:Detectors:ScanLineEdgelDetector:scanlines", "mark the scan lines", false);
  DEBUG_REQUEST_REGISTER("Vision:Detectors:ScanLineEdgelDetector:mark_edgels", "mark the edgels on the image", false);
  DEBUG_REQUEST_REGISTER("Vision:Detectors:ScanLineEdgelDetector:mark_double_edgels", "mark the edgels on the image", false);
  DEBUG_REQUEST_REGISTER("Vision:Detectors:ScanLineEdgelDetector:mark_endpoints", "mark the endpints on the image", false);
}

ScanLineEdgelDetector::~ScanLineEdgelDetector()
{}

void ScanLineEdgelDetector::execute(CameraInfo::CameraID id)
{
  cameraID = id;
  CANVAS_PX(cameraID);
  getScanLineEdgelPercept().reset();

  // TODO: implement a general validation for timestamps
  if(getBodyContour().timestamp != getFrameInfo().getTime()) {
    return;
  }
 
  int horizon_height = (int)(std::min(getArtificialHorizon().begin().y, getArtificialHorizon().end().y)+0.5);
  // clamp it to the image
  horizon_height = Math::clamp(horizon_height,0,(int)getImage().height());

  // scan only inside the estimated field region
  //horizon_height = getFieldPerceptRaw().getValidField().points[0].y;

  // horizontal stepsize between the scanlines
  int step = (getImage().width() - 1) / (theParameters.scanline_count - 1);

  // don't scan the lower lines in the image
  int borderY = getImage().height() - theParameters.pixel_border_y - 1;
  
  // start and endpoints for the scanlines
  Vector2i start(step / 2, borderY);
  Vector2i end(step / 2, horizon_height );
  
  for (int i = 0; i < theParameters.scanline_count - 1; i++)
  {
    ASSERT(getImage().isInside(start.x, start.y));
    // don't scan the own body
    start = getBodyContour().getFirstFreeCell(start);

    // execute the scan
    ScanLineEdgelPercept::EndPoint endPoint = scanForEdgels(i, start, end);
    
    // check if endpoint is not same as the begin of the scanline
    if(endPoint.posInImage == start) {
      endPoint.color = ColorClasses::none;
      endPoint.posInImage.y = borderY;
    }

    // try to project it on the ground
    endPoint.valid = CameraGeometry::imagePixelToFieldCoord(
      getCameraMatrix(),
      getCameraInfo(),
      endPoint.posInImage.x,
      endPoint.posInImage.y,
      0.0,
      endPoint.posOnField);

    //
    getScanLineEdgelPercept().endPoints.push_back(endPoint);

    start.y = borderY;
    start.x += step;
    end.x = start.x;
  }//end for


  DEBUG_REQUEST("Vision:Detectors:ScanLineEdgelDetector:mark_edgels",
    for(size_t i = 0; i < getScanLineEdgelPercept().edgels.size(); i++) {
      const Edgel& edgel = getScanLineEdgelPercept().edgels[i];
      LINE_PX(ColorClasses::black,edgel.point.x, edgel.point.y, edgel.point.x + (int)(edgel.direction.x*10), edgel.point.y + (int)(edgel.direction.y*10));
    }
  );

  // mark finished valid edgels
  DEBUG_REQUEST("Vision:Detectors:ScanLineEdgelDetector:mark_double_edgels",
    for(size_t i = 0; i < getScanLineEdgelPercept().pairs.size(); i++)
    {
      const ScanLineEdgelPercept::EdgelPair& pair = getScanLineEdgelPercept().pairs[i];
      CIRCLE_PX(ColorClasses::black, (int)pair.point.x, (int)pair.point.y, 3);
      LINE_PX(ColorClasses::red   ,(int)pair.point.x, (int)pair.point.y, (int)(pair.point.x + pair.direction.x*10), (int)(pair.point.y + pair.direction.y*10));
    }
  );
  
  DEBUG_REQUEST("Vision:Detectors:ScanLineEdgelDetector:mark_endpoints",
    for(size_t i = 0; i < getScanLineEdgelPercept().endPoints.size(); i++)
    {
      const ScanLineEdgelPercept::EndPoint& point_two = getScanLineEdgelPercept().endPoints[i];
      CIRCLE_PX(point_two.color, point_two.posInImage.x, point_two.posInImage.y, 5);

      if(i > 0) {
        const ScanLineEdgelPercept::EndPoint& point_one = getScanLineEdgelPercept().endPoints[i-1];
        LINE_PX(point_one.color,
                point_one.posInImage.x, point_one.posInImage.y,
                point_two.posInImage.x, point_two.posInImage.y);
      }
    }
  );
}//end execute


ScanLineEdgelPercept::EndPoint ScanLineEdgelDetector::scanForEdgels(int scan_id, const Vector2i& start, const Vector2i& end)
{
  ScanLineEdgelPercept::EndPoint endPoint;
  endPoint.posInImage = start;
  endPoint.color = ColorClasses::none;
  endPoint.ScanLineID = scan_id;

  const int step = 2;

  // no scan if the start is at the top of the image
  if(start.y <= step) {
    return endPoint;
  }

  Vector2i point(start);
  point.y -= step; // make one step

  Vector2i last_down_point(point); // needed for the endpoint
  bool begin_found = false;

  // calculate the threashold
  int t_edge = theParameters.brightness_threshold * 2;
  // HACK (TEST): make it dependend on the angle of the camera in the future
  if(cameraID == CameraInfo::Bottom) {
    t_edge *= 4;
  }

  // initialize the scanner
  Vector2i peak_point_max(point);
  Vector2i peak_point_min(point);
  MaximumScan<int,int> positiveScan(peak_point_max.y, t_edge);
  MaximumScan<int,int> negativeScan(peak_point_min.y, t_edge);

  int f_last = getImage().getY(point.x, point.y); // scan the first point
  // just go up
  for(;point.y >= end.y + step; point.y -= step)
  {
    // get the brightness chanel
    int f_y = getImage().getY(point.x, point.y);
    int g = f_y - f_last;
    f_last = f_y;

    // begin found
    if(positiveScan.addValue(point.y+1, g))
    {
      // refine the position of the peak
      int f_2 = getImage().getY(point.x, peak_point_max.y-2);
      int f0  = getImage().getY(point.x, peak_point_max.y);
      int f2  = getImage().getY(point.x, peak_point_max.y+2);

      if(f_2-f0 > positiveScan.maxValue()) peak_point_max.y -= 1;
      if(f0 -f2 > positiveScan.maxValue()) peak_point_max.y += 1;

      if(estimateColorOfSegment(last_down_point, peak_point_max) == ColorClasses::green) {
        endPoint.color = ColorClasses::green;
        endPoint.posInImage = peak_point_max;
      }

      add_edgel(peak_point_max);
      
      begin_found = true;
      last_down_point.y = peak_point_max.y;
    }//end if

    // end found
    if(negativeScan.addValue(point.y+1, -g))
    {
      // refine the position of the peak
      int f_2 = getImage().getY(point.x, peak_point_min.y-2);
      int f0  = getImage().getY(point.x, peak_point_min.y);
      int f2  = getImage().getY(point.x, peak_point_min.y+2);
        
      if(f_2-f0 < negativeScan.maxValue()) peak_point_min.y -= 1;
      if(f0 -f2 < negativeScan.maxValue()) peak_point_min.y += 1;

      if(estimateColorOfSegment(last_down_point, peak_point_min) == ColorClasses::green) {
        endPoint.color = ColorClasses::green;
        endPoint.posInImage = peak_point_min;
      }

      // new end edgel
      // found a new double edgel
      if(begin_found) {
        add_double_edgel(peak_point_min, scan_id);
        begin_found = false;
      } else {
        add_edgel(peak_point_min);
      }

      last_down_point.y = peak_point_min.y;
    }//end if


    DEBUG_REQUEST("Vision:Detectors:ScanLineEdgelDetector:scanlines",
      Pixel pixel = getImage().get(point.x, point.y);
      ColorClasses::Color thisPixelColor = (getFieldColorPercept().isFieldColor(pixel.a, pixel.b, pixel.c))?ColorClasses::green:ColorClasses::none;
      POINT_PX(thisPixelColor, point.x, point.y);
    );
  }//end for

  if(point.y < end.y + step) {
    if(estimateColorOfSegment(last_down_point, end) == ColorClasses::green) {
        endPoint.color = ColorClasses::green;
        endPoint.posInImage = end;
      }
  }

  return endPoint;
}//end scanForEdgels


ColorClasses::Color ScanLineEdgelDetector::estimateColorOfSegment(const Vector2i& begin, const Vector2i& end) const
{
  ASSERT(begin.x == end.x && end.y <= begin.y);

  const int numberOfSamples = theParameters.green_sampling_points;
  int length = begin.y - end.y;
  int numberOfGreen = 0;
  Vector2i point(begin);
  Pixel pixel;

  if(numberOfSamples >= length) 
  {
    for(; point.y > end.y; point.y--)
    {
      getImage().get(point.x, point.y, pixel);
      numberOfGreen += getFieldColorPercept().isFieldColor(pixel.a, pixel.b, pixel.c);
    }
  }
  else
  {
    int step = length / numberOfSamples;
    int offset = Math::random(length); // number in [0,length-1]

    for(int i = 0; i < numberOfSamples; i++)
    {
      int k = (offset + i*step) % length;
      point.y = end.y + k;
      getImage().get(point.x, point.y, pixel);
      numberOfGreen += getFieldColorPercept().isFieldColor(pixel.a, pixel.b, pixel.c);
    }
  }

  return (numberOfGreen > numberOfSamples/2) ? ColorClasses::green : ColorClasses::none;
}//end estimateColorOfSegment


Vector2d ScanLineEdgelDetector::calculateGradient(const Vector2i& point) const
{
  Vector2d gradient;

  // no angle at the border (shouldn't happen)
  if( point.x < 1 || point.x + 2 > (int)getImage().width() ||
      point.y < 1 || point.y + 2 > (int)getImage().height() ) {
    return gradient;
  }

  //apply Sobel Operator on (pointX, pointY)
  //and calculate gradient in x and y direction by that means
  
  gradient.x =
       getImage().getY(point.x-1, point.y+1)
    +2*getImage().getY(point.x  , point.y+1)
    +  getImage().getY(point.x+1, point.y+1)
    -  getImage().getY(point.x-1, point.y-1)
    -2*getImage().getY(point.x  , point.y-1)
    -  getImage().getY(point.x+1, point.y-1);

  gradient.y =
       getImage().getY(point.x-1, point.y-1)
    +2*getImage().getY(point.x-1, point.y  )
    +  getImage().getY(point.x-1, point.y+1)
    -  getImage().getY(point.x+1, point.y-1)
    -2*getImage().getY(point.x+1, point.y  )
    -  getImage().getY(point.x+1, point.y+1);

  //calculate the angle of the gradient
  return gradient.normalize();
}//end calculateGradient
