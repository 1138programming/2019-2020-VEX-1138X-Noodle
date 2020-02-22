#ifndef _RotateBase_H_
#define _RotateBase_H_

#include "libIterativeRobot/commands/Command.h"

class RotateBase : public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    RotateBase(double rotationTarget);
    RotateBase(double rotationTarget, double slewRate);
    RotateBase(double rotationTarget, double slewRate, int maxSpeed);
    RotateBase(double rotationTarget, double slewRate, int maxSpeed, int duration);
  private:
    double rotationTarget;
    double slewRate;
    int maxSpeed;
    int duration;
    int startTime;
};

#endif //_RotateBase_H_
