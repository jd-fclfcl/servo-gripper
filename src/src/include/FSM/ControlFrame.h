/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef CONTROLFRAME_H
#define CONTROLFRAME_H
#include "keyboard/CmdPanel.h"
#include "keyboard/Command.h"
#include "FSM/FSM.h"


class ControlFrame{
public:
	ControlFrame();
	~ControlFrame(){
		delete _FSMController;
		delete cmdPanel;
		delete commandSource;
	}
	void run(bool i);
private:
	FSM* _FSMController;
public:
   CmdPanel *cmdPanel;
   Command *commandSource;
};

#endif  //CONTROLFRAME_H