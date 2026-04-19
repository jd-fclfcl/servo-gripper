/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef LG_H
#define LG_H

#include "FSMState.h"

class State_LG: public FSMState{
public:
    State_LG();
    void enter();
    void run();
    void exit();
    FSMStateName checkChange();
};

#endif  // LG_H