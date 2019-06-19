#include "libIterativeRobot/commands/DriveWithJoy.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

DriveWithJoy::DriveWithJoy() {
  requires(Robot::base);
  this->priority = 2;
}

bool DriveWithJoy::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void DriveWithJoy::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  xSpeed = Robot::mainController->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
  ySpeed = Robot::mainController->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
}

void DriveWithJoy::execute() {
  //printf("Drive with joy is running\n");
  Robot::base->move(ySpeed + xSpeed, ySpeed - xSpeed);
  printf("ySpeed is %d and xSpeed is %d\n", ySpeed, xSpeed);
}

bool DriveWithJoy::isFinished() {
  return true;
}

void DriveWithJoy::end() {
  // Code that runs when isFinished() returns true.
}

void DriveWithJoy::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}
