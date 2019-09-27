#include "libIterativeRobot/commands/LiftControl.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

LiftControl::LiftControl() {
  requires(Robot::lift);
  this->priority = 2;
}

bool LiftControl::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void LiftControl::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  // printf("Claw control initialized\n");
  Robot::lift->disablePID();
}

void LiftControl::execute() {
  //printf("Claw control running\n");
  Robot::lift->move(Robot::partnerController->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
}

bool LiftControl::isFinished() {
  return true;
}

void LiftControl::end() {
  // Code that runs when isFinished() returns true.
  //Robot::claw->lock();
}

void LiftControl::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void LiftControl::blocked() {

}
