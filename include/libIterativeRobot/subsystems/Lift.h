#ifndef _SUBSYSTEMS_ARM_H_
#define _SUBSYSTEMS_ARM_H_

#include "./Subsystem.h"
#include "api.h"

class Lift : public libIterativeRobot::Subsystem {
  private:
    // Lift motors
    Motor* leftLiftMotor;
    Motor* rightLiftMotor;

    PIDController* leftLiftController;
    PIDController* rightLiftController;

    pros::ADIDigitalIn* leftLiftBumper;
    pros::ADIDigitalIn* rightLiftBumper;

  public:
    void initDefaultCommand();
    void move(int speed);
    void setSetpoint(int setpoint);
    bool atSetpoint();
    void loop();
    void lock();
    void disablePID();
    void enablePID();
    Lift();
};

#endif // _SUBSYSTEMS_ARM_H_
