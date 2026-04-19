/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef RP_H
#define RP_H

#include "FSMState.h"

class State_RP: public FSMState{
public:
    State_RP();
    void enter();
    void run();
    void exit();
    FSMStateName checkChange();
};

#endif  // RP_H