#include "libIterativeRobot/commands/StopArm.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

StopArm::StopArm() {
  //requires(Robot::intake);
  //this->priority = DefaultCommandPriority; // Lowest priority
}

bool StopArm::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void StopArm::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  Robot::arm->move(0);
}

void StopArm::execute() {
}

bool StopArm::isFinished() {
  return false;
}

void StopArm::end() {
  // Code that runs when isFinished() returns true.
}

void StopArm::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void StopArm::blocked() {

}
