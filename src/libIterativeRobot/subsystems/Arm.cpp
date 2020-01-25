#include "main.h"
#include "libIterativeRobot/commands/Arm/StopArm.h"

Arm::Arm() {
  // Get intake motors
  armMotor = Motor::getMotor(armMotorPort, armMotorGearset);
  armController = new PIDController(armMotor, 0.7, 0, 0);
  armController->setThreshold(25);

  bumper1 = new pros::ADIDigitalIn(bumperPort1);
  bumper2 = new pros::ADIDigitalIn(bumperPort2);
}

void Arm::initDefaultCommand() {
  setDefaultCommand(new StopArm());
}

/**
 * Move the arm
 * @param speed - speed of the speed arm motor
 */
void Arm::move(int speed) {
  if (bumper1->get_value() || bumper2->get_value()) {
    armMotor->setSpeed(0);
    if (speed > 0) {
      armMotor->setSpeed(speed);
    } else if (speed < 0) {
      armMotor->setSpeed(0);
    }
    armMotor->resetEncoder();
  } else {
    armMotor->setSpeed(speed);
  }
}

int Arm::getSensorValue() {
  return (int)armMotor->getEncoderValue();
}

int Arm::getSetpointValue() {
  return armController->getSensorValue();
}

void Arm::setSetpoint(int setpoint) {
  armController->setSetpoint(setpoint);
}

bool Arm::atSetpoint() {
  return armController->atSetpoint();
}

void Arm::loop() {
  armController->loop();
}

void Arm::lock() {
  armController->lock();
}

void Arm::disablePID() {
  armController->disable();
}

void Arm::enablePID() {
  armController->enable();
}
