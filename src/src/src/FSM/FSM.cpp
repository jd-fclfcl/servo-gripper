/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/FSM.h"
#include <iostream>

FSM::FSM(){

    _stateList.invalid = nullptr;
    initialize();
}


FSM::~FSM(){
    _stateList.deletePtr();
}

void FSM::initialize(){
    _currentState = _stateList.invalid;
    _currentState -> enter();
    _nextState = _currentState;
    _mode = FSMMode::NORMAL;
}

void FSM::run()
{
  
  

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
    default:
        return _stateList.invalid;
        break;
        
    }
}

