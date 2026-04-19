/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/State_LG.h"
State_LG::State_LG()
                :FSMState(FSMStateName::LEFTGET, "leftget"){}
void State_LG::enter(){
    Flag = StateFlag::start;
}

void State_LG::run(){
    switch (Flag)
    {
    case StateFlag::start:
        
        /* code */
        // delay(100);
        Flag = StateFlag::down;

        break;
    case StateFlag::down:
        value[0] = 200;
        value[1] = 0;   
        /* code */
        delay(3000);
        Flag = StateFlag::grip;
        break;
    case StateFlag::grip:
        value[0] = 200;
        value[1] = 110;   
        /* code */
        delay(3000);
        Flag = StateFlag::up;
        break;
    case StateFlag::up:
        value[0] = 90;
        value[1] = 110;   
        /* code */
        delay(1000);
        Flag = StateFlag::keep;
        break;
    case StateFlag::keep:
        value[0] = 90;
        value[1] = 110;   
        Flag = StateFlag::keep;
    }
}

void State_LG::exit(){
    Flag = StateFlag::end;
    value[0] = 90;
    value[1] = 110;   
}

FSMStateName State_LG::checkChange(){
    if(userCmd == UserCommand::LEFTPUT){
        return FSMStateName::LEFTPUT;
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