#include "libIterativeRobot/commands/Base/RotateBase.h"
#include "libIterativeRobot/Robot.h"

RotateBase::RotateBase(double rotationTarget, double slewRate, int maxSpeed, int duration) {
  this->rotationTarget = rotationTarget;
  this->slewRate = slewRate;
  this->maxSpeed = maxSpeed;
  this->duration = duration;

  this->priority = 3;
  requires(Robot::base);
}

RotateBase::RotateBase(double rotationTarget, double slewRate, int maxSpeed) : RotateBase(rotationTarget, slewRate, maxSpeed, 5000) {};
RotateBase::RotateBase(double rotationTarget, double slewRate) : RotateBase(rotationTarget, slewRate, KMaxMotorSpeed, 5000) {};
RotateBase::RotateBase(double rotationTarget) : RotateBase(rotationTarget, Robot::base->kDefaultRotationSlewRate, KMaxMotorSpeed, 5000) {};

bool RotateBase::canRun() {
  //printf("Checking if Rotate Base can run\n");
  return true;
}

void RotateBase::initialize() {
  printf("Init Rotate Base: %f\n", rotationTarget);
  Robot::base->resetRotation();
  Robot::base->setRotationTarget(rotationTarget);
  Robot::base->setRotationSlewRate(slewRate);
  Robot::base->setMaxRotationSpeed(maxSpeed);
  startTime = pros::millis();
}

void RotateBase::execute() {
  //printf("Running Rotate Base\n");
  Robot::base->calculateRotation();
}

bool RotateBase::isFinished() {
  //return (!Robot::base->imuCallibrating() && Robot::base->atRotationTarget()) || (pros::millis() - startTime > duration);
  return false;
}

void RotateBase::end() {
  printf("Rotate Base end\n");
}

void RotateBase::interrupted() {
  printf("Rotate Base interrupted\n");
}

void RotateBase::blocked() {
  printf("Rotate Base blocked\n");
}
