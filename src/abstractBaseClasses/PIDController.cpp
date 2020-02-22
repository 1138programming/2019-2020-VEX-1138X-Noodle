#include "abstractBaseClasses/PIDController.h"

PIDController::PIDController(double kP, double kI, double kD, double kF) {
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
  this->kF = kF;

  errorCache = new std::vector<double>();
}

PIDController::PIDController(double kP, double kI, double kD) : PIDController(kP, kI, kD, 0) {};

void PIDController::setP(double kP) {
  this->kP = kP;
}

void PIDController::setI(double kI) {
  this->kI = kI;
}

void PIDController::setD(double kD) {
  this->kD = kD;
}

void PIDController::setF(double kF) {
  this->kF = kF;
}

void PIDController::setGains(double kP, double kI, double kD, double kF) {
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
  this->kF = kF;
}

void PIDController::setGains(double kP, double kI, double kD) {
  setGains(kP, kI, kD, kF);
}

double PIDController::getP() {
  return kP;
}

double PIDController::getI() {
  return kI;
}

double PIDController::getD() {
  return kD;
}

double PIDController::getF() {
  return kF;
}

void PIDController::setSetpoint(double setpoint) {
  //printf("Setpoint set to %d\n", setpoint);
  this->setpoint = setpoint;
}

void PIDController::setSetpointRelative(double setpoint) {
  this->setpoint += setpoint;
}

double PIDController::getSetpoint() {
  return this->setpoint;
}

bool PIDController::atSetpoint() {
  return fabs(error) < setpointTolerance && fabs(velocityError) < velocityTolerance;
}

void PIDController::setTolerance(double setpointTolerance, double velocityTolerance) {
  this->setpointTolerance = setpointTolerance;
  this->velocityTolerance = velocityTolerance;
}

double PIDController::getError() {
  return error;
}

double PIDController::getVelocityError() {
  return velocityError;
}

double PIDController::getErrorIntegral() {
  return integral;
}

void PIDController::setOutputRange(double minOutput, double maxOutput) {
  if (minOutput > maxOutput) {
    this->minOutput = maxOutput;
    this->maxOutput = minOutput;
  } else {
    this->minOutput = minOutput;
    this->maxOutput = maxOutput;
  }
}

void PIDController::setIntegralRange(double minIntegral, double maxIntegral) {
  if (minOutput > maxOutput) {
    this->minIntegral = maxIntegral;
    this->maxIntegral = minIntegral;
  } else {
    this->minIntegral = minIntegral;
    this->maxIntegral = maxIntegral;
  }
}

void PIDController::setOutputDeadband(double deadband, double tolerance) {
  this->outputDeadband = deadband;
  this->outputDeadbandTolerance = tolerance;
}

void PIDController::configIntegral(IntegralType integralType, bool integralZone) {
  this->integralType = integralType;
  this->integralZone = integralZone;

  if (integralType != IntegralType::Window) {
    integralWindow = 0;
  }
}

void PIDController::setIntegralZoneRange(double integralZoneRange) {
  this->integralZoneRange = integralZoneRange;
}

void PIDController::setIntegralWindowLength(int integralWindow) {
  if (integralType != IntegralType::Window) {
    this->integralWindow = 0;
  } else {
    if (integralWindow < 1) {
      this->integralWindow = 1;
    } else {
      this->integralWindow = integralWindow;
    }
  }
}

double PIDController::calculate(double measurement) {
  deltaTime = pros::millis() - lastTime;

  // Stores the given measurement
  this->measurement = measurement;

  // Calculates error
  error = setpoint - measurement;

  // Calculates the derivative
  velocityError  = (error - lastError) / deltaTime;

  // Store current error and remove the oldest error if necessary
  double oldestError;
  if (integralWindow > 0) {
    if (errorCache->size() >= integralWindow) { // Error cache is no longer growing
      (*errorCache)[oldestErrorIndex] = error * deltaTime;

      oldestErrorIndex++;
      if (oldestErrorIndex >= integralWindow) {
        oldestErrorIndex = 0;
      }

      oldestError = (*errorCache)[oldestError];
    } else { // Error cache is still growing
      errorCache->push_back(error * deltaTime);
      oldestErrorIndex = 0;
      oldestError = 0;
    }
  } else {
    oldestError = 0;
  }

  // Handles maintaining the integral term
  if (integralType != IntegralType::None && (!integralZone || fabs(error) < integralZoneRange)) {
    integral += error;

    if (integralType == IntegralType::Window) {
      integral -= oldestError;
    }

    integral = confineToRange(integral, minIntegral, maxIntegral);
  } else {
    integral = 0;
  }

  // Calculates the output
  output = (kP * error) + (kI * integral) + (kD * velocityError) + (kF * setpoint);

  if (fabs(output) > outputDeadbandTolerance) {
    if (output > 0) {
      output += outputDeadband;
    } else {
      output -= outputDeadband;
    }
  } else {
    output = 0;
  }

  // Clamps output between the maximum and minimum output
  output = confineToRange(output, minOutput, maxOutput);

  // Update stored values
  lastError = error;
  lastTime = pros::millis();

  // Return the controller's output
  return output;
}

void PIDController::reset() {
  integral = 0;
  lastError = 0;
  lastTime = pros::millis() - 10;
  oldestErrorIndex = 0;
  errorCache->clear();
}
