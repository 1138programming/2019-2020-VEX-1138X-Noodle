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
    MoveAnglerTo(int target, int maxSpeed);
    MoveAnglerTo(int target, int maxSpeed, int duration);
  private:
    int target = 0;
    int duration;
    int maxSpeed;
    int startTime;
};

#endif // _COMMANDS_MOVEANGLERTO_H_
