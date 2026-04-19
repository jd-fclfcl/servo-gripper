/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef CONTROLFRAME_H
#define CONTROLFRAME_H
#include "keyboard/CmdPanel.h"
#include "FSM/FSM.h"

extern CmdPanel *cmdPanel;

class ControlFrame{
public:
	ControlFrame();
	~ControlFrame(){
		delete _FSMController;
		delete cmdPanel;
	}
	void run();
private:
	FSM* _FSMController;

};

#endif  //CONTROLFRAME_H