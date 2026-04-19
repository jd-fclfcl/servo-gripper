/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/State_LP.h"
State_LP::State_LP()
                :FSMState(FSMStateName::LEFTPUT, "leftput"){}
void State_LP::enter(){
}

void State_LP::run(){
    
}

void State_LP::exit(){
}

FSMStateName State_LP::checkChange(){
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
     else if(userCmd == UserCommand::RIGHTPUTLEFTGET){
        return FSMStateName::RIGHTPUTLEFTGET;
    }
    else{
        return FSMStateName::LEFTPUT;
    }
}