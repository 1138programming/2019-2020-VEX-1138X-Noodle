#include "abstractBaseClasses/LinearProfiler.h"

LinearProfiler::LinearProfiler(double maxVel, double maxAccel, double kP, double kI, double kD, double kFV, double kFA) {
  this->maxVel = maxVel;
  this->maxAccel = maxAccel;
  this->kFV = kFV;
  this->kFA = kFA;

  posPID = new PIDController(kP, kI, kD);
}

LinearProfiler::LinearProfiler(double maxVel, double maxAccel, double kP, double kI, double kD) : LinearProfiler(maxVel, maxAccel, kP, kI, kD, 0, 0) {};
LinearProfiler::LinearProfiler(double maxVel, double maxAccel) : LinearProfiler(maxVel, maxAccel, 1, 0, 0, 0, 0) {};
LinearProfiler::LinearProfiler(double maxAccel) : LinearProfiler(std::numeric_limits<double>::max(), maxAccel, 1, 0, 0, 0, 0) {};

void LinearProfiler::setMaxVel(double maxVel) {
  this->maxVel = maxVel;
}

void LinearProfiler::setMaxAccel(double maxAccel) {
  this->maxAccel = maxAccel;
}

void LinearProfiler::setContraints(double maxVel, double maxAccel) {
  this->maxVel = maxVel;
  this->maxAccel = maxAccel;
}

void LinearProfiler::setP(double kP) {
  posPID->setP(kP);
}

void LinearProfiler::setI(double kI) {
  posPID->setI(kI);
}

void LinearProfiler::setD(double kD) {
  posPID->setD(kD);
}

void LinearProfiler::setVelocityFeedforward(double kFV) {
  this->kFV = kFV;
}

void LinearProfiler::setAccelFeedforward(double kFA) {
  this->kFA = kFA;
}

void LinearProfiler::setFeedforwardGains(double kFV, double kFA) {
  this->kFV = kFV;
  this->kFA = kFA;
}

void LinearProfiler::setGains(double kP, double kI, double kD, double kFV, double kFA) {
  setP(kP);
  setI(kP);
  setD(kP);
  setFeedforwardGains(kFV, kFA);
}

void LinearProfiler::setGains(double kP, double kI, double kD) {
  setGains(kP, kI, kD, kFV, kFA);
}

void LinearProfiler::setOutputRange(double minOutput, double maxOutput) {
  posPID->setOutputRange(minOutput, maxOutput);
}

void LinearProfiler::configIntegral(IntegralType integralType, bool integralZone) {
  posPID->configIntegral(integralType, integralZone);
}

void LinearProfiler::setIntegralZoneRange(double integralZoneRange) {
  posPID->setIntegralZoneRange(integralZoneRange);
}

void LinearProfiler::setTolerance(double positionTolerance, double velocityTolerance) {
  this->posPID->setTolerance(positionTolerance, velocityTolerance);
}

void LinearProfiler::setTarget(double targetPos) {
  this->targetPos = targetPos;
}

void LinearProfiler::setTargetRelative(double targetPos) {
  this->targetPos = measurement + targetPos;
}

double LinearProfiler::getTarget() {
  return targetPos;
}

double LinearProfiler::getP() {
  return posPID->getP();
}

double LinearProfiler::getI() {
  return posPID->getI();
}

double LinearProfiler::getD() {
  return posPID->getD();
}

double LinearProfiler::getVelocityFeedforward() {
  return kFV;
}

double LinearProfiler::getAccelFeedforward() {
  return kFV;
}

PIDController* LinearProfiler::getPID() {
  return posPID;
}

void LinearProfiler::init(double measurement) {
  this->measurement = measurement;

  initialPos = measurement;
  distance = fabs(targetPos - initialPos);
  midPoint = distance / 2;
  flatPoint = (0.5 * maxVel * maxVel / maxAccel);

  if (initialPos < targetPos) {
    dir = 1;
    t_accel = maxAccel;
  } else {
    dir = -1;
    t_accel = -maxAccel;
  }

  if (midPoint > flatPoint) {
    deccelPoint = distance - flatPoint;
  } else {
    flatPoint = midPoint;
    deccelPoint = midPoint;
  }

  t_pos = 0;
  pidSetpoint = initialPos;
  posPID->setSetpoint(pidSetpoint);
  posPID->reset();

  dt = 0;
  vel = 0;
  accel = 0;
  lastTime = pros::millis() - 10;
  lastPos = initialPos;
  lastVel = 0;
}

double LinearProfiler::calculate(double measurement) {
  this->measurement = measurement;

  std::uint32_t time = pros::millis();
  dt = (double)(time - lastTime);

  vel = (measurement - lastPos) / dt;
  accel = (vel - lastVel) / dt;

  //printf("%p: target pos: %f, target t_vel: %f, target t_accel: %f, pos: %d, t_vel: %f\n", this, pidSetpoint, t_vel, t_accel, getSensorValue(), ((double)deltaPos / dt));

  if (t_pos < flatPoint) {
    t_accel = maxAccel;
  } else if (t_pos < deccelPoint) {
    t_accel = 0;
  } else {
    t_accel = -maxAccel;
  }
  t_vel += t_accel * dt;

  if (t_vel > maxVel) {
    t_vel = maxVel;
    t_accel = 0;
  } else if (t_vel < 0) {
    t_vel = 0;
    t_accel = 0;
  }
  t_pos += t_vel * dt;

  pidSetpoint = dir * t_pos + initialPos;
  posPID->setSetpoint(pidSetpoint);
  output = posPID->calculate(measurement) + (kFV * t_vel * dir) + (kFA * t_accel * dir);

  //printf("%p: %f, %f, %f, %f, %f, %f, %f, %f, %f\n", this, targetPos, t_pos, t_vel, t_accel, measurement, vel, accel, output, dt);

  lastTime = time;
  lastPos = measurement;
  lastVel = vel;

  return output;
}

bool LinearProfiler::atTarget() {
  if (fabs(measurement) > deccelPoint) {
    return (t_vel == 0 && posPID->atSetpoint());
  }
  return false;
}

double LinearProfiler::getTargetPos() {
  return pidSetpoint;
}

double LinearProfiler::getTargetVel() {
  return t_vel * dir;
}

double LinearProfiler::getTargetAccel() {
  return t_accel * dir;
}

double LinearProfiler::getPos() {
  return measurement;
}

double LinearProfiler::getVel() {
  return vel;
}

double LinearProfiler::getAccel() {
  return accel;
}

double LinearProfiler::getDeltaTime() {
  return dt;
}
