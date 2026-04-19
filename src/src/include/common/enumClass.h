/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef ENUMCLASS_H
#define ENUMCLASS_H

#include <iostream>
#include <sstream>



enum class UserCommand{
    // EXIT,
    NONE,
    command,
    LEFTPUT,
    LEFTGET,
    RIGHTPUT,
    RIGHTGET,
    LEFTPUTRIGHTGET,
    RIGHTPUTLEFTGET,
    END
    
 
};



enum class FSMMode{
    NORMAL,
    CHANGE
};

enum class FSMStateName{
    // EXIT,
    INVALID,
    LEFTPUT,
    LEFTGET,
    RIGHTPUT,
    RIGHTGET,
    LEFTPUTRIGHTGET,
    RIGHTPUTLEFTGET,
    END
   

   
};

enum class StateFlag{
  start,
  down,
  grip,
  up,
  relax,
  back,
  bringback,
  transfer,
  keep,
  end,
  another
};

#endif  // ENUMCLASS_H