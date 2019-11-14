#include "libIterativeRobot/commands/Angler/AnglerControl.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

AnglerControl::AnglerControl(bool Up) {
  this->Up = Up;
  requires(Robot::angler);
  this->priority = 2;
}

bool AnglerControl::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void AnglerControl::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  // printf("Angler control initialized\n");
  Robot::angler->disablePID();
}

void AnglerControl::execute() {
  //printf("Angler control running\n");
  if (this->Up)
    Robot::angler->move(60);
  else
    Robot::angler->move(-60);

  printf("Angler at %d\n", Robot::angler->getSensorValue());
}

bool AnglerControl::isFinished() {
  return true;
}

void AnglerControl::end() {
  // Code that runs when isFinished() returns true.
  //Robot::angler->lock();
}

void AnglerControl::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void AnglerControl::blocked() {

}
