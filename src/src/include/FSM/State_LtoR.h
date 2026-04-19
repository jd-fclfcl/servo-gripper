/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef LtoR_H
#define LtoR_H

#include "FSMState.h"

class State_LtoR: public FSMState{
public:
    State_LtoR();
    void enter();
    void run();
    void exit();
    FSMStateName checkChange();
};

#endif  // LtoR_H