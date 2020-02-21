#ifndef _COMMANDS_TUNELINEARPROFILE_H_
#define _COMMANDS_TUNELINEARPROFILE_H_

#include "libIterativeRobot/commands/Command.h"
#include "libIterativeRobot/subsystems/Subsystem.h"
#include "abstractBaseClasses/LinearProfiler.h"
#include "abstractBaseClasses/Motor.h"
#include <vector>
#include <cmath>

class TuneLinearProfile: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    TuneLinearProfile(LinearProfiler* profiler, const double* motorData, Motor* motor, int target);
  private:
    LinearProfiler* profiler;
    const double* motorData;
    Motor* motor;
    int target;

    double learning_rate = 0.00001;

    double dP = 0;
    double dI = 0;
    double dD = 0;

    int error = 0;
    int lastError = 0;
    double accError = 0;
    double dError = 0;
    int lastVoltage = 0;

    int loss = 0;

    //std::vector<int> dt; // Time between each loop
    //std::vector<int> z; // Voltage given by the PID after each loop
    //std::vector<int> x; // Positions
    //std::vector<int> error; // Setpoint - position
    //std::vector<double> acc; // Accumulated error
    //std::vector<double> deriv; // Derivative of the error

    void adjustConstants();
    double deltaMotor(const double* data, int voltage);
};

#endif // _COMMANDS_TUNELINEARPROFILE_H_
