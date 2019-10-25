#ifndef _SUBSYSTEMS_ARM_H_
#define _SUBSYSTEMS_ARM_H_

#include "./Subsystem.h"
#include "abstractBaseClasses/PIDController.h"
#include "api.h"

class Arm : public libIterativeRobot::Subsystem {
  private:
    Motor* armMotor;
    PIDController* armController;
  public:
    static const int lowTowerPos = 2500;
    static const int midTowerPos = 3000;

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
