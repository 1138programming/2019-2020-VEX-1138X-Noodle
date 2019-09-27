#include "libIterativeRobot/commands/MoveClawTo.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

MoveClawTo::MoveClawTo(int target = 0) {
  requires(Robot::claw);
  this->priority = 1;
  this->target = target;
}

bool MoveClawTo::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void MoveClawTo::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  Robot::claw->enablePID();
  Robot::claw->setSetpoint(target);
}

void MoveClawTo::execute() {
  //printf("Moving claw to: %d\n", target);
}

bool MoveClawTo::isFinished() {
  return Robot::claw->atSetpoint();
}

void MoveClawTo::end() {
  // Code that runs when isFinished() returns true.
  //Robot::claw->lock();
}

void MoveClawTo::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void MoveClawTo::blocked() {

}
