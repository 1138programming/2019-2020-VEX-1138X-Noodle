#ifndef _COMMANDS_MOVELIFTFOR_H_
#define _COMMANDS_MOVELIFTFOR_H_

#include "libIterativeRobot/commands/Command.h"

class MoveLiftFor: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    MoveLiftFor(unsigned int duration, int speed = 127);
  private:
    unsigned int duration;
    unsigned int speed;
    unsigned int startTime;
};

#endif // _COMMANDS_MOVELIFTFOR_H_
