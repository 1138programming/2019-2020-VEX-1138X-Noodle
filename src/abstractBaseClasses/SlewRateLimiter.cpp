#include "abstractBaseClasses/SlewRateLimiter.h"

SlewRateLimiter::SlewRateLimiter(double rate) {
  this->rate = rate;
}

void SlewRateLimiter::setRate(double rate) {
  this->rate = rate;
}

double SlewRateLimiter::getRate() {
  return rate;
}

void SlewRateLimiter::reset() {
  output = 0;
  lastOutput = 0;
  lastTime = pros::millis() - 10;
}

double SlewRateLimiter::calculate(double input) {
  deltaTime = (double)(pros::millis() - lastTime);
  double error = input - output;
  double dOutput = rate * deltaTime;

  if (error < dOutput) {
    output = input;
  } else {
    if (error > 0) {
      output += dOutput;
    } else {
      output -= dOutput;
    }
  }

  lastTime = pros::millis();
  lastOutput = output;

  return output;
}
