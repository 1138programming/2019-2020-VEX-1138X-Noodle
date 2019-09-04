#include "abstractBaseClasses/MotionProfiler.h"

MotionProfiler::MotionProfiler(Motor* leftOutputMotor, Motor* rightOutputMotor, float leftKp, float leftKi, float leftKd, float rightKp, float rightKi, float rightKd) {
  this->leftOutputMotor = leftOutputMotor;
  this->rightOutputMotor = rightOutputMotor;

  leftPosPID = new PIDController(leftKp, leftKi, leftKd);
  leftPosPID = new PIDController(rightKp, rightKi, rightKd);
}

MotionProfiler::MotionProfiler(Motor* leftOutputMotor, Motor* rightOutputMotor) {
  this->leftOutputMotor = leftOutputMotor;
  this->rightOutputMotor = rightOutputMotor;

  leftPosPID = new PIDController(0.45, 0, 0);
  leftPosPID = new PIDController(0.45, 0, 0);
}

void MotionProfiler::setPIDConstants(float leftKp, float leftKi, float leftKd, float rightKp, float rightKi, float rightKd) {
  leftPosPID->setKp(leftKp);
  leftPosPID->setKi(leftKi);
  leftPosPID->setKd(leftKd);
  rightPosPID->setKp(rightKp);
  rightPosPID->setKi(rightKi);
  rightPosPID->setKd(rightKd);
}

void MotionProfiler::setSetpoints(int leftSetpoint, int rightSetpoint) {
  this->leftSetpoint = leftSetpoint;
  this->rightSetpoint = rightSetpoint;
}

void MotionProfiler::setSetpointsRelative(int leftSetpoint, int rightSetpoint) {

}

int MotionProfiler::getLeftSensorValue() {
  if (leftOutputMotor == NULL) {
    return leftSensorValue;
  }
  return (int)leftOutputMotor->getEncoderValue();
}

int MotionProfiler::getRightSensorValue() {
  if (rightOutputMotor == NULL) {
    return rightSensorValue;
  }
  return (int)rightOutputMotor->getEncoderValue();
}

void MotionProfiler::initMovement() {
  // if (absolute) {
  //   leftPosPID->setSetpoint(leftSetpoint);
  //   rightPosPID->setSetpoint(rightSetpoint);
  // } else {
  //   leftPosPID->setSetpointRelative(leftSetpoint);
  //   rightPosPID->setSetpointRelative(rightSetpoint);
  // }
  resetEncoders();

  this->leftSetpoint = leftSetpoint;
  this->rightSetpoint = rightSetpoint;

  int midpoint = abs(leftSetpoint / 2);
  int flatPoint = (0.5 * ((maxVel / accel) + 1) * (maxVel / accel)) * accel;
  if (midpoint < flatPoint) {
    leftDeccelPoint = midpoint;
  } else {
    leftDeccelPoint = abs(leftSetpoint) - flatPoint;
  }

  midpoint = abs(rightSetpoint / 2);
  if (midpoint < flatPoint) {
    rightDeccelPoint = midpoint;
  } else {
    rightDeccelPoint = abs(rightSetpoint) - flatPoint;
  }

  if (leftSetpoint > (int)getLeftEncoderValue()) {
    leftAccel = accel;
  } else {
    leftAccel = -accel;
  }

  if (rightSetpoint > (int)getRightEncoderValue()) {
    rightAccel = accel;
  } else {
    rightAccel = -accel;
  }

  //printf("Left accel is %f, right accel is %f\n", leftAccel, rightAccel);
  //printf("Left deccel point is %d and right deccel point is %d\n", leftDeccelPoint, rightDeccelPoint);

  leftSetpoint = 0;
  rightSetpoint = 0;

  leftPosPID->setSetpoint(0);
  rightPosPID->setSetpoint(0);

  leftPosPID->enable();
  rightPosPID->enable();
  //leftVelPID->enable();
  //rightVelPID->enable();

  // vel = 0;

  // Loop the position PIDs once so that they have a useful output to give to the velocity PIDs
  //leftPosPID->loop();
  //rightPosPID->loop();
  // if (absolute) {
  //   velPID->setSetpoint(target);
  // } else {
  //   velPID->setSetpointRelative(target);
  // }
  //lastTime = pros::millis();
  //lastPos = getRightEncoderValue();
}

// void MotionProfiler::updateMovement() {
//   if (abs((int)leftSetpoint) < leftDeccelPoint) {
//     leftVel += leftAccel;
//     if (leftAccel > 0) {
//       if (leftVel > maxVel)
//         leftVel = maxVel;
//     } else {
//       if (leftVel < -maxVel)
//         leftVel = -maxVel;
//     }
//   } else {
//     leftVel -= leftAccel;
//     if (leftAccel > 0) {
//       if (leftVel < 0)
//       leftVel = 0;
//     } else {
//       if (leftVel > 0)
//         leftVel = 0;
//     }
//   }

//   if (abs((int)rightSetpoint) < rightDeccelPoint) {
//     rightVel += rightAccel;
//     if (rightAccel > 0) {
//       if (rightVel > maxVel)
//         rightVel = maxVel;
//     } else {
//       if (rightVel < -maxVel)
//         rightVel = -maxVel;
//     }
//   } else {
//     rightVel -= rightAccel;
//     if (rightAccel > 0) {
//       if (rightVel < 0)
//       rightVel = 0;
//     } else {
//       if (rightVel > 0)
//         rightVel = 0;
//     }
//   }

//   leftSetpoint += leftVel;
//   rightSetpoint += rightVel;

//   //printf("Left vel is %f, setpoint is %f, and sensor value is %d\n", leftVel, leftSetpoint, (int)getLeftEncoderValue());
//   //printf("Left enc value is %d and right enc value is %d\n", (int)getLeftEncoderValue(), (int)getRightEncoderValue());

//   //printf("%f, %d, %d, %f, %d, %d\n", leftVel, (int)leftSetpoint, (int)getLeftEncoderValue(), rightVel, (int)leftSetpoint, (int)getRightEncoderValue());
//   //printf("%d\n", (int)(getLeftEncoderValue() - getRightEncoderValue()));

//   leftPosPID->setSetpoint((int)leftSetpoint);
//   rightPosPID->setSetpoint((int)rightSetpoint);

//   //pros::delay(5);
//   //printf("Left side rpm is %f and right side rpm is %f\n", leftFrontBaseMotor->getMotorObject()->get_actual_velocity(), rightFrontBaseMotor->getMotorObject()->get_actual_velocity());

//   // Passes encoder values to the position PIDs
//   //leftPosPID->setSensorValue((int)getLeftEncoderValue());
//   //rightPosPID->setSensorValue((int)getRightEncoderValue());

//   // Passes the position PIDs' outputs to the velocity PIDs as their setpoints
//   //leftVelPID->setSetpoint(leftPosPID->getOutput());
//   //rightVelPID->setSetpoint(rightPosPID->getOutput());

//   // Passes velocitie values to the velocity PIDs
//   //leftVelPID->setSensorValue((int)leftFrontBaseMotor->getMotorObject()->get_actual_velocity());
//   //rightVelPID->setSensorValue((int)rightFrontBaseMotor->getMotorObject()->get_actual_velocity());

//   // Moves the base using the velocity PIDs' outputs
//   //moveBase(leftVelPID->getOutput(), rightVelPID->getOutput());
//   //int deltaTime = pros::millis() - lastTime;
//   //double deltaPos = getRightEncoderValue() - lastPos;

//   //printf("Delta time is %d\n", deltaTime);
//   //printf("Delta pos is %f\n", deltaPos);
//   //int vel = (int)(1000 * deltaPos / deltaTime);
//   //printf("Velocity is %d\n", vel);

//   // velPID->setSensorValue(vel);
//   // velPID->loop();
//   // int output = velPID->getOutput();
//   // moveBase(output, output);

//   //moveBase(60, 60);

//   //lastTime = pros::millis();
//   //lastPos = getRightEncoderValue();

//   //basePIDController->setSensorValue((int)getRightEncoderValue());
//   //printf("Enc pos: %d\n", (int)getRightEncoderValue());
//   //printf("Target is %d\n", basePIDController->getSetpoint());
//   //basePIDController->loop();
//   //int output = reverseThreshold(-basePIDController->getOutput());
//   //int output = basePIDController->getOutput();
//   //printf("PID output is %d\n", output);
//   //int gyroCorrection = baseGyro->get_value() * 0.11;
//   //moveBase((int)(output + gyroCorrection), (int)(output - gyroCorrection));
//   //moveBase(output, output);
// }

// // bool Base::baseAtTarget() {
// //   return abs(leftFrontBaseMotor->getMotorObject()->get_target_position() - leftFrontBaseMotor->getMotorObject()->get_position()) <= 3; // Tune threshold and make a varaible
// // }

// bool MotionProfiler::profilerAtTarget() {
//   //return leftPosPID->atSetpoint() && rightPosPID->atSetpoint();
//   if (abs((int)getLeftEncoderValue()) > leftDeccelPoint && abs((int)getRightEncoderValue()) > rightDeccelPoint) {
//     if (leftVel == 0 && rightVel == 0) {
//       if (leftPosPID->atSetpoint() && rightPosPID->atSetpoint())
//         return true;
//     }
//   }
//   return false;
// }

// void MotionProfiler::stopMovement() {
//   //leftPosPID->stop();
//   //rightPosPID->stop();
//   leftPosPID->disable();
//   rightPosPID->disable();
//   //leftVelPID->disable();
//   //rightVelPID->disable();
// }