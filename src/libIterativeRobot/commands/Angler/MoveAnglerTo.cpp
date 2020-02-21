#include "libIterativeRobot/commands/Angler/MoveAnglerTo.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

MoveAnglerTo::MoveAnglerTo(double target, int maxSpeed, int duration) {
  requires(Robot::angler);
  this->priority = 1;
  this->target = target;
  this->duration = duration;
  this->maxSpeed = maxSpeed;
}

MoveAnglerTo::MoveAnglerTo(double target) : MoveAnglerTo(target, KMaxMotorSpeed, 0) {};
MoveAnglerTo::MoveAnglerTo(double target, int maxSpeed) : MoveAnglerTo(target, maxSpeed, 0) {};

bool MoveAnglerTo::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void MoveAnglerTo::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  Robot::angler->resetPID();
  Robot::angler->setSetpoint(target);
  Robot::angler->setMaxSpeed(maxSpeed);
  startTime = pros::millis();
}

void MoveAnglerTo::execute() {
  //printf("Moving angler to: %d\n", target);
  printf("Moving angler, position is %d, time is %d, duration is %d\n", Robot::angler->getSensorValue(), pros::millis() - startTime, duration);
  Robot::angler->calculate();
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
  Robot::angler->setMaxSpeed(KMaxMotorSpeed);
  //Robot::angler->encoderReset();
}

void MoveAnglerTo::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
  Robot::angler->setMaxSpeed(KMaxMotorSpeed);
  //Robot::angler->encoderReset();
}

void MoveAnglerTo::blocked() {
}
