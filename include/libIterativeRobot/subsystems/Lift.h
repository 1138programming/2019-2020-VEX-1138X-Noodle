#ifndef _SUBSYSTEMS_ARM_H_
#define _SUBSYSTEMS_ARM_H_

#include "./Subsystem.h"
#include "api.h"

class Claw : public libIterativeRobot::Subsystem {
  private:
    // Claw motors
    Motor* clawMotor;

    PIDController* clawController;

    pros::ADIDigitalIn* bumper;

  public:
    void initDefaultCommand();
    void move(int speed);
    void setSetpoint(int setpoint);
    bool atSetpoint();
    void loop();
    void lock();
    void disablePID();
    void enablePID();
    Claw();
};

#endif // _SUBSYSTEMS_ARM_H_
