/* 
 * File:   ActionNew.h
* @author <a href="mailto:schlottb@informatik.hu-berlin.de">Benjamin Schlotter</a>
* Declaration of class ActionNew
*/

#ifndef _ActionNew_H
#define _ActionNew_H


class ActionNew
{
public:

  ActionNew() {}

  virtual ~ActionNew() {}

  // position of the most interesting point in robot coords
  enum ActionId
  {
    none,
    kick_short,
    kick_long,
    sidekick_left,
    sidekick_right 
  };
  
  //number of ActionID's, has to write manual
  static const int numOfActions = 5;

  ActionId myAction;
};


#endif  /* _ActionNew_H */

