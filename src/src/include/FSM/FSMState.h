/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef FSMSTATE_H
#define FSMSTATE_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <array>

#include "cstdio"
#include "vector"
#include "common/enumClass.h"
#include "common/usercmd.h"
///////////////////////////////////////////////
extern std::array<int32_t, 4> value;



///////////////////////////////////////////////
class FSMState{
public:
    FSMState(FSMStateName stateName, std::string stateNameString);

    virtual void enter() = 0;
    virtual void run() = 0;
    virtual void exit() = 0;
    virtual FSMStateName checkChange() {return FSMStateName::INVALID;}
    
    FSMStateName _stateName;
    std::string _stateNameString;
protected:
    FSMStateName _nextStateName;
    StateFlag  Flag;

 
};

#endif  // FSMSTATE_H