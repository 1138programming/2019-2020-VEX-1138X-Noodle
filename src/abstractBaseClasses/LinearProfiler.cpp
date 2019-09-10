#include "abstractBaseClasses/LinearProfiler.h"

LinearProfiler::LinearProfiler(Motor* outputMotor, double maxVel, double maxAccel, float kP, float kI, float kD) {
  this->outputMotor = outputMotor;
  this->maxVel = maxVel;
  this->maxAccel = maxAccel;
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;

  posPID = new PIDController(outputMotor, kP, kI, kD);
}

LinearProfiler::LinearProfiler(Motor* outputMotor, double maxVel, double maxAccel) {
  this->outputMotor = outputMotor;
  this->maxVel = maxVel;
  this->maxAccel = maxAccel;

  posPID = new PIDController(outputMotor, kP, kI, kD);
}

LinearProfiler::LinearProfiler(Motor* outputMotor) {
  this->outputMotor = outputMotor;

  posPID = new PIDController(outputMotor, kP, kI, kD);
}

void LinearProfiler::setMaxVel(int maxVel) {
  this->maxVel = maxVel;
}

void LinearProfiler::setMaxAccel(int maxAccel) {
  this->maxAccel = maxAccel;
}

void LinearProfiler::setTarget(int target) {
  this->target = target;
}

void LinearProfiler::setTargetRelative(int target) {
  this->target = getSensorValue() + target;
}

int LinearProfiler::getTarget() {
  return target;
}

void LinearProfiler::setSensorValue(int sensorValue) {
  posPID->setSensorValue(sensorValue);
}

int LinearProfiler::getSensorValue() {
  return posPID->getSensorValue();
}

PIDController* LinearProfiler::getPID() {
  return posPID;
}

void LinearProfiler::init() {
  int initial = getSensorValue();
  int distance = target - initial;

  // The middle point on the path
  int midpoint = abs(distance / 2) + initial;

  // Calculates the point at which the acceleration should become 0
  flatPoint = 0.5 * ((maxVel * maxVel) / maxAccel) + initial;

  // Checks to see if the target distance is long enough to get to the max velocity
  if (midpoint < flatPoint) {
    deccelPoint = midpoint;
  } else {
    deccelPoint = (target - (flatPoint)) + initial;
  }

  if (target > initial) {
    dir = 1;
  } else {
    dir = -1;
  }

  pidSetpoint = initial;
  posPID->setSetpoint((int)pidSetpoint);
  posPID->enable();
}

void LinearProfiler::update() {
  if (abs(pidSetpoint) < flatPoint) {
    accel = maxAccel * dir;
  } else if (abs(pidSetpoint) < deccelPoint) {
    accel = 0;
  } else {
    accel = -maxAccel * dir;
  }

  vel += accel;
  if (abs(vel) > maxVel) {
    vel = maxVel * dir;
  }

  pidSetpoint += vel;

  posPID->setSetpoint((int)pidSetpoint);
}

bool LinearProfiler::atTarget() {
  if (abs(getSensorValue()) > deccelPoint) {
    return (vel == 0 && posPID->atSetpoint());
  }
  return false;
}

void LinearProfiler::stop() {
  posPID->disable();
}

int LinearProfiler::getOutput() {
  return posPID->getOutput();
}
