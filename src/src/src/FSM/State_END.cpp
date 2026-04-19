/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/State_END.h"
State_END::State_END()
                :FSMState(FSMStateName::END, "end"){}
void State_END::enter(){
    Flag = StateFlag::end;
}

void State_END::run(){
    // if(userCmd == UserCommand::command){
    //    Flag == StateFlag::another;    
    // }
    if(Flag == StateFlag::end){
        value[0] = 40;
        value[1] = 0;
        value[2] = 0;
        value[3] = 0;
    }
    // else if(Flag == StateFlag::another){
    //     // value[0] = 0;
    //     // value[1] = 0;
    //     // value[2] = 0;
    //     // value[3] = 0;
    // }
}

void State_END::exit(){
    Flag = StateFlag::end;
}

FSMStateName State_END::checkChange(){
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
      else if(userCmd == UserCommand::LEFTGET){
        return FSMStateName::LEFTGET;
    }
    else{
        return FSMStateName::END;
    }
}