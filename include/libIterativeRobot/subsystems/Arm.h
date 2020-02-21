#ifndef _SUBSYSTEMS_ARM_H_
#define _SUBSYSTEMS_ARM_H_

#include "./Subsystem.h"
#include "abstractBaseClasses/PIDController.h"
#include "api.h"

class Arm : public libIterativeRobot::Subsystem {
  private:
    Motor* armMotor;
    PIDController* armController;
    pros::ADIDigitalIn* bumper1;
    pros::ADIDigitalIn* bumper2;
  public:
    static const double kLowTowerPos;
    static const double kMidTowerPos;

    void initDefaultCommand();
    void move(int speed);
    double getSensorValue();
    void setSetpoint(double setpoint);
    void lock();
    double getSetpoint();
    void calculate();
    bool atSetpoint();
    void resetPID();
    Arm();
};

#endif // _SUBSYSTEMS_ARM_H_
