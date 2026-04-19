/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/FSM.h"
#include "FSM/State_LP.h"
#include "FSM/State_RG.h"
#include "FSM/State_RP.h"
#include "FSM/State_LG.h"
#include "FSM/State_LtoR.h"
#include "FSM/State_RtoL.h"
#include <iostream>

class InvalidState : public FSMState {
public:
    InvalidState() : FSMState(FSMStateName::INVALID, "invalid") {}
    void enter() override {}
    void run() override {}
    void exit() override {}
    FSMStateName checkChange() override { return FSMStateName::INVALID; }
};

FSM::FSM(){
    _stateList.invalid = new InvalidState();
    _stateList.leftput = new State_LP();
    _stateList.rightput = new State_RP();
    _stateList.leftget = new State_LG();
    _stateList.rightget = new State_RG();
    _stateList.leftputrightget = new State_LtoR();
    _stateList.rightputleftget = new State_RtoL();
    _stateList.end = new State_END(); // Assuming you have an END state

    initialize();
}


FSM::~FSM(){
    _stateList.deletePtr();
}

void FSM::initialize(){
    _currentState = _stateList.end;
    _currentState -> enter();
    _nextState = _currentState;
    _mode = FSMMode::NORMAL;
}

void FSM::run()
{
  
//   std::cout << "当前状态: " << _currentState->_stateNameString << std::endl;

    if (_mode == FSMMode::NORMAL)
    {
      
        _currentState->run();
        _nextStateName = _currentState->checkChange();
        if (_nextStateName != _currentState->_stateName)
        {
            _mode = FSMMode::CHANGE;
            _nextState = getNextState(_nextStateName);
            std::cout << "Switched from " << _currentState->_stateNameString
                      << " to " << _nextState->_stateNameString << std::endl;
        }
    }
    else if(_mode == FSMMode::CHANGE){
        _currentState->exit();
        _currentState = _nextState;
        _currentState->enter();
        _mode = FSMMode::NORMAL;
        _currentState->run();
    }

}

FSMState* FSM::getNextState(FSMStateName stateName){
    switch (stateName)
    {

    case FSMStateName::INVALID:
        return _stateList.invalid;
        break;
    case FSMStateName::LEFTPUT:
        return _stateList.leftput;
        break;
    case FSMStateName::RIGHTPUT:
        return _stateList.rightput;
        break;
    case FSMStateName::LEFTGET:
        return _stateList.leftget;
        break;
    case FSMStateName::RIGHTGET:
        return _stateList.rightget;
        break;
    case FSMStateName::LEFTPUTRIGHTGET:
        return _stateList.leftputrightget;
        break;
    case FSMStateName::RIGHTPUTLEFTGET:
        return _stateList.rightputleftget;
        break;
    case FSMStateName::END:
        return _stateList.end;
        break;
    default:
        return _stateList.invalid;
        break;
        
    }
}

