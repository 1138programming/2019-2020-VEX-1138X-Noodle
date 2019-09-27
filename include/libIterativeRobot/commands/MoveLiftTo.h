#ifndef _COMMANDS_MOVELIFTTO_H_
#define _COMMANDS_MOVELIFTTO_H_

#include "libIterativeRobot/commands/Command.h"

class MoveLiftTo: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    MoveLiftTo(int target);
  private:
    int target = 0;
};

#endif // _COMMANDS_MOVELIFTTO_H_
