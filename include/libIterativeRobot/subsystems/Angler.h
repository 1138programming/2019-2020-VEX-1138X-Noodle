#ifndef _SUBSYSTEMS_ANGLER_H_
#define _SUBSYSTEMS_ANGLER_H_

#include "./Subsystem.h"
#include "api.h"

class Angler : public libIterativeRobot::Subsystem {
  private:
    // Angler motors
    Motor* anglerMotor;

    PIDController* anglerController;

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
    Angler();
};

#endif // _SUBSYSTEMS_ANGLER_H_
