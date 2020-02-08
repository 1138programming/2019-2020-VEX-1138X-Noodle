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
    static const int kLowTowerPos = 2500;
    static const int kMidTowerPos = 3000;

    void initDefaultCommand();
    void move(int speed);
    int getSensorValue();
    int getSetpointValue();
    void setSetpoint(int setpoint);
    bool atSetpoint();
    void loop();
    void lock();
    void disablePID();
    void enablePID();
    Arm();
};

#endif // _SUBSYSTEMS_ARM_H_
