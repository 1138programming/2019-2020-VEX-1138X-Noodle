#ifndef _COMMANDS_ARMCONTROL_H_
#define _COMMANDS_ARMCONTROL_H_

#include "libIterativeRobot/commands/Command.h"

class ClawControl: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    ClawControl(bool Up);
  private:
    bool Up;
};

#endif // _COMMANDS_ARMCONTROL_H_
