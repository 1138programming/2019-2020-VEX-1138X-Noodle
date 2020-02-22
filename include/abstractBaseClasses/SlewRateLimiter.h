#ifndef _ABSTRACTBASECLASSES_SLEWRATELIMITER_H_
#define _ABSTRACTBASECLASSES_SLEWRATELIMITER_H_

#include "api.h"

class SlewRateLimiter {
  private:
    double rate;
    double input; // If no motor is given, this must be set manually
    double output; // Output of the PID loop
    double lastOutput;
    double deltaTime; // Time between loops
    int lastTime = 0; // Time recorded in the last loop
  public:
    SlewRateLimiter(double rate); // Initializes a PID controller with a motor
    void setRate(double rate);
    double getRate();
    double calculate(double input); // Does all calculations
    void reset();
};

#endif
