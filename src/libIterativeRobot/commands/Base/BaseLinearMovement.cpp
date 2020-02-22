#include "libIterativeRobot/commands/Base/BaseLinearMovement.h"
#include "libIterativeRobot/Robot.h"

BaseLinearMovement::BaseLinearMovement(double leftTarget, double rightTarget, double maxVel, double maxAccel, bool absolute) {
  this->leftTarget = leftTarget;
  this->rightTarget = rightTarget;
  this->maxVel = maxVel;
  this->maxAccel = maxAccel;
  this->absolute = absolute;

  printf("BaseLinearMovement: %d %d %d %d\n", leftTarget, rightTarget, maxVel, maxAccel);

  this->priority = 3;
  requires(Robot::base);
}

BaseLinearMovement::BaseLinearMovement(double leftTarget, double rightTarget) : BaseLinearMovement(leftTarget, rightTarget, Robot::base->kDefaultMaxVel, Robot::base->kDefaultMaxAccel, false) {};
BaseLinearMovement::BaseLinearMovement(double leftTarget, double rightTarget, double maxVel, double maxAccel) : BaseLinearMovement(leftTarget, rightTarget, maxVel, maxAccel, false) {};
BaseLinearMovement::BaseLinearMovement(double leftTarget, double rightTarget, bool absolute) : BaseLinearMovement(leftTarget, rightTarget, Robot::base->kDefaultMaxVel, Robot::base->kDefaultMaxAccel, absolute) {};

bool BaseLinearMovement::canRun() {
  //printf("Checking if linear movement can run\n");
  return true;
}

void BaseLinearMovement::initialize() {
  printf("Init linear movement: %d %d %d %d\n", leftTarget, rightTarget, maxVel, maxAccel);

  if (absolute) {
    Robot::base->setLinearTarget(leftTarget, rightTarget);
  } else {
    Robot::base->setLinearTargetRelative(leftTarget, rightTarget);
  }

  printf("Left: %f, Right: %f\n", Robot::base->getLeftSensorValue(), Robot::base->getRightSensorValue());

  Robot::base->setMaxVel(maxVel);
  Robot::base->setMaxAccel(maxAccel);
  Robot::base->initLinearMovement();
}

void BaseLinearMovement::execute() {
  //printf("Running base linear movement\n");
  Robot::base->calculateLinearMovement();
}

bool BaseLinearMovement::isFinished() {
  return Robot::base->atLinearTarget();
}

void BaseLinearMovement::end() {
  printf("Linear movement end\n");
}

void BaseLinearMovement::interrupted() {
  printf("Linear movement interrupted\n");
}

void BaseLinearMovement::blocked() {
  printf("Linear movement blocked\n");
}
