#include "main.h"
#include "libIterativeRobot/commands/Intake/StopIntake.h"

Intake::Intake() {
  // Get intake motors
  leftIntakeMotor = Motor::getMotor(leftIntakeMotorPort, intakeMotorGearset);
  rightIntakeMotor = Motor::getMotor(rightIntakeMotorPort, intakeMotorGearset);

  rightIntakeMotor->reverse();
  leftIntakeMotor->getMotorObject()->set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  rightIntakeMotor->getMotorObject()->set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void Intake::initDefaultCommand() {
  setDefaultCommand(new StopIntake());
}

/**
 * Move the intake
 * 
 * @param speed - speed of the speed side
 */

void Intake::move(int speed) {
  leftIntakeMotor->setSpeed(speed);
  rightIntakeMotor->setSpeed(speed);
  //printf("Motor speed set to %d\n", speed);
}
