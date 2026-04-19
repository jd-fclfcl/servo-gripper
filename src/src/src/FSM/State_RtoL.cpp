/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/State_RtoL.h"
State_RtoL::State_RtoL()
                :FSMState(FSMStateName::RIGHTPUTLEFTGET, "rightputleftget"){}
void State_RtoL::enter(){
}

void State_RtoL::run(){
    
}

void State_RtoL::exit(){
}

FSMStateName State_RtoL::checkChange(){
    if(userCmd == UserCommand::LEFTGET){
        return FSMStateName::LEFTGET;
    }
    else if(userCmd == UserCommand::RIGHTGET){
        return FSMStateName::RIGHTGET;
    }
     else if(userCmd == UserCommand::RIGHTPUT){
        return FSMStateName::RIGHTPUT;
    }
     else if(userCmd == UserCommand::LEFTPUTRIGHTGET){
        return FSMStateName::LEFTPUTRIGHTGET;
    }
     else if(userCmd == UserCommand::LEFTPUT){
        return FSMStateName::LEFTPUT;
    }
        else if(userCmd == UserCommand::END){
        return FSMStateName::END;
    }
    else{
        return FSMStateName::RIGHTPUTLEFTGET;
    }
}