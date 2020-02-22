#ifndef LINEARPROFILER_H_
#define LINEARPROFILER_H_

#include "abstractBaseClasses/PIDController.h"
#include "abstractBaseClasses/Motor.h"
#include "abstractBaseClasses/IntegralType.h"
#include <limits>

class LinearProfiler {
  private:
    PIDController* posPID; // Internal position PID

    std::uint32_t lastTime = 0;

    double lastPos = 0; // Last position measurement
    double lastVel = 0; // Last velocity measurement

    double vel = 0;
    double accel = 0;

    double dt = 0;

    double measurement; // Current position measurement

    double maxAccel = 1;
    double maxVel = std::numeric_limits<double>::max();

    double t_accel = 0;
    double t_vel = 0;
    double t_pos = 0;
    double pidSetpoint = 0;

    double initialPos = 0;
    double flatPoint = 0;
    double midPoint = 0;
    double deccelPoint = 0;
    double targetPos = 0;
    double distance = 0;

    int dir = 0;

    double kFV = 0; // Feedforward velocity gain
    double kFA = 0; // Feedforward acceleration gain

    double output = 0;
  protected:
  public:
    LinearProfiler(double maxVel, double maxAccel, double kP, double kI, double kD, double kFV, double kFA);
    LinearProfiler(double maxVel, double maxAccel, double kP, double kI, double kD);
    LinearProfiler(double maxVel, double maxAccel);
    LinearProfiler(double maxAccel);

    // Functions to set constants
    void setMaxVel(double maxVel);
    void setMaxAccel(double maxAccel);
    void setContraints(double maxVel, double maxAccel);
    void setP(double kP);
    void setI(double kI);
    void setD(double kD);
    void setVelocityFeedforward(double kFV);
    void setAccelFeedforward(double kFA);
    void setFeedforwardGains(double kFV, double kFA);
    void setGains(double kP, double kI, double kD, double kFV, double kFA);
    void setGains(double kP, double kI, double kD);
    void setOutputRange(double minOutput, double maxOutput);
    void configIntegral(IntegralType integralType, bool integralZone);
    void setIntegralZoneRange(double integralZoneRange);
    void setTolerance(double positionTolerance, double velocityTolerance);

    // Target functions
    void setTarget(double target);
    void setTargetRelative(double target);
    double getTarget();
    double getP();
    double getI();
    double getD();
    double getVelocityFeedforward();
    double getAccelFeedforward();

    // PID Functions
    PIDController* getPID();

    void init(double measurement);
    double calculate(double measurement);
    bool atTarget();

    // Getters for internal variables
    double getTargetPos();
    double getTargetVel();
    double getTargetAccel();
    double getPos();
    double getVel();
    double getAccel();
    double getDeltaTime();
};

#endif
