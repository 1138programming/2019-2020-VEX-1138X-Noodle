#include "libIterativeRobot/commands/Arm/MoveArmTo.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

MoveArmTo::MoveArmTo(double target) {
  requires(Robot::arm);
  this->priority = 1;
  this->target = target;
  this->duration = 0;
}

MoveArmTo::MoveArmTo(double target, int duration) {
  requires(Robot::arm);
  this->priority = 1;
  this->target = target;
  this->duration = duration;
}

bool MoveArmTo::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void MoveArmTo::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  Robot::arm->setSetpoint(target);
  Robot::arm->resetPID();
  startTime = pros::millis();
}

void MoveArmTo::execute() {
  printf("Moving arm to: %d, arm position is %d\n", (int)Robot::arm->getSetpoint(), Robot::arm->getSensorValue());
  Robot::arm->calculate();
}

bool MoveArmTo::isFinished() {
  if (duration == 0) {
    return Robot::arm->atSetpoint();
  } else {
    return Robot::arm->atSetpoint() || pros::millis() > (startTime + duration);
  }
}

void MoveArmTo::end() {
  // Code that runs when isFinished() returns true.
}

void MoveArmTo::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void MoveArmTo::blocked() {
}
