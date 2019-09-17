#include "libIterativeRobot/commands/BaseLinearMovement.h"
#include "libIterativeRobot/Robot.h"

BaseLinearMovement::BaseLinearMovement(int leftTarget, int rightTarget, bool absolute) {
  this->leftTarget = leftTarget;
  this->rightTarget = rightTarget;
  this->absolute = absolute;

  this->priority = 3;

  requires(Robot::base);
}

bool BaseLinearMovement::canRun() {
  printf("Checking if linear movement can run\n");
  return true;
}

void BaseLinearMovement::initialize() {
  printf("Init linear movement\n");
  if (absolute) {
    Robot::base->setLinearTarget(leftTarget, rightTarget);
  } else {
    Robot::base->setLinearTargetRelative(leftTarget, rightTarget);
  }

  Robot::base->initLinearMovement();
}

void BaseLinearMovement::execute() {
  printf("Running base linear movement\n");
  Robot::base->updateLinearMovement();
}

bool BaseLinearMovement::isFinished() {
  return Robot::base->atLinearTarget();
}

void BaseLinearMovement::end() {
  printf("Linear movement end\n");
  Robot::base->stopLinearMovement();
}

void BaseLinearMovement::interrupted() {
  printf("Linear movement interrupted\n");
  Robot::base->stopLinearMovement();
}

void BaseLinearMovement::blocked() {

}
