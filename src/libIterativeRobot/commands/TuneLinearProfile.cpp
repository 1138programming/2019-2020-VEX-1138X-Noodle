#include "libIterativeRobot/commands/TuneLinearProfile.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

TuneLinearProfile::TuneLinearProfile(LinearProfiler* profiler, const double* motorData, libIterativeRobot::Subsystem* subsystem, int target) {
  this->profiler = profiler;
  this->subsystem = subsystem;
  this->target = target;
  this->priority = 2;
  this->motorData = motorData;

  requires(subsystem);
}

bool TuneLinearProfile::canRun() {
  return true;
}

void TuneLinearProfile::initialize() {
  profiler->init();
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
  profiler->update();

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

  loss += std::pow(error, 2);

  lastError = error;
  lastVoltage = profiler->getOutput();
}

bool TuneLinearProfile::isFinished() {
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
  profiler->kP += -dP * learning_rate;
  profiler->kI += -dI * learning_rate;
  profiler->kD += -dD * learning_rate;
}

double TuneLinearProfile::deltaMotor(const double* data, int voltage) {
  if (voltage == 127) {
    return data[254] - data[253];
  } else {
    return data[voltage + 128] - data[voltage + 127];
  }
}
