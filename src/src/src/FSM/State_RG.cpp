/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/State_RG.h"
State_RG::State_RG()
                :FSMState(FSMStateName::RIGHTGET, "rightget"){}
void State_RG::enter(){
}

void State_RG::run(){
    
}

void State_RG::exit(){
}

FSMStateName State_RG::checkChange(){
    if(userCmd == UserCommand::LEFTGET){
        return FSMStateName::LEFTGET;
    }
    else if(userCmd == UserCommand::LEFTPUT){
        return FSMStateName::LEFTPUT;
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
        return FSMStateName::RIGHTGET;
    }
}