/**********************************************************************                                   
fcl ***********************************************************************/
#include "keyboard/KeyBoard.h"
#include <iostream>

KeyBoard::KeyBoard(){
    userCmd = UserCommand::NONE;
    userValue.setZero();

    tcgetattr( fileno( stdin ), &_oldSettings );
    _newSettings = _oldSettings;
    _newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr( fileno( stdin ), TCSANOW, &_newSettings );
//   std::cout << "KeyBoard init" << std::endl;
    pthread_create(&_tid, NULL, runKeyBoard, (void*)this);
}

KeyBoard::~KeyBoard(){
    pthread_cancel(_tid);
    pthread_join(_tid, NULL);
    tcsetattr( fileno( stdin ), TCSANOW, &_oldSettings );
}

UserCommand KeyBoard::checkCmd()
{
    switch (_c)
    {
    case '0':
        return UserCommand::END;
    case '1':
        return UserCommand::LEFTGET;
    case '2':
        return UserCommand::LEFTPUT;
    case '3':
        return UserCommand::LEFTPUTRIGHTGET;
    case '4':
        return UserCommand::RIGHTGET;
    case '5':
        return UserCommand::RIGHTPUT;
    case '6':
        return UserCommand::RIGHTPUTLEFTGET;

   

    case ' ':
        userValue.setZero();
        return UserCommand::NONE;
    default:
        return UserCommand::NONE;
    }
}

void KeyBoard::changeValue(){
    switch (_c){
    case 'w':case 'W':
        userValue.ly = min<float>(userValue.ly+sensitivityLeft, 1.0);
        break;
    case 's':case 'S':
        userValue.ly = max<float>(userValue.ly-sensitivityLeft, -1.0);
        break;
    case 'd':case 'D':
        userValue.lx = min<float>(userValue.lx+sensitivityLeft, 1.0);
        break;
    case 'a':case 'A':
        userValue.lx = max<float>(userValue.lx-sensitivityLeft, -1.0);
        break;

    case 'i':case 'I':
        userValue.ry = min<float>(userValue.ry+sensitivityRight, 1.0);
        break;
    case 'k':case 'K':
        userValue.ry = max<float>(userValue.ry-sensitivityRight, -1.0);
        break;
    case 'l':case 'L':
        userValue.rx = min<float>(userValue.rx+sensitivityRight, 1.0);
        break;
    case 'j':case 'J':
        userValue.rx = max<float>(userValue.rx-sensitivityRight, -1.0);
        break;

    case 'p':case 'P':
        userValue.rx=  0;
        break;
    case 'o': case 'O':
        userValue.lx = 0;
        break;
        case 'q': case 'Q':
        userValue.ly=0;
        break;

    case 'h':
    case 'H':
        userValue.FH = min<float>(userValue.FH + sensitivityRight, 1.0);
        break;
    case 'f':
    case 'F':
        userValue.FH = max<float>(userValue.FH - sensitivityRight, -1.0);
        break;
    case 'x':
    case 'X':
    userValue.FLAG = max<float>(userValue.FH - sensitivityRight, -1.0);

    default:
        break;
    }
}

void* KeyBoard::runKeyBoard(void *arg){
    ((KeyBoard*)arg)->run(NULL);
    return NULL;
}

void* KeyBoard::run(void *arg){
    while(1){

        FD_ZERO(&set);
        //   std::cout << "KeyBoard init" << std::endl;

        FD_SET( fileno( stdin ), &set );

        res = select( fileno( stdin )+1, &set, NULL, NULL, NULL);

        if(res > 0){
            ret = read( fileno( stdin ), &_c, 1 );
            userCmd = checkCmd();
            if(userCmd == UserCommand::NONE)
                changeValue();
            _c = '\0';
            // std::cout << "按键命令: " << static_cast<int>(userCmd) << std::endl;
            // std::cout << "方向值: lx=" << userValue.lx 
            // << " ly=" << userValue.ly 
            // << " rx=" << userValue.rx 
            // << " ry=" << userValue.ry << std::endl;
        }
        usleep(1000);
    }
    return NULL;
}