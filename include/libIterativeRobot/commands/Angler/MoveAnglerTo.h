#ifndef _COMMANDS_MOVEANGLERTO_H_
#define _COMMANDS_MOVEANGLERTO_H_

#include "libIterativeRobot/commands/Command.h"

class MoveAnglerTo: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    MoveAnglerTo(int target);
    MoveAnglerTo(int target, int duration);
  private:
    int target = 0;
    int duration;
    int startTime;
};

#endif // _COMMANDS_MOVEANGLERTO_H_
