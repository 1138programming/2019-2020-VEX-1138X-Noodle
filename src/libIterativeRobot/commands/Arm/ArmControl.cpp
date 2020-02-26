#include "libIterativeRobot/commands/Arm/ArmControl.h"
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
  printf("ArmControl init\n");
  armSpeed = Robot::mainController->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)*2;
}

void ArmControl::execute() {
  Robot::arm->move(armSpeed);
  printf("Arm position is %d\n", Robot::arm->getSensorValue());
}

bool ArmControl::isFinished() {
  return true;
}

void ArmControl::end() {
  // Code that runs when isFinished() returns true.
  //Robot::arm->lock();
}

void ArmControl::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
  //Robot::arm->lock();
}

void ArmControl::blocked() {
  //Robot::arm->lock();
}
