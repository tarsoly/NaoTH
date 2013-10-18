#include "OpenCVImage.h"

#include <vector>

OpenCVImage::OpenCVImage()
{
}

OpenCVImage::OpenCVImage(const Image &orig)
{
  data = convertFromNaoImage(orig);
}

cv::Mat OpenCVImage::convertFromNaoImage(const Image &orig)
{
  // construct a matrix that has an column for each color value of each pixel
  cv::Mat newImg = cv::Mat::zeros(orig.height(), orig.width()*3, CV_8SC1);

  // wrap the original one in a way that uses 4 columns for two pixels
  cv::Mat wrappedYUV422((int) orig.height(), (int) orig.height()*2,
                        CV_8SC1,
                        (void*) orig.yuv422);

  std::vector<cv::Mat> src(1);
  src[0] = wrappedYUV422;

  std::vector<cv::Mat> dst(1);
  dst[0] = newImg;

  // Y1 U Y12 V will be converted to Y1 U V, Y2 U V
  // Y1=0 -> 0
  // U=1 -> 1,4
  // Y2=2 -> 3
  // V=3 -> 2,5
  int fromTo[] = { 0,0, 1,1, 1,4, 2,3, 3,2, 3,5};

  cv::mixChannels(src, dst, fromTo, 6);

  return newImg;
}
