/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/State_RP.h"
State_RP::State_RP()
                :FSMState(FSMStateName::RIGHTPUT, "rightput"){}
void State_RP::enter(){
}

void State_RP::run(){
    
}

void State_RP::exit(){
}

FSMStateName State_RP::checkChange(){
    if(userCmd == UserCommand::LEFTGET){
        return FSMStateName::LEFTGET;
    }
    else if(userCmd == UserCommand::RIGHTGET){
        return FSMStateName::RIGHTGET;
    }
     else if(userCmd == UserCommand::LEFTPUT){
        return FSMStateName::LEFTPUT;
    }
     else if(userCmd == UserCommand::LEFTPUTRIGHTGET){
        return FSMStateName::LEFTPUTRIGHTGET;
    }
     else if(userCmd == UserCommand::RIGHTPUTLEFTGET){
        return FSMStateName::RIGHTPUTLEFTGET;
    }
    else{
        return FSMStateName::RIGHTPUT;
    }
}