/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/State_LtoR.h"
State_LtoR::State_LtoR()
                :FSMState(FSMStateName::LEFTPUTRIGHTGET, "leftputrightget"){}
void State_LtoR::enter(){
}

void State_LtoR::run(){
    
}

void State_LtoR::exit(){
}

FSMStateName State_LtoR::checkChange(){
    if(userCmd == UserCommand::LEFTGET){
        return FSMStateName::LEFTGET;
    }
        else if(userCmd == UserCommand::END){
        return FSMStateName::END;
    }
    else if(userCmd == UserCommand::RIGHTGET){
        return FSMStateName::RIGHTGET;
    }
     else if(userCmd == UserCommand::RIGHTPUT){
        return FSMStateName::RIGHTPUT;
    }
     else if(userCmd == UserCommand::LEFTPUT){
        return FSMStateName::LEFTPUT;
    }
     else if(userCmd == UserCommand::RIGHTPUTLEFTGET){
        return FSMStateName::RIGHTPUTLEFTGET;
    }
    else{
        return FSMStateName::LEFTPUTRIGHTGET;
    }
}