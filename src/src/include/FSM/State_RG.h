/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef RG_H
#define RG_H

#include "FSMState.h"

class State_RG: public FSMState{
public:
    State_RG();
    void enter();
    void run();
    void exit();
    FSMStateName checkChange();
};

#endif  // RG_H