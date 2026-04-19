/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/ControlFrame.h"

CmdPanel *cmdPanel = nullptr;

ControlFrame::ControlFrame(){
    _FSMController = new FSM();
    cmdPanel = new CmdPanel();
}

void ControlFrame::run(){
    _FSMController->run();
}