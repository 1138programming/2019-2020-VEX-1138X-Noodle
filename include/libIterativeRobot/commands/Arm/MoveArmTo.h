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
    MoveArmTo(double target);
    MoveArmTo(double target, int duration);
  private:
    double target = 0;
    int duration;
    int startTime;
};

#endif // _COMMANDS_MOVEARMTO_H_
