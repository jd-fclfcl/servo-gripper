/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef CMDPANEL_H
#define CMDPANEL_H

#include "common/enumClass.h"
#include <pthread.h>



struct UserValue{
    float lx;
    float ly;
    float rx;
    float ry;
    float FH;
    float FLAG;

    UserValue(){
        setZero();
    }
    void setZero(){
        lx = 0;
        ly = 0;
        rx = 0;
        ry = 0;
        FH=0;
        FLAG=0;
    }
};

class CmdPanel{
public:
    CmdPanel(){}
    virtual ~CmdPanel(){}
    UserCommand getUserCmd(){return userCmd;}
    UserValue getUserValue(){return userValue;}
    void setPassive(){userCmd = UserCommand::NONE;}
    void setZero(){userValue.setZero();}
   // virtual void receiveHandle(UNITREE_LEGGED_SDK::LowState *lowState){}; // COMPILE_WITH_REAL_ROBOT
protected:
    virtual void* run(void *arg){return NULL;}
    UserCommand userCmd;
    UserValue userValue;
};

#endif  // CMDPANEL_H