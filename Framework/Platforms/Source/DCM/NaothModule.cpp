/**
* @file NaothModule.cpp
*
* @author <a href="mailto:welter@informatik.hu-berlin.de">Oliver Welter</a>
* @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
* Implementation of NaothModule
*/
#include "NaothModule.h"
#include "PlatformInterface/Platform.h"

using namespace naoth;

static NaothModule* theModule = NULL;

inline static void motion_wrapper_pre()
{
  if (theModule != NULL)
    theModule->motionCallbackPre();
}

inline static void motion_wrapper_post()
{
  if (theModule != NULL)
    theModule->motionCallbackPost();
}

NaothModule::NaothModule(ALPtr<ALBroker> pB, const std::string& pName ): 
  ALModule(pB, pName ),
  pBroker(pB)
{
  theModule = this;
  
 // Describe the module here
  setModuleDescription( "Naoth-controlunit of the robot" );
  // Define callable methods with there description
  functionName( "init", "NaothModule",  "Initialize Controller" );
  BIND_METHOD( NaothModule::init );
}

NaothModule::~NaothModule()
{
  theModule = NULL;
  delete theCognition;
  delete theMotion;
  delete theCognitionThread;
}

bool NaothModule::innerTest() 
{
  bool result = true;
  // put here codes dedicaced to autotest this module.
  // return false if fail, success otherwise
  return result;
}

std::string NaothModule::version()
{
  //return ALTOOLS_VERSION( NAOTH );
  return std::string(NAOTH_VERSION);
}


void NaothModule::init()
{
  if (!g_thread_supported())
    g_thread_init(NULL);
  
  //int cognition_interval = 60000;
  int cognition_interval =   40000;
  
  cout << "Initializing Controller" << endl;
  NaoController::getInstance().init(pBroker);

  
  cout << "Creating Cognition and Motion" << endl;
  theCognition = new Cognition();
  theMotion = new Motion();
  
  cout << "Registering Cognition and Motion" << endl;
  NaoController::getInstance().registerCallbacks(theMotion,theCognition);
  
  getParentBroker()->getProxy("DCM")->getModule()->atPreProcess(motion_wrapper_pre);
  getParentBroker()->getProxy("DCM")->getModule()->atPostProcess(motion_wrapper_post);
  
  cout << "Creating Cognition-Thread" << endl;
  theCognitionThread = new CognitionThread();
  theCognitionThread->setPeriod(cognition_interval);
  theCognitionThread->setRealtime(SCHED_RR,1);
  //theCognitionThread->setRealtime(SCHED_OTHER,0);
  theCognitionThread->create();
  
  cout << "NaothModule:init finished!" << endl;
}

void NaothModule::motionCallbackPre()
{
    // we are at the moment shortly before the DCM commands are send to the
    // USB bus, so put the motion execute stuff here
    NaoController::getInstance().callMotion();
}

void NaothModule::motionCallbackPost()
{
  NaoController::getInstance().updateSensorData(); // read sensor data from DCM
  
  // right behind the sensor update from the DCM
  // TODO: get stuff into internal buffers
}

void NaothModule::exit()
{
  cout << "NaoTH is exiting ..."<<endl;
  
  theCognitionThread->stop();
  theCognitionThread->join();
  
  // stop motion
  while ( !theMotion->exit() )
  {
    usleep(100000);
  }
  
  cout << "NaoTH exit is finished" << endl;
}
