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
    BaseLinearMovement(double leftTarget, double rightTarget);
    BaseLinearMovement(double leftTarget, double rightTarget, double maxVel, double maxAccel);
    BaseLinearMovement(double leftTarget, double rightTarget, bool absolute);
    BaseLinearMovement(double leftTarget, double rightTarget, double maxVel, double maxAccel, bool absolute);
  private:
    double leftTarget;
    double rightTarget;
    double maxVel;
    double maxAccel;
    bool absolute;
};

#endif //_BASELINEARMOVEMENT_H_
