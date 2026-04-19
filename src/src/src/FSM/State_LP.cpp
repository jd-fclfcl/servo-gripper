/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/State_LP.h"
State_LP::State_LP()
    : FSMState(FSMStateName::LEFTPUT, "leftput") {}
void State_LP::enter()
{
    Flag = StateFlag::start;
}

void State_LP::run()
{
    switch (Flag)
    {
    case StateFlag::start:

        delay(100);
        Flag = StateFlag::down;
        break;
    case StateFlag::down:
        value[0] = 200;
        value[1] = 110;   
        delay(1000);
        Flag = StateFlag::relax;
    break;

    case StateFlag::relax:
        value[0] = 200;
        value[1] = 60;   
        delay(1000);
        Flag = StateFlag::back;
        break;

    case StateFlag::back:
        value[0] = 40;
        value[1] = 0;   
        delay(1000);
        Flag = StateFlag::keep;
        break;

    case StateFlag::keep:
        value[0] = 40;
        value[1] = 0;   
        Flag = StateFlag::keep;
        break;

    }
}

void State_LP::exit(){
    Flag = StateFlag::end;
    value[0] = 40;
    value[1] = 0;
}

FSMStateName State_LP::checkChange(){
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