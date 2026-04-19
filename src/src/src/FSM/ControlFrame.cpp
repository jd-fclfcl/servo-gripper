/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/ControlFrame.h"
#include "keyboard/KeyBoard.h"

// void setonce(std::string s){for(int i(0); i<1; i++) std::cout << "s" << std::endl;}

/* fcl ***********************************************************************/

#include "FSM/ControlFrame.h"
#include "keyboard/KeyBoard.h"
#include <iostream>
#include <string>

void setonce(const char* s) {
    for(int i(0); i<1; i++)
    std::cout << s << std::endl;
}

ControlFrame::ControlFrame(){
    _FSMController = new FSM();
    cmdPanel = new KeyBoard();
    commandSource = new Command();
}

void ControlFrame::run(bool i){
    _FSMController->run();
    if(!i) {
        setonce("keyboard");
    } else {
        commandSource->run();
        setonce("autoself");
    }
}