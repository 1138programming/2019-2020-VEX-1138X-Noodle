#include "libIterativeRobot/commands/Arm/MoveArmTo.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

MoveArmTo::MoveArmTo(int target) {
  requires(Robot::arm);
  this->priority = 1;
  this->target = target;
  this->duration = 0;
}

MoveArmTo::MoveArmTo(int target, int duration) {
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
  Robot::arm->enablePID();
  Robot::arm->setSetpoint(target);
  startTime = pros::millis();
}

void MoveArmTo::execute() {
  printf("Moving arm to: %d, arm position is %d\n", Robot::arm->getSetpointValue(), Robot::arm->getSensorValue());
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
  Robot::arm->disablePID();
}

void MoveArmTo::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
  Robot::arm->disablePID();
}

void MoveArmTo::blocked() {
}
