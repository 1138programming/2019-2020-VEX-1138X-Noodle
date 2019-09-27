#include "main.h"
#include "libIterativeRobot/commands/StopClaw.h"

Claw::Claw() {
  // Get intake motors
  clawMotor = Motor::getMotor(clawMotorPort, clawMotorGearset);

  clawMotor->getMotorObject()->set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void Claw::initDefaultCommand() {
  setDefaultCommand(new StopClaw());
}

/**
 * Move the intake
 * @param speed - speed of the speed side
 * @param right - speed of the right side
 */

void Claw::move(int speed) {
  clawMotor->setSpeed(speed);
  //printf("Motor speed set to %d\n", speed);
}
