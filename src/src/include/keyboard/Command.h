/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef COMMAND_H
#define COMMAND_H

#include "common/enumClass.h"
#include <pthread.h>





class Command{
public:
    Command(): userCmd(UserCommand::NONE){}
    ~Command(){}
    UserCommand getUserCmd(){return userCmd;}
    UserCommand checkCmd();
    void run();
       
    
protected:
    UserCommand userCmd;
    int count;
};


#endif  // COMMAND_H