/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef END_H
#define END_H

#include "FSMState.h"

class State_END: public FSMState{
public:
    State_END();
    void enter();
    void run();
    void exit();
    FSMStateName checkChange();
};

#endif  // END_H