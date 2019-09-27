#include "main.h"
#include "libIterativeRobot/commands/StopLift.h"

Lift::Lift() {
  // Get lift motors
  liftMotor = Motor::getMotor(liftPort, liftMotorGearset);

  liftController = new PIDController(liftMotor, 0.32, 0, 0.05);

  bumper = new pros::ADIDigitalIn(bumperPort);
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
  if (bumper->get_value())
  {
    if (speed > 0) {
      liftMotor->setSpeed(0);
    } else if (speed < 0) {
      liftMotor->setSpeed(-K50MotorSpeed);
    }
    //pros::delay(500);
    //printf("Motor speed reversed.");
  }
  else
  {
    liftMotor->setSpeed(speed);
  }
}

void Lift::setSetpoint(int setpoint) {
  liftController->setSetpoint(setpoint);
}

bool Lift::atSetpoint() {
  return liftController->atSetpoint();
}

void Lift::loop() {
  liftController->loop();
}

void Lift::lock() {
  liftController->lock();
}

void Lift::disablePID() {
  liftController->disable();
}

void Lift::enablePID() {
  liftController->enable();
}
