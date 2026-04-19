/**********************************************************************                                   
fcl ***********************************************************************/
#include "FSM/FSMState.h"

UserCommand userCmd = UserCommand::NONE;
std::array<int32_t, 4> value = {0, 0, 0, 0};

FSMState::FSMState(FSMStateName stateName, std::string stateNameString)
    : _stateName(stateName),
      _stateNameString(stateNameString),
      _nextStateName(FSMStateName::INVALID),
      Flag(StateFlag::end) {}
