#include "libIterativeRobot/commands/Angler/MoveAnglerTo.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

/*MoveAnglerTo::MoveAnglerTo(int target) {
  requires(Robot::angler);
  this->priority = 1;
  this->target = target;
  this->duration = 0;
  this->maxSpeed = KMaxMotorSpeed;
  printf("%x: wtf\n", this);
}

MoveAnglerTo::MoveAnglerTo(int target, int duration) {
  requires(Robot::angler);
  this->priority = 1;
  this->target = target;
  this->duration = duration;
  this->maxSpeed = KMaxMotorSpeed;
  printf("%x: Target %d, duration %d\n", this, this->target, this->duration);
}*/

MoveAnglerTo::MoveAnglerTo(int target, int maxSpeed, int duration) {
  requires(Robot::angler);
  this->priority = 1;
  this->target = target;
  this->duration = duration;
  this->maxSpeed = maxSpeed;
}

MoveAnglerTo::MoveAnglerTo(int target) : MoveAnglerTo(target, KMaxMotorSpeed, 0) {};
MoveAnglerTo::MoveAnglerTo(int target, int maxSpeed) : MoveAnglerTo(target, maxSpeed, 0) {};

bool MoveAnglerTo::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void MoveAnglerTo::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  Robot::angler->enablePID();
  Robot::angler->setSetpoint(target);
  Robot::angler->setMaxSpeed(maxSpeed);
  startTime = pros::millis();
}

void MoveAnglerTo::execute() {
  //printf("Moving angler to: %d\n", target);
  printf("Moving angler, position is %d, time is %d, duration is %d\n", Robot::angler->getSensorValue(), pros::millis() - startTime, duration);
}

bool MoveAnglerTo::isFinished() {
  if (duration == 0) {
    return Robot::angler->atSetpoint();
  } else {
    return Robot::angler->atSetpoint() || (pros::millis() > (startTime + duration));
  }
}

void MoveAnglerTo::end() {
  // Code that runs when isFinished() returns true.
  Robot::angler->disablePID();
  Robot::angler->setMaxSpeed(KMaxMotorSpeed);
}

void MoveAnglerTo::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
  Robot::angler->disablePID();
  Robot::angler->setMaxSpeed(KMaxMotorSpeed);
}

void MoveAnglerTo::blocked() {
}
