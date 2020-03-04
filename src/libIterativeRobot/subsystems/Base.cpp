#include "main.h"
#include "libIterativeRobot/Robot.h"
#include "libIterativeRobot/commands/Base/StopBase.h"

const double Base::kDefaultMaxAccel = 0.127;
const double Base::kDefaultMaxVel = 2; // Max is 3.6
const double Base::kDefaultRotationSlewRate = 0.01;   
std::uint32_t startTime = 0;
bool fiveSeconds = false;

Base::Base() {
  // Set up motors
  frontLeftMotor = Motor::getMotor(frontLeftBasePort, baseMotorGearset);
  frontRightMotor = Motor::getMotor(frontRightBasePort, baseMotorGearset);
  backLeftMotor = Motor::getMotor(backLeftBasePort, baseMotorGearset);
  backRightMotor = Motor::getMotor(backRightBasePort, baseMotorGearset);

  frontLeftMotor->getMotorObject()->set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_COAST);
  backLeftMotor->getMotorObject()->set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_COAST);
  frontRightMotor->getMotorObject()->set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_COAST);
  backRightMotor->getMotorObject()->set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_COAST);

  frontRightMotor->reverse();
  backRightMotor->reverse();
  //backRightMotor->reverse();
  //frontRightMotor->reverse();
  frontRightMotor->reverseEncoder();
  frontLeftMotor->reverseEncoder();

  frontLeftMotor->addFollower(backLeftMotor);
  frontRightMotor->addFollower(backRightMotor);

  //leftProfiler = new LinearProfiler(2, 0.017, 0.7, 0, 0, 0, 0);
  //rightProfiler = new LinearProfiler(2, 0.017, 0.7, 0, 0, 0, 0);
  leftProfiler = new LinearProfiler(0.5, 0.001, 0.5, 0, 0, 35.27, 5000);
  rightProfiler = new LinearProfiler(0.5, 0.001, 0.5, 0, 0, 35.27, 5000);

  leftProfiler->setTolerance(15, 1);
  rightProfiler->setTolerance(15, 1);

  rotController = new PIDController(0.6, 0.001, 0.5, 100);
  rotController->setTolerance(5, 1);
  rotController->configIntegral(IntegralType::Default, true);
  rotController->setIntegralZoneRange(20);
  rotController->setOutputDeadband(20, 5);

  rotLimiter = new SlewRateLimiter(kDefaultRotationSlewRate);

  imu = new pros::Imu(imuPort);
  imu->reset();

  startTime = pros::millis();
  fiveSeconds = false;
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
void Base::move(int leftSpeed, int rightSpeed) {
  if (imuCallibrating()) {
    leftSpeed = 0;
    rightSpeed = 0;
    printf("IMU Still calibrating\n");
  }
  //printf("Left speed: %d, Right speed: %d\n", leftSpeed, rightSpeed);
  frontLeftMotor->setSpeed(leftSpeed);
  frontRightMotor->setSpeed(rightSpeed);
}

double Base::getLeftSensorValue() {
  return frontLeftMotor->getEncoderValue();
}

double Base::getRightSensorValue() {
  return frontRightMotor->getEncoderValue();
}

double Base::getHeading() {
  if (!imu->is_calibrating()) {
    return imu->get_rotation();
  } else {
    //printf("Imu is callibrating...\n");
    return 0;
  }
}

bool Base::imuCallibrating() {
  if (!imu->is_calibrating()) {
    return false;
  } else {
    /*if (fiveSeconds) {
      return false;
    } else {
      fiveSeconds = (int)(pros::millis() - startTime) > 5000;
      !imu->is_calibrating() = !!imu->is_calibrating();
      return !!imu->is_calibrating();
    }*/
    return true;
  }
}

void Base::zeroEncoders() {
  printf("Resetting encoders\n");
  frontLeftMotor->resetEncoder();
  frontRightMotor->resetEncoder();
  backLeftMotor->resetEncoder();
  backRightMotor->resetEncoder();
}

void Base::setLinearTarget(double leftTarget, double rightTarget) {
  printf("Left target: %f, Right target: %f\n", leftTarget, rightTarget);
  leftProfiler->setTarget(leftTarget);
  rightProfiler->setTarget(rightTarget);
}

void Base::setLinearTargetRelative(double leftTarget, double rightTarget) {
  printf("Left relative target: %f, Right relative target: %f\n", leftTarget, rightTarget);
  leftProfiler->setTargetRelative(leftTarget);
  rightProfiler->setTargetRelative(rightTarget);
}

void Base::initLinearMovement() {
  leftProfiler->init(getLeftSensorValue());
  rightProfiler->init(getRightSensorValue());
}

void Base::calculateLinearMovement() {
  move((int)leftProfiler->calculate(getLeftSensorValue()), (int)rightProfiler->calculate(getRightSensorValue()));
  printf("Left: %f, Right: %f, Diff: %f\n", getLeftSensorValue(), getRightSensorValue(), getLeftSensorValue() - getRightSensorValue());
}

bool Base::atLinearTarget() {
  return leftProfiler->atTarget() && rightProfiler->atTarget();
}

void Base::setMaxVel(double maxVel) {
  //printf("Setting maxVel to %f\n", maxVel);
  leftProfiler->setMaxVel(maxVel);
  rightProfiler->setMaxVel(maxVel);
}

void Base::setMaxAccel(double maxAccel) {
  //printf("Setting maxAccel to %f\n", maxAccel);
  leftProfiler->setMaxAccel(maxAccel);
  rightProfiler->setMaxAccel(maxAccel);
}

void Base::setRotationTarget(double rotationTarget) {
  rotController->setSetpoint(getHeading() + rotationTarget);
}

void Base::calculateRotation() {
  if (!imu->is_calibrating()) {
    rotController->reset();
    rotLimiter->reset();
    //printf("Still callibrating...\n");
  } else {
    double output = rotLimiter->calculate(rotController->calculate(getHeading()));
    printf("Error: %f, Output: %f\n", rotController->getError(), output);
    move(output, -output);
  }
}

bool Base::atRotationTarget() {
  return rotController->atSetpoint();
}

void Base::resetRotation() {
  rotController->reset();
  rotLimiter->reset();
}

void Base::setMaxRotationSpeed(int maxSpeed) {
  rotController->setOutputRange(-(double)maxSpeed, (double)maxSpeed);
}

void Base::setRotationSlewRate(double slewRate) {
  rotLimiter->setRate(slewRate);
}

void Base::setRotationPIDConstants(double kP, double kI, double kD) {
  rotController->setGains(kP, kI, kD);
}

LinearProfiler* Base::getLeftProfiler() {
  return leftProfiler;
}

LinearProfiler* Base::getRightProfiler() {
  return rightProfiler;
}
