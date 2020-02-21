#include "libIterativeRobot/commands/Angler/AnglerControl.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

AnglerControl::AnglerControl(bool Up) {
  this->Up = Up;
  this->priority = 2;

  requires(Robot::angler);
}

bool AnglerControl::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void AnglerControl::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  // printf("Angler control initialized\n");
}

void AnglerControl::execute() {
  //printf("Angler control running\n");
  if (this->Up) {
    Robot::angler->move(-KMaxMotorSpeed);
  }
  else {
    Robot::angler->move(KMaxMotorSpeed);
  }

  printf("Angler at %d\n", Robot::angler->getSensorValue());
}

bool AnglerControl::isFinished() {
  return true;
}

void AnglerControl::end() {
  // Code that runs when isFinished() returns true.
}

void AnglerControl::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void AnglerControl::blocked() {
}
