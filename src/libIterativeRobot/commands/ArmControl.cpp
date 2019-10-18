#include "libIterativeRobot/commands/ArmControl.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

ArmControl::ArmControl() {
  requires(Robot::arm);
  this->priority = 2;
}

bool ArmControl::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void ArmControl::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  armSpeed = Robot::mainController->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
}

void ArmControl::execute() {
  Robot::arm->move(armSpeed);
}

bool ArmControl::isFinished() {
  return true;
}

void ArmControl::end() {
  // Code that runs when isFinished() returns true.
}

void ArmControl::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void ArmControl::blocked() {

}
