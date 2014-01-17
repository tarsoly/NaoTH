#include "TeamCommReceiver.h"
#include "TeamCommSender.h"

#include <Tools/Debug/DebugRequest.h>
#include <Messages/Representations.pb.h>

using namespace std;

TeamCommReceiver::TeamCommReceiver()
{
  DEBUG_REQUEST_REGISTER("TeamCommReceiver:artificial_delay",
                         "Add an artificial delay to all team comm messages", false );
}

void TeamCommReceiver::execute()
{
  const naoth::TeamMessageDataIn& teamMessageData = getTeamMessageDataIn();

  bool usingDelayBuffer = false;
  DEBUG_REQUEST("TeamCommReceiver:artificial_delay",
    usingDelayBuffer = true;
  );

  for(vector<string>::const_iterator iter = teamMessageData.data.begin();
      iter != teamMessageData.data.end(); ++iter)
  {
    if(usingDelayBuffer)
    {
      delayBuffer.add(*iter);
    }
    else
    {
      handleMessage(*iter);
    }
  }

  // handle messages if buffer half full (so we get really old messages)
  if(usingDelayBuffer
     && delayBuffer.size() >= delayBuffer.getMaxEntries()/2)
  {
    // only handle a quarter of the messages
    for(int i=0; i < delayBuffer.getMaxEntries()/4; i++)
    {
      handleMessage(delayBuffer.first());
      delayBuffer.removeFirst();
    }
  }

  // add our own status as artifical message
  // (so we are not dependant on a lousy network)

  naothmessages::TeamCommMessage ownMsg;
  TeamCommSender::fillMessage(getPlayerInfo(), getRobotInfo(), getFrameInfo(),
                              getBallModel(), getRobotPose(), getBodyState(),
                              getMotionStatus(), getSoccerStrategy(), getPlayersModel(),
                              getTeamMessage(), ownMsg);

  handleMessage(ownMsg.SerializeAsString(), true);


}

void TeamCommReceiver::handleMessage(const string& msgContent, bool allowOwn)
{
  // TODO: implement handleMessage

  naothmessages::TeamMessage msg;
  msg.ParseFromString(msgContent);

  unsigned int num = msg.playernum();
  unsigned int teamnum = msg.team();

  if ( teamnum == getPlayerInfo().gameData.teamNumber
       // ignore our own messages, we are adding it artficially later
       && (allowOwn || num != getPlayerInfo().gameData.playerNumber)
     )
  {
    TeamMessage::Data& data = getTeamMessage().data[num];
    data.frameInfo.setTime( getFrameInfo().getTime() );

//    Serializer<TeamMessage::Data>::serialize(data)

//    if ( msg.has_opponent() && msg.opponent().number() )
//    {
//      // mark this opponent is updated
//      getTeamMessage().lastFrameNumberHearOpp[msg.opponent().number()] = getFrameInfo().getFrameNumber();
//    }
  }
}
