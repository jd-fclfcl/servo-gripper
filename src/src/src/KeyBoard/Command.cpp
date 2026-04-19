#include "keyboard/Command.h"

UserCommand Command::checkCmd()
{
   
    switch (count)
    {
    default:
        return UserCommand::NONE;
    }
}

void Command::run()
{
    userCmd = checkCmd();
}