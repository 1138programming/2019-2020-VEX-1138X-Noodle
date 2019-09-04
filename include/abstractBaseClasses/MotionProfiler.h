#ifndef MOTION_PROFILER_H
#define MOTION_PROFILER_H

#include "Motor.h"
#include "PIDController.h"

class MotionProfiler {
  private:
    PIDController* leftPosPID;
    PIDController* rightPosPID;

    Motor* leftOutputMotor;
    Motor* rightOutputMotor;

    int rightSensorValue;
    int leftSensorValue;

    int leftLastPos = 0;
    int rightLastPos = 0;
    //int leftVel = 0;
    //int rightVel = 0;
    std::uint32_t lastTime = 0;

    bool baseReversed = false;
    bool baseSlow = false;

    int baseEncoderDrift = 0;

    //double accel = 0.34;
    //double accel = 0.68;
    double accel = 0.17;
    double leftAccel = 0;
    double rightAccel = 0;
    double leftVel = 0;
    double rightVel = 0;
    //double maxVel = 17;
    double maxVel = 10;
    double leftSetpoint = 0;
    double rightSetpoint = 0;
    int leftSetpoint = 0;
    int rightSetpoint = 0;
    int leftDeccelPoint = 0;
  public:
    MotionProfiler(Motor* leftOutputMotor, Motor* rightOutputMotor, float leftKP, float leftKI, float leftKD, float rightKP, float rightKI, float rightKD);
    MotionProfiler(Motor* leftOutputMotor, Motor* rightOutputMotor);
    // MotionProfiler();

    void setPIDConstants(float leftKP, float leftKI, float leftKD, float rightKP, float rightKI, float rightKD);
    void setSetpointsRelative(int leftSetpoint, int rightSetpoint);
    void setSetpoints(int leftSetpoint, int rightSetpoint);

    void setSensorValues(int leftSensorValue, int rightSensorValue);

    int getLeftSensorValue();
    int getRightSensorValue();

    // These functions are used to initialize and access the MotionProfiler object
    void initMovement(int leftTarget, int rightTarget);
//     void updateMovement();
//     bool profilerAtTarget();
//     void updateMovement();
};

#endif // MOTION_PROFILER_H
