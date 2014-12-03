/*
 * 
 */

package de.naoth.rc.manager;

import com.google.protobuf.InvalidProtocolBufferException;
import de.naoth.rc.dataformats.SPLMessage;
import de.naoth.rc.dialogs.drawings.Circle;
import de.naoth.rc.dialogs.drawings.Drawable;
import de.naoth.rc.dialogs.drawings.DrawingOnField;
import de.naoth.rc.dialogs.drawings.DrawingsContainer;
import de.naoth.rc.dialogs.drawings.FillOval;
import de.naoth.rc.dialogs.drawings.Line;
import de.naoth.rc.dialogs.drawings.Pen;
import de.naoth.rc.dialogs.drawings.Robot;
import de.naoth.rc.dialogs.drawings.Text;
import de.naoth.rc.math.Pose2D;
import de.naoth.rc.math.Vector2D;
import de.naoth.rc.messages.Representations;
import de.naoth.rc.server.Command;
import de.naoth.rc.server.MessageServer;
import java.awt.Color;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;
import net.xeoh.plugins.base.annotations.PluginImplementation;

/**
 *
 * @author Heinrich Mellmann
 */
@PluginImplementation
public class TeamCommDrawingManagerImpl extends AbstractManager<DrawingsContainer>
        implements TeamCommDrawingManager
{

  private static class DummyServer extends MessageServer
  {
    @Override
    public boolean isConnected()
    {
       return true;
    }

    @Override
    public void connect(String host, int port) throws IOException
    {
      // do nothing
    }

    @Override
    public void disconnect()
    {
      // do nothing
    }
  }
 
  
  private final DummyServer dummyServer = new DummyServer();
  private DrawingsContainer drawings;
  
  public TeamCommDrawingManagerImpl()
  {
  }

  @Override
  public void handleSPLMessages(Map<String, SPLMessage> messages)
  {
    drawings = new DrawingsContainer();
    
    for(SPLMessage msg : messages.values())
  {
      // add the drawings for this message/player
      for(Drawable drawing : parseContainer(msg))
      {
        drawings.add(drawing);
      }
    }
    
    // HACK: trigger distribution of the message
    handleResponse(null, null);
  }

  
  
  @Override
  public DrawingsContainer convertByteArrayToType(byte[] result) throws IllegalArgumentException
  {
    return drawings;

  }//end convertByteArrayToType


  private ArrayList<Drawable> parseContainer(SPLMessage msg)
  {
    ArrayList<Drawable> drawingList = new ArrayList<Drawable>();
    drawingList.add(new DrawingOnField(null));

    Pose2D robotPose = new Pose2D();

    drawingList.add(new Pen(30, Color.gray));
    
    robotPose = new Pose2D(msg.pose_x,
            msg.pose_y,
            msg.pose_a);

    
    drawingList.add(new Pen(1, msg.team == 0 ? Color.BLUE : Color.RED));
    Robot robot = new Robot(
            robotPose.translation.x,
            robotPose.translation.y,
            robotPose.rotation);

    drawingList.add(robot);

    try
    {
      Representations.BUUserTeamMessage bumsg = Representations.BUUserTeamMessage.parseFrom(msg.data);
      
      if(bumsg.hasWasStriker() && bumsg.getWasStriker())
      {
        drawingList.add(new Pen(30, Color.red));

        Circle marker = new Circle(
                (int)robotPose.translation.x,
                (int)robotPose.translation.y,
                150);

        drawingList.add(marker);
      }
      
      Pen pen = new Pen(1, Color.black);
      drawingList.add(pen);
      
    }
    catch(InvalidProtocolBufferException ex)
    {
      Logger.getLogger(TeamCommDrawingManager.class.getName()).log(Level.INFO, "Invalid user team-message", ex);
    }
   
    // get the number
    {

      drawingList.add(new Pen(1, Color.BLACK));
      Text text = new Text(
        (int) robotPose.translation.x,
        (int) robotPose.translation.y + 150,
        (msg.team == 0 ? "blue" : "red") + " " + msg.playerNum);
      drawingList.add(text);
    }

    // ball
    if(msg.ballAge >= 0)
    {
      drawingList.add(new Pen(1, Color.orange));

      Vector2D ballPos = new Vector2D(msg.ball_x,
        msg.ball_y);

      Vector2D globalBall = robotPose.multiply(ballPos);

      FillOval ball = new FillOval(
        (int) globalBall.x,
        (int) globalBall.y,
        65,
        65);
      drawingList.add(ball);
      
      // add a surrounding black circle so the ball is easier to see
      drawingList.add(new Pen(1, Color.black));
      Circle outerBall = new Circle((int) globalBall.x, (int) globalBall.y, 65);
      drawingList.add(outerBall);
      
      {
        // show the time since the ball was last seen
        drawingList.add(new Pen(1, Color.black));
        double t = msg.ballAge / 1000.0;

        Text text = new Text(
          (int) globalBall.x + 50,
          (int) globalBall.y + 50,
          Math.round(t) + "s");
        drawingList.add(text);
      }
      // draw a line between robot and ball
      {
        drawingList.add(new Pen(5, Color.orange));
        Line ballLine = new Line(
          (int) robotPose.translation.x, (int) robotPose.translation.y, 
          (int) globalBall.x,(int)  globalBall.y);
        drawingList.add(ballLine);
      }
    }

    return drawingList;
  }//end parseNewContainer

  @Override
  public Command getCurrentCommand()
  {
    return new Command("dummy_teamcomm_command");
  }

  @Override
  public MessageServer getServer()
  {
    return dummyServer;
  }
}//end TeamCommDrawingManager
