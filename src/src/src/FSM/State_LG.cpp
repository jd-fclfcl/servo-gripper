/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/State_LG.h"
State_LG::State_LG()
                :FSMState(FSMStateName::LEFTGET, "leftget"){}
void State_LG::enter(){
    Flag = StateFlag::staticFlag;
}

void State_LG::run(){
    switch (Flag)
    {
    case StateFlag::staticFlag:
        value[0] = 1;
        value[1] = 0;   
        value[2] = 0;
        value[3] = 0;
        /* code */
        break;
    
    default:
        break;
    }




}

void State_LG::exit(){
    Flag = StateFlag::end;
}

FSMStateName State_LG::checkChange(){
    if(userCmd == UserCommand::LEFTPUT){
        return FSMStateName::LEFTPUT;
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
        return FSMStateName::LEFTGET;
    }
}