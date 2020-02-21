#ifndef _SUBSYSTEMS_PIDCONTROLLER_H_
#define _SUBSYSTEMS_PIDCONTROLLER_H_

#include "Motor.h"
#include <vector>
#include <limits>
#include "abstractBaseClasses/IntegralType.h"

class PIDController {
  private:
    double setpoint = 0; // Setpoint to get to
    double setpointTolerance = 15; // Default value of the threshold for the error at the setpoint
    // PID constants
    double kP = 0;
    double kI = 0;
    double kD = 0;
    double kF = 0;
    // Integers to hold the error, integal, and derivative value of the loop
    double error = 0;
    double lastError = 0;
    double integral = 0;
    double velocityError = 0;
    double velocityTolerance = 0.05;
    double minOutput = -KMaxMotorSpeed; // Default is -KMaxMotorSpeed
    double maxOutput = KMaxMotorSpeed; // Default is KMaxMotorSpeed
    double outputDeadband = 0;
    double outputDeadbandTolerance = 0;
    double measurement = 0; // If no motor is given, this must be set manually
    double output = 0; // Output of the PID loop
    int deltaTime = 0; // Time between loops
    int lastTime = 0; // Time recorded in the last loop
    // Vector to hold past error values, and other variables to hold the index of the last error value and the number of past error values to record
    int integralWindow = 1;
    std::vector<double>* errorCache;
    int oldestErrorIndex = 0;
    IntegralType integralType = IntegralType::Default;
    bool integralZone = false;
    double integralZoneRange = 0;
    double maxIntegral = std::numeric_limits<double>::max();
    double minIntegral = std::numeric_limits<double>::min();
  public:
    PIDController(double kP, double kI, double kD, double kF); // Initializes a PID controller with a motor
    PIDController(double kP, double kI, double kD); // Initializes a PID controller without a motor
    void setP(double kP); // Sets P value
    void setI(double kI); // Sets I value
    void setD(double kD); // Sets D value
    void setF(double kF); // Sets D value
    void setGains(double kP, double kI, double kD, double kF);
    void setGains(double kP, double kI, double kD);
    double getP();
    double getI();
    double getD();
    double getF();
    void setSetpoint(double setpoint); // Sets the setpoint to the given value
    void setSetpointRelative(double setpoint); // Adds the given value to the setpoint
    double getSetpoint(); // Returns the current setpoint
    bool atSetpoint(); // Returns if the PID loop has reached the setpoint
    void setTolerance(double setpointTolerance, double velocityTolerance);
    double getError();
    double getVelocityError();
    double getErrorIntegral();
    void setOutputRange(double minOutput, double maxInput);
    void setIntegralRange(double minIntegral, double maxIntegral);
    void setOutputDeadband(double deadband, double tolerance);
    void configIntegral(IntegralType integralType, bool integralZone);
    void setIntegralZoneRange(double integralZoneRange);
    void setIntegralWindowLength(int integralWindow);
    double calculate(double measurement); // Does all calculations
    void reset();
};

#endif
