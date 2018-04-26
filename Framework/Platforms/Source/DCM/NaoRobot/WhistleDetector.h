#ifndef _WhistleDetector_H
#define _WhistleDetector_H

#include <mutex>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <limits>

#include <fftw3/fftw3.h>
#include <pulse/simple.h>

#include "SoundConfig.h"

#include "Representations/Infrastructure/WhistlePercept.h"
#include "Representations/Infrastructure/WhistleControl.h"

namespace naoth
{

class WhistleDetector
{
public:
  WhistleDetector();
  virtual ~WhistleDetector();

  void get(naoth::WhistlePercept& perceptData);
  void set(const naoth::WhistleControl& controlData);

protected:
  std::thread whistleDetectorThread;
  std::mutex getMutex;
  std::mutex setMutex;
  int command;

  //Parameter Substitute:
  std::string whistleListFile = "whistles.lst";
  std::string activeChannels = "1010";

  double threshold = 0.25;
  bool checkAllWhistles = true;
  bool saveRawAudio = true;

  void initAudio();
  void clearBuffers();
  void loadReferenceWhistles();
  void execute(); // This should be called in a loop -> create loop function like in CPUTemperatureReader
  void deinitAudio();
  bool detectWhistles(int channel);

  pa_simple* paSimple;
  //RingBufferWithSum<int, 10> detectedCountBuffer;
  double signalBuffer[NUM_CHANNELS_RX][WHISTLE_BUFF_LEN];
  double* signal2correlateBuffer;
  fftw_complex* fftOut;
  fftw_complex* fftIn;
  double* correlatedBuffer;

  fftw_plan planFFT;
  fftw_plan planIFFT;

  std::vector<short> test_samples;

  //std::ifstream audioTestFile;
  //bool testFileMode;

  std::vector<fftw_complex*> referenceWhistleSpectra;
  std::vector<double> referenceWhistleAutoCorrelationMaxima;
  std::vector<std::string> referenceWhistleNames;
  std::vector<WhistlePercept::Whistle> recognizedWhistles;

  int overallWhistleEventCounter;
  //unsigned long long aktFrameTime;
  //unsigned long long lastFrameTime;
  std::vector<short> audioReadBuffer;

  volatile bool running;
  bool recording;
  bool resetting;
  std::ofstream outputFileStream;
  int startStopCount;
  int deinitCyclesCounter;
  long long samplesRecorded;
};

}
#endif // _WhistleDetector_H
