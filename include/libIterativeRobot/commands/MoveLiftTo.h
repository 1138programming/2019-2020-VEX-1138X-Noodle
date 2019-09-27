#ifndef _COMMANDS_MOVEARMTO_H_
#define _COMMANDS_MOVEARMTO_H_

#include "libIterativeRobot/commands/Command.h"

class MoveClawTo: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    MoveClawTo(int target);
  private:
    int target = 0;
};

#endif // _COMMANDS_MOVEARMTO_H_
