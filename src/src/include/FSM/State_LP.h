/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef LP_H
#define LP_H

#include "FSMState.h"

class State_LP: public FSMState{
public:
    State_LP();
    void enter();
    void run();
    void exit();
    FSMStateName checkChange();
};

#endif  // LP_H