#include "main.h"
#include "libIterativeRobot/commands/Angler/StopAngler.h"

Angler::Angler() {
  // Get angler motors
  anglerMotor = Motor::getMotor(anglerPort, anglerMotorGearset);

  anglerController = new PIDController(anglerMotor, 0.6, 0, 0);
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

int Angler::getSensorValue() {
  return (int)anglerMotor->getEncoderValue();
}

void Angler::setSetpoint(int setpoint) {
  anglerController->setSetpoint(setpoint);
}

bool Angler::atSetpoint() {
  return anglerController->atSetpoint();
}

void Angler::loop() {
  anglerController->loop();
}

void Angler::lock() {
  anglerController->lock();
}

void Angler::disablePID() {
  anglerController->disable();
  anglerMotor->resetEncoder();
}

void Angler::enablePID() {
  anglerController->enable();
}

void Angler::setMaxSpeed(int maxSpeed) {
  anglerController->setOutputRange(-maxSpeed, maxSpeed);
}
