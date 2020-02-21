#ifndef _SUBSYSTEMS_ANGLER_H_
#define _SUBSYSTEMS_ANGLER_H_

#include "./Subsystem.h"
#include "api.h"

class Angler : public libIterativeRobot::Subsystem {
  private:
    // Angler motor
    Motor* anglerMotor;

    PIDController* anglerController;

  public:
    static const double kCollectingPosition;

    void initDefaultCommand();
    void move(int speed);
    void encoderReset();
    double getSensorValue();
    void setSetpoint(double setpoint);
    void lock();
    void calculate();
    bool atSetpoint();
    void resetPID();
    void setMaxSpeed(int maxSpeed);
    Angler();
};

#endif // _SUBSYSTEMS_ANGLER_H_
