/**********************************************************************                                   
fcl ***********************************************************************/
#ifndef FSM_H
#define FSM_H

// FSM States
#include "FSM/FSMState.h"
#include "common/enumClass.h"
#include "FSM/State_LP.h"
#include "FSM/State_RG.h"
#include "FSM/State_RP.h"
#include "FSM/State_LG.h"
#include "FSM/State_LtoR.h"
#include "FSM/State_RtoL.h"

struct FSMStateList{
    FSMState *invalid;
    FSMState *leftput;
    FSMState *rightput;
    FSMState *leftget;
    FSMState *rightget;
    FSMState *leftputrightget;
    FSMState *rightputleftget;
    void deletePtr(){
     delete invalid;    
     delete leftput;
     delete rightput;
     delete leftget;
     delete rightget;
     delete leftputrightget;
     delete rightputleftget;

    }
};

class FSM{
public:
    FSM();
    ~FSM();
    void initialize();
    void run();

private:
    FSMState* getNextState(FSMStateName stateName);//状态切换器：根据状态枚举值返回对应的状态对象指针（如传入 TROTTING 返回行走状态对象）
    FSMState *_currentState;//当前状态：指向正在执行的状态对象（如指向 State_Trotting 表示处于行走状态）
    FSMState *_nextState;//待切换状态：在状态迁移过程中暂存目标状态对象（用于平滑过渡）
    FSMStateName _nextStateName;//下一状态标识：存储将要切换到的状态枚举值（如 FREESTAND 表示即将进入自由站立）
    FSMStateList _stateList;//状态容器：预创建所有状态实例的对象池（包含被动/站立/行走等具体状态）
    FSMMode _mode;//状态机模式：标记当前是 NORMAL（正常执行）还是 CHANGE（正在切换状态）
    long long _startTime;//周期计时器：记录每次控制循环开始的时间戳（用于保障 500Hz 的精确周期）

    int count;
};


#endif  // FSM_H