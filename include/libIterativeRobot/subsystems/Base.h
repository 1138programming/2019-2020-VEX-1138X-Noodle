#ifndef _SUBSYSTEMS_BASE_H_
#define _SUBSYSTEMS_BASE_H_

#include "./Subsystem.h"
#include "abstractBaseClasses/LinearProfiler.h"
#include "api.h"

class Base : public libIterativeRobot::Subsystem {
  private:
    // Base motors
    Motor* frontLeftMotor;
    Motor* frontRightMotor;
    Motor* backLeftMotor;
    Motor* backRightMotor;

    LinearProfiler* leftProfiler;
    LinearProfiler* rightProfiler;

    pros::Imu* imu;
  public:
    static const double kDefaultMaxAccel;
    static const double kDefaultMaxVel;

    void initDefaultCommand();
    void move(int leftSpeed, int rightSpeed);
    double getLeftSensorValue();
    double getRightSensorValue();
    double getHeading();
    void zeroEncoders();
    void setLinearTarget(double leftTarget, double rightTarget);
    void setLinearTargetRelative(double leftTarget, double rightTarget);
    void initLinearMovement();
    void calculateLinearMovement();
    bool atLinearTarget();
    void setMaxVel(double maxVel);
    void setMaxAccel(double maxAccel);
    LinearProfiler* getLeftProfiler();
    LinearProfiler* getRightProfiler();
    Base();
};

#endif // _SUBSYSTEMS_BASE_H_
