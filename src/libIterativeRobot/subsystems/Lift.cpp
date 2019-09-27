#include "main.h"
#include "libIterativeRobot/commands/StopLift.h"

Lift::Lift() {
  // Get lift motors
  leftLiftMotor = Motor::getMotor(leftLiftMotorPort, liftMotorGearset);
  rightLiftMotor = Motor::getMotor(rightLiftMotorPort, liftMotorGearset);

  rightLiftMotor->reverse();

  leftLiftController = new PIDController(leftLiftMotor, 0.32, 0, 0.05);
  rightLiftController = new PIDController(leftLiftMotor, 0.32, 0, 0.05);

  leftLiftBumper = new pros::ADIDigitalIn(leftLiftBumperPort);
  rightLiftBumper = new pros::ADIDigitalIn(rightLiftBumperPort);
}

void Lift::initDefaultCommand() {
  setDefaultCommand(new StopLift());
}

/**
 * Move the lift
 * @param left - speed of the left side
 * @param right - speed of the right side
 */
//pros::ADIDigitalIn bumper ('a');
void Lift::move(int speed) {
  //printf("Lift speed is %d\n", speed);
  if (leftLiftBumper->get_value() || rightLiftBumper->get_value())
  {
    if (speed > 0) {
      leftLiftMotor->setSpeed(0);
      rightLiftMotor->setSpeed(0);
    } else if (speed < 0) {
      leftLiftMotor->setSpeed(-K50MotorSpeed);
      rightLiftMotor->setSpeed(-K50MotorSpeed);
    }
    //pros::delay(500);
    //printf("Motor speed reversed.");
  }
  else
  {
    leftLiftMotor->setSpeed(speed);
    rightLiftMotor->setSpeed(speed);
  }
}

void Lift::setSetpoint(int setpoint) {
  leftLiftController->setSetpoint(setpoint);
  rightLiftController->setSetpoint(setpoint);
}

bool Lift::atSetpoint() {
  return leftLiftController->atSetpoint() && rightLiftController->atSetpoint();
}

void Lift::loop() {
  leftLiftController->loop();
  rightLiftController->loop();
}

void Lift::lock() {
  leftLiftController->lock();
  rightLiftController->lock();
}

void Lift::disablePID() {
  leftLiftController->disable();
  rightLiftController->disable();
}

void Lift::enablePID() {
  leftLiftController->enable();
  rightLiftController->enable();
}
