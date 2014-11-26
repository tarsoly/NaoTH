/* 
 * File:   StopwatchSender.h
 * Author: thomas
 *
 */

#ifndef STOPWATCHSENDER_H
#define STOPWATCHSENDER_H

#include <map>

#include <ModuleFramework/Module.h>
#include <DebugCommunication/DebugCommandExecutor.h>

#include <Tools/DataStructures/ParameterList.h>

#include <Representations/Infrastructure/FrameInfo.h>
#include <Tools/Debug/Stopwatch.h>

using namespace naoth;

BEGIN_DECLARE_MODULE(StopwatchSender)
  REQUIRE(FrameInfo)
END_DECLARE_MODULE(StopwatchSender)

class StopwatchSender : public StopwatchSenderBase, public DebugCommandExecutor
{
public:
  StopwatchSender();
  virtual ~StopwatchSender();

  virtual void execute();

  virtual void executeDebugCommand(
    const std::string& command, const std::map<std::string,std::string>& arguments,
    std::ostream &outstream);
};

template<>
class Serializer<StopwatchManager>
{
  public:
  static void serialize(const StopwatchManager& object, std::ostream& stream);

  // we don't need that
  //static void deserialize(std::istream& stream, StopwatchManager& object);
};

#endif  /* STOPWATCHSENDER_H */

