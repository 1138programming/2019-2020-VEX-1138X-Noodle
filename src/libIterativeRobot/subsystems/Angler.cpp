#include "main.h"
#include "libIterativeRobot/commands/Angler/StopAngler.h"

const double Angler::kCollectingPosition = -500;

Angler::Angler() {
  // Get angler motors
  anglerMotor = Motor::getMotor(anglerPort, anglerMotorGearset);

  anglerController = new PIDController(0.6, 0, 0);
}

void Angler::initDefaultCommand() {
  setDefaultCommand(new StopAngler());
}

/**
 * Move the angler
 * @param left - speed of the left side
 * @param right - speed of the right side
 */
//pros::ADIDigitalIn bumper ('a');
void Angler::move(int speed) {
  //printf("Angler speed is %d\n", speed);
  anglerMotor->setSpeed(speed);
}

void Angler::encoderReset(){
  anglerMotor->resetEncoder();
}

double Angler::getSensorValue() {
  return anglerMotor->getEncoderValue();
}

void Angler::setSetpoint(double setpoint) {
  anglerController->setSetpoint(setpoint);
}

void Angler::lock() {
  anglerController->setSetpoint(getSensorValue());
}

void Angler::calculate() {
  move((int)anglerController->calculate(getSensorValue()));
}

bool Angler::atSetpoint() {
  return anglerController->atSetpoint();
}

void Angler::resetPID() {
  anglerController->reset();
}

void Angler::setMaxSpeed(int maxSpeed) {
  anglerController->setOutputRange(-(double)maxSpeed, (double)maxSpeed);
}
