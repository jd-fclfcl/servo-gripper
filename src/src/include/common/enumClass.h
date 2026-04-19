/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef ENUMCLASS_H
#define ENUMCLASS_H

#include <iostream>
#include <sstream>



enum class UserCommand{
    // EXIT,
    NONE,
    LEFTPUT,
    LEFTGET,
    RIGHTPUT,
    RIGHTGET,
    LEFTPUTRIGHTGET,
    RIGHTPUTLEFTGET,
    
 
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
   

   
};

enum class StateFlag{
    staticFlag, // staticFlag,
    Frist,
    Second,
    Third,
    Fourth,
    Fifth,
    Sixth,
    Seventh,
    Eighth,
    Ninth,
    Tenth,
    Eleventh,
    Twelfth,
    Thirteenth,
    Fourteenth,
    Fifteenth,
    end
};

#endif  // ENUMCLASS_H