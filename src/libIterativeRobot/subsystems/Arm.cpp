#include "main.h"
#include "libIterativeRobot/commands/StopArm.h"

Arm::Arm() {
  // Get intake motors
  armMotor = Motor::getMotor(armMotorPort, armMotorGearset);
}

void Arm::initDefaultCommand() {
  setDefaultCommand(new StopArm());
}

/**
 * Move the arm
 * @param speed - speed of the speed arm motor
 */
void Arm::move(int speed) {
  armMotor->setSpeed(speed);;
}
