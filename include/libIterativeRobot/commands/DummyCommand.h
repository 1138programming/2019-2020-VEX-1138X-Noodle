#ifndef _COMMANDS_DUMMYCOMMAND_H_
#define _COMMANDS_DUMMYCOMMAND_H_

#include "libIterativeRobot/commands/Command.h"

class DummyCommand : public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    DummyCommand();
};

#endif // _COMMANDS_DUMMYCOMMAND_H_
