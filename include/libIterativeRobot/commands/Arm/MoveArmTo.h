#ifndef _COMMANDS_MOVEARMTO_H_
#define _COMMANDS_MOVEARMTO_H_

#include "libIterativeRobot/commands/Command.h"

class MoveArmTo: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    MoveArmTo(int target);
    MoveArmTo(int target, unsigned int duration);
  private:
    int target = 0;
    unsigned int duration;
    unsigned int startTime;
};

#endif // _COMMANDS_MOVEARMTO_H_
