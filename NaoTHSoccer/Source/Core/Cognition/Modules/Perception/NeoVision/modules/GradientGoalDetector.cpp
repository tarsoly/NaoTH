
/**
* @file GradientGoalDetector.cpp
*
* Implementation of class GradientGoalDetector
*
*/

#include "GradientGoalDetector.h"

#include "Tools/DataStructures/ArrayQueue.h"
#include "Tools/CameraGeometry.h"

#include "Tools/Debug/Stopwatch.h"

#include "Tools/ImageProcessing/BresenhamLineScan.h"

#include <Representations/Infrastructure/CameraInfoConstants.h>


GradientGoalDetector::GradientGoalDetector()
: 
  cameraID(CameraInfo::Bottom)
{
  DEBUG_REQUEST_REGISTER("NeoVision:GradientGoalDetector:markPeaks", "mark found maximum u-v peaks in image", false);
  DEBUG_REQUEST_REGISTER("NeoVision:GradientGoalDetector:draw_scanlines","..", false);  
  DEBUG_REQUEST_REGISTER("NeoVision:GradientGoalDetector:draw_response","..", false);  
  DEBUG_REQUEST_REGISTER("NeoVision:GradientGoalDetector:draw_difference","..", false);  
  DEBUG_REQUEST_REGISTER("NeoVision:GradientGoalDetector:markFootScans","..", false);  
  DEBUG_REQUEST_REGISTER("NeoVision:GradientGoalDetector:markFootScanResponse","..", false);  
  DEBUG_REQUEST_REGISTER("NeoVision:GradientGoalDetector:markFootScanGoodPoints","..", false);   

  DEBUG_REQUEST_REGISTER("NeoVision:GradientGoalDetector:use_horizon","..", false);
}


void GradientGoalDetector::execute(CameraInfo::CameraID id, bool horizon)
{
  cameraID = id;
  CANVAS_PX(cameraID);

  getGoalPercept().reset();



  //if(cameraID == CameraInfo::Top)
  {
    Vector3d zem = CameraGeometry::imagePixelToWorld(getCameraMatrix(), getImage().cameraInfo,
      getImage().cameraInfo.getOpticalCenterX(), getImage().cameraInfo.getOpticalCenterY(),
      300);

    zem.y = 0;
    zem.x = 500;
    zem.z = getCameraMatrix().translation.z;

    Vector2<int> pp = CameraGeometry::relativePointToImage(getCameraMatrix(), getImage().cameraInfo,zem);

    if(pp.x > 40 && pp.x < 640 - 40 && pp.y > 0 && pp.y < 480)
    {
      LINE_PX(ColorClasses::red, pp.x - 20, pp.y, pp.x+20, pp.y);
    }
  }

  Vector2d p1(0, getImage().cameraInfo.getOpticalCenterY());
  Vector2d p2(getImage().cameraInfo.resolutionWidth, getImage().cameraInfo.getOpticalCenterY());
  Vector2d direction(1,0);

  if(horizon) {
    p1 = getArtificialHorizon().begin();
    p2 = getArtificialHorizon().end();
    direction = getArtificialHorizon().getDirection();
  }
  
  int imageBorderOffset = 25;
  int heightOfHorizon = (int) ((p1.y + p2.y) * 0.5 + 0.5);
  // image over the horizon
  if(heightOfHorizon > (int) getImage().cameraInfo.resolutionHeight - 10) 
  { 
    return;
  }

  // adjust the scan height in case of the bottom camera
  //if(cameraID == CameraInfo::Bottom) 
  {
    // clamp the scanline
    p1.y = Math::clamp((int) p1.y, imageBorderOffset + 5, (int)getImage().cameraInfo.resolutionHeight - imageBorderOffset - 5);
    p2.y = Math::clamp((int) p2.y, imageBorderOffset + 5 , (int)getImage().cameraInfo.resolutionHeight - imageBorderOffset - 5);
  }
  
  //double horizont = min(p1.y, p2.y);

  double threshold = params.gradientThreshold;
  double thresholdY = params.minY;

  double response = 0.0;
  double responseY = 0.0;
  double lastResponse = 0.0;
  double lastResponseY = 0.0;

  Pixel pixel;

  int aktIdx = 0;

  for(int i = 0; i < 5; i++)
  {
     features[i].clear();
  }

  if
  (
    p1.y > imageBorderOffset && 
    p2.y > imageBorderOffset && 
    p1.y < (int) getImage().height() - imageBorderOffset && 
    p2.y < (int) getImage().height() - imageBorderOffset
  )
  {
    bool isCandidate = false;
    bool isObstacle = false;
    
    Feature candidate;

    int diffVU = 0;
    int lastDiffVU = 0;

    for(int y = (int) p1.y - 12; y <= (int) p1.y + 12; y += 6)
    {
      valueBuffer.init();
      valueBufferY.init();
      pointBuffer.init();
      isCandidate = false;
      Vector2<int> pos((int) p1.x + 2, y);
      BresenhamLineScan scanner(pos, direction, getImage().cameraInfo);
      do
      {
        pointBuffer.add(pos);
        getImage().get(pos.x, pos.y, pixel);
        diffVU = (int) pixel.v - (int) pixel.u;
        valueBuffer.add(diffVU);
        valueBufferY.add(pixel.y);

        if(pos.x > 3)
        {
          response = valueBuffer[4] + 2 * valueBuffer[3]  + 4 * valueBuffer[2] + valueBuffer[1] * 2 + valueBuffer[0];
          //response = valueBuffer[4] + 2 * valueBuffer[3]  - valueBuffer[1] * 2 - valueBuffer[0];
          responseY = valueBufferY[2];
          response /= 10;
          DEBUG_REQUEST("NeoVision:GradientGoalDetector:draw_scanlines",
            if(aktIdx == 2)
            {
              POINT_PX(ColorClasses::yellow, pos.x, pos.y );
            }
            else
            {
              POINT_PX(ColorClasses::gray, pos.x, pos.y );
            }
          );
          DEBUG_REQUEST("NeoVision:GradientGoalDetector:draw_difference",
            if(aktIdx == 2)
            {
              LINE_PX(ColorClasses::green, (int) pointBuffer[3].x, (int) pointBuffer[3].y - lastDiffVU, (int) pointBuffer[4].x, (int) pointBuffer[4].y - diffVU);
              lastDiffVU = diffVU;
            }
          );
          DEBUG_REQUEST("NeoVision:GradientGoalDetector:draw_response",
            if(aktIdx == 2)
            {
              LINE_PX(ColorClasses::red, (int) pointBuffer[1].x, (int) pointBuffer[1].y - (int) /*fabs*/(lastResponse), (int) pointBuffer[2].x, (int) pointBuffer[2].y - (int)/* fabs*/(response) );
              LINE_PX(ColorClasses::white, (int) pointBuffer[1].x, (int) pointBuffer[1].y - (int) fabs(lastResponseY / 3), (int) pointBuffer[2].x, (int) pointBuffer[2].y - (int) fabs(responseY / 3) );
              lastResponse = response;
              lastResponseY = responseY;
            }
          );
          if(/*fabs*/(response) >= threshold && fabs(responseY) >= thresholdY)
          {
            if(!isCandidate)
            {
              candidate.begin = pointBuffer[2];
              candidate.center = pointBuffer[2];
              candidate.end = pointBuffer[2];
              candidate.responseAtBegin.x = response;
              candidate.responseAtBegin.y = diffVU;
              if(diffVU < 0)
              {
                isObstacle = true;
              }
            }
            isCandidate = true;
            if(isObstacle)
            {
              candidate.possibleObstacle = isObstacle;
              DEBUG_REQUEST("NeoVision:GradientGoalDetector:markPeaks", 
                POINT_PX(ColorClasses::orange, pos.x - 2, pos.y);
              );
            }
            else
            {
              DEBUG_REQUEST("NeoVision:GradientGoalDetector:markPeaks", 
                POINT_PX(ColorClasses::blue, pos.x - 2, pos.y);
              );
            }
          }
          else
          {
            if(isCandidate)
            {
              candidate.end = pointBuffer[2];
              candidate.center = (candidate.end + candidate.begin) / 2;
              candidate.responseAtEnd.x = response;
              candidate.responseAtEnd.y = diffVU;
              features[aktIdx].push_back(candidate);
            }
            isCandidate = false;
            isObstacle = false;
          }//end if
        }
      }
      while(scanner.getNextWithCheck(pos));
      aktIdx++;
    }//end for
  }//end if
  Vector2<double> dir(-direction.y, direction.x);

  memset(&lastTestFeatureIdx, 0, sizeof(lastTestFeatureIdx));
  bool goalPostFound = false;
  goalPosts.clear();

  //std::cout << std::endl << " ------ " << std::endl;
  for(unsigned i = 0; i < features[0].size(); i++)
  {
    const Feature& candidate = features[0][i];

    BresenhamLineScan footPointScanner(candidate.center, dir, getImage().cameraInfo);

    int goodPointsCount = 1;

    Vector2<int> pos = candidate.center;
    valueBuffer.init();
    valueBufferY.init();
    pointBuffer.init();
    
    Vector2d last(pos);

    for(int y = 1; y < 5; y++)
    {
      bool stop = false;
      for(int yy = 0; yy < 5; yy++)
      {
        if(footPointScanner.getNextWithCheck(pos))
        {
          DEBUG_REQUEST("NeoVision:GradientGoalDetector:markFootScans", 
            POINT_PX(ColorClasses::skyblue, pos.x, pos.y);
          );
          pointBuffer.add(pos);
          getImage().get(pos.x, pos.y, pixel);
          int diffVU = (int) pixel.v - (int) pixel.u;
          valueBuffer.add(diffVU);
          valueBufferY.add(pixel.y);

          if(yy > 0)
          {
            response = valueBuffer[4] + 2 * valueBuffer[3]  + 4 * valueBuffer[2] + valueBuffer[1] * 2 + valueBuffer[0];
            //response = valueBuffer[4] + 2 * valueBuffer[3]  - valueBuffer[1] * 2 - valueBuffer[0];
            responseY = valueBufferY[2];
            response /= 10;
            if(/*fabs*/(response) < params.responseHoldFactor * threshold || fabs(responseY) < params.responseHoldFactor * thresholdY)
            {
              stop = true;
            }
          }
        }
      }
      unsigned j = lastTestFeatureIdx[y];
      while (!stop && j < features[y].size())
      {
        int dist = (pos - features[y][j].center).abs();
        if(dist < params.dist)
        {
          DEBUG_REQUEST("NeoVision:GradientGoalDetector:markFootScanGoodPoints", 
            POINT_PX(ColorClasses::red, features[y][j].center.x, features[y][j].center.y);
          );
          lastTestFeatureIdx[y] = j;
          goodPointsCount++;
          stop = true;
           //std::cout << "good (" << i << ") " << dist << " pos: " << pos << " point:" << features[y][j].center << std::endl;
        }
        j++;
      }
    }//end for


    if(goodPointsCount >= params.minGoodPoints)
    {
      
      bool footPointFound = false;
      bool stop = false;
      Pixel pixel1;
      Pixel pixel2;
      Pixel pixel3;

      int lastDiffVU = 0;
      int lastResponse = 0;

      while(!stop && footPointScanner.getNextWithCheck(pos))
      {
        pointBuffer.add(pos);
        getImage().get(pos.x, pos.y, pixel);
        int diffVU = (int) pixel.v - (int) pixel.u;
        valueBuffer.add(diffVU);
        valueBufferY.add(pixel.y);

        response = valueBuffer[4] + 2 * valueBuffer[3]  + 4 * valueBuffer[2] + valueBuffer[1] * 2 + valueBuffer[0];
        //response = valueBuffer[4] + 2 * valueBuffer[3]  - valueBuffer[1] * 2 - valueBuffer[0];
        responseY = valueBufferY[2];
        response /= 10;

        DEBUG_REQUEST("NeoVision:GradientGoalDetector:markFootScans", 
          if(getFieldColorPercept().isFieldColor(pixel))
          {
             POINT_PX(ColorClasses::green, (int) pointBuffer[2].x, (int) pointBuffer[2].y);
          }
          else
          {
            POINT_PX(ColorClasses::gray, (int) pointBuffer[2].x, (int) pointBuffer[2].y);
          }
        );
        DEBUG_REQUEST("NeoVision:GradientGoalDetector:markFootScanResponse", 
          LINE_PX(ColorClasses::white, (int) pointBuffer[1].x + lastResponse, (int) pointBuffer[1].y, (int) pointBuffer[2].x + (int) response, (int) pointBuffer[2].y);
          LINE_PX(ColorClasses::orange, (int) pointBuffer[1].x + lastDiffVU, (int) pointBuffer[1].y, (int) pointBuffer[2].x + diffVU, (int) pointBuffer[2].y);
        );
        lastDiffVU = diffVU;
        lastResponse = (int) response;
 
        getImage().get((int) pointBuffer[4].x, (int) pointBuffer[4].y, pixel1);
        getImage().get((int) pointBuffer[3].x, (int) pointBuffer[3].y, pixel2);
        getImage().get((int) pointBuffer[2].x, (int) pointBuffer[2].y, pixel3);
        if(/*fabs*/(response) < params.responseHoldFactor * threshold || fabs(responseY) < params.responseHoldFactor * thresholdY)
        {
          stop = true;
          if
          (
            //c > params.minScanPointsAfterGoodPoints && 
            (getFieldColorPercept().isFieldColor(pixel1) || getFieldColorPercept().isFieldColor(pixel2) || getFieldColorPercept().isFieldColor(pixel3))
          )
          {
            footPointFound = true;
          }
          else
          {
            int t = 0;
            int count = 0;
            while( t < 10 && footPointScanner.getNextWithCheck(pos))
            {
              getImage().get(pos.x, pos.y, pixel);
              if(getFieldColorPercept().isFieldColor(pixel))
              {
                count++;
              }
              DEBUG_REQUEST("NeoVision:GradientGoalDetector:markFootScans", 
                if(getFieldColorPercept().isFieldColor(pixel))
                {
                   POINT_PX(ColorClasses::green, pos.x, pos.y);
                }
                else
                {
                  POINT_PX(ColorClasses::black, pos.x, pos.y);
                }
              );
              t++;
            }
            if(count > 4)
            {
              footPointFound = true;
            }
          }
        }
      }//end while

      if(footPointFound)
      {
        goalPostFound = true;
        GoalPercept::GoalPost post;

        post.basePoint = Vector2<int>(pointBuffer[2]);
        CameraGeometry::imagePixelToFieldCoord(
          getCameraMatrix(),
          getImage().cameraInfo,
          post.basePoint.x, post.basePoint.y, 0.0,
          post.position);

        post.positionReliable = true;
        goalPosts.push_back(post);
        getGoalPercept().add(post);

        DEBUG_REQUEST("NeoVision:GradientGoalDetector:markFootScans", 
          CIRCLE_PX(ColorClasses::yellowOrange, (int) pointBuffer[2].x, (int) pointBuffer[2].y, 10);
        );
      }
      else
      {
        DEBUG_REQUEST("NeoVision:GradientGoalDetector:markFootScans", 
          CIRCLE_PX(ColorClasses::red, (int) pointBuffer[2].x, (int) pointBuffer[2].y, 10);
        );
      }


    }//end if


    if(candidate.possibleObstacle)
    {
      DEBUG_REQUEST("NeoVision:GradientGoalDetector:markPeaks", 
        POINT_PX(ColorClasses::pink, candidate.center.x, candidate.center.y);
      );
    }
    else
    {
      DEBUG_REQUEST("NeoVision:GradientGoalDetector:markPeaks", 
        POINT_PX(ColorClasses::red, candidate.center.x, candidate.center.y);
      );
    }

  }//end for features[0].size()

  
  // exactly two posts are seen => assign site labels
  if(getGoalPercept().getNumberOfSeenPosts() == 2) {
    GoalPercept::GoalPost& postOne = getGoalPercept().getPost(0);
    GoalPercept::GoalPost& postTwo = getGoalPercept().getPost(1);
    
    // sort: which one is left or right
    if(postOne.basePoint.x > postTwo.basePoint.x)
    {
      postOne.type = GoalPercept::GoalPost::rightPost;
      postTwo.type = GoalPercept::GoalPost::leftPost;
    } else {
      postOne.type = GoalPercept::GoalPost::leftPost;
      postTwo.type = GoalPercept::GoalPost::rightPost;
    }
  }
}//end execute

