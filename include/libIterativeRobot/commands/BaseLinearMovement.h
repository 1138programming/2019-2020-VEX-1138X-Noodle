#ifndef _BASELINEARMOVEMENT_H_
#define _BASELINEARMOVEMENT_H_

#include "libIterativeRobot/commands/Command.h"

class BaseLinearMovement : public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    BaseLinearMovement(int leftTarget, int rightTarget, bool absolute = false);
  private:
    int leftTarget;
    int rightTarget;
    bool absolute;
};

#endif //_BASELINEARMOVEMENT_H_
