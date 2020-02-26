#include "main.h"
#include "libIterativeRobot/commands/Arm/StopArm.h"
#include "libIterativeRobot/commands/Arm/ArmControl.h"

const double Arm::kLowTowerPos = 2500;
const double Arm::kMidTowerPos = 3000;

Arm::Arm() {
  // Get intake motors
  armMotor = Motor::getMotor(armMotorPort, armMotorGearset);
  armController = new PIDController(0.7, 0, 0);
  armController->setTolerance(25, 10);

  bumper1 = new pros::ADIDigitalIn(bumperPort1);
  bumper2 = new pros::ADIDigitalIn(bumperPort2);
}

void Arm::initDefaultCommand() {
  if (pros::E_CONTROLLER_DIGITAL_X > abs(20)) {
    setDefaultCommand(new ArmControl());
  }
  else
  {
    setDefaultCommand(new StopArm());
  }
  
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

double Arm::getSensorValue() {
  return armMotor->getEncoderValue();
}

void Arm::setSetpoint(double setpoint) {
  armController->setSetpoint(setpoint);
}

void Arm::lock() {
  armController->setSetpoint(getSensorValue());
}

double Arm::getSetpoint() {
  return armController->getSetpoint();
}

void Arm::calculate() {
  move((int)armController->calculate(getSensorValue()));
}

bool Arm::atSetpoint() {
  return armController->atSetpoint();
}

void Arm::resetPID() {
  armController->reset();
}
