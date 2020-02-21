#include "libIterativeRobot/commands/Miscellaneous/TuneLinearProfile.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

TuneLinearProfile::TuneLinearProfile(LinearProfiler* profiler, const double* motorData, Motor* motor, int target) {
  this->profiler = profiler;
  this->motor = motor;
  this->target = target;
  this->motorData = motorData;
  this->priority = 2;
}

bool TuneLinearProfile::canRun() {
  return true;
}

void TuneLinearProfile::initialize() {
  printf("Linear profile tuner starting\n");

  profiler->init(motor->getEncoderValue());
  profiler->setTargetRelative(target);
  dP = 0;
  dI = 0;
  dD = 0;

  error = 0;
  lastError = 0;
  accError = 0;
  dError = 0;
  lastVoltage = 0;
  loss = 0;
}

void TuneLinearProfile::execute() {
  printf("Executing linear profile tuner\n");

  int output = (int)profiler->calculate(motor->getEncoderValue());

  int dt = profiler->getDeltaTime();

  error = profiler->getTargetPos() - profiler->getPos();
  if (dt == 0) {
    dError = 0;
  } else {
    dError = (double)(error - lastError) / dt;
    accError += (double)error / dt;
  }

  double coef = (double)(2 * -error) * deltaMotor(motorData, lastVoltage) * dt;
  dP += coef * error;
  dI += coef * accError;
  dD += coef * dError;

  loss += (error * error);

  lastError = error;
  lastVoltage = output;
}

bool TuneLinearProfile::isFinished() {
  printf("Linear profile tuner is finished\n");

  return profiler->atTarget();
}

void TuneLinearProfile::end() {
  adjustConstants();
}

void TuneLinearProfile::interrupted() {
}

void TuneLinearProfile::blocked() {
}

void TuneLinearProfile::adjustConstants() {
  printf("%x: dP %f, dI %f, dD %f, loss %d\n", this, learning_rate * dP, learning_rate * dI, learning_rate * dD, loss);
  profiler->setP(profiler->getP() + (-dP * learning_rate));
  profiler->setP(profiler->getI() + (-dI * learning_rate));
  profiler->setP(profiler->getD() + (-dD * learning_rate));
}

double TuneLinearProfile::deltaMotor(const double* data, int voltage) {
  if (voltage == 127) {
    return data[254] - data[253];
  } else {
    return data[voltage + 128] - data[voltage + 127];
  }
}
