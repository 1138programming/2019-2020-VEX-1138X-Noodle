#include "main.h"
#include "libIterativeRobot/commands/StopBase.h"

Base::Base() {
  // Set up motors
  frontLeftMotor = Motor::getMotor(frontLeftBasePort, baseMotorGearset);
  frontRightMotor = Motor::getMotor(frontRightBasePort, baseMotorGearset);
  backLeftMotor = Motor::getMotor(backLeftBasePort, baseMotorGearset);
  backRightMotor = Motor::getMotor(backRightBasePort, baseMotorGearset);

  backLeftMotor->reverse();
  frontLeftMotor->reverse();

  frontLeftMotor->addFollower(backLeftMotor);
  frontRightMotor->addFollower(backRightMotor);

  leftProfiler = new LinearProfiler(frontLeftMotor, 10, 0.17, 0.7, 0, 0);
  rightProfiler = new LinearProfiler(frontRightMotor, 10, 0.17, 0.7, 0, 0);
}

void Base::initDefaultCommand() {
  // Setup up a default command here
  setDefaultCommand(new StopBase());
}

/**
 * Move the base
 * @param left - speed of the left side
 * @param right - speed of the right side
 */
void Base::moveAtSpeed(int leftSpeed, int rightSpeed) {
  frontLeftMotor->setSpeed(leftSpeed);
  frontRightMotor->setSpeed(rightSpeed);
}

void Base::setLinearTarget(int leftTarget, int rightTarget) {
  leftProfiler->setTarget(leftTarget);
  rightProfiler->setTarget(rightTarget);
}

void Base::setLinearTargetRelative(int leftTarget, int rightTarget) {
  leftProfiler->setTargetRelative(leftTarget);
  rightProfiler->setTargetRelative(rightTarget);
}

void Base::initLinearMovement() {
  leftProfiler->init();
  rightProfiler->init();
}

void Base::updateLinearMovement() {
  leftProfiler->update();
  rightProfiler->update();
}

bool Base::atLinearTarget() {
  return leftProfiler->atTarget() && rightProfiler->atTarget();
}

void Base::stopLinearMovement() {
  leftProfiler->stop();
  rightProfiler->stop();
}
