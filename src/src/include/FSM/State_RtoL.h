/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef RtoL_H
#define RtoL_H

#include "FSMState.h"

class State_RtoL: public FSMState{
public:
    State_RtoL();
    void enter();
    void run();
    void exit();
    FSMStateName checkChange();
};

#endif  // RtoL_H