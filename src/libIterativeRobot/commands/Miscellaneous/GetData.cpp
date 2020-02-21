#include "libIterativeRobot/commands/Miscellaneous/GetData.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

GetData::GetData() {
  requires(Robot::base);
  this->priority = 2;
}

bool GetData::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void GetData::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor

  // Init variables keeping track of the state of the command
  voltage = -127;
  trial = 0;
  lastTime = pros::millis() - 10;
  time = lastTime;
  lastPos = Robot::base->getLeftSensorValue();
  pos = lastPos;
  vel = 0;
  avgVel = 0;
  ramp = 0;
}

void GetData::execute() {
  // Update deltas
  time = pros::millis();
  int dt = (int)(time - lastTime);
  lastTime = time;

  pos = Robot::base->getLeftSensorValue();
  int dpos = pos - lastPos;
  lastPos = pos;

  // If the motor is done ramping up, start collecting data from the trials
  if (ramp > maxRamp) {
    // Run the base at the voltage
    Robot::base->move(voltage, voltage);

    // Calculate velocity from deltas
    vel = (double)dpos / dt;

    // Average velocity, calculated over the trials
    avgVel += vel / maxTrials;

    // Increments trials
    trial++;

    // Increments the voltage once the trials for that voltage are complete
    if (trial >= maxTrials) {
      // Prints voltage and average velocity
      printf("%d, %f\n", voltage, avgVel);

      trial = 0;
      voltage++;
      avgVel = 0;
    }
  } else {
    // Ramp up the motor
    Robot::base->move(voltage, voltage);
    ramp++;
  }
}

bool GetData::isFinished() {
  return voltage >= 128;
}

void GetData::end() {
  // Code that runs when isFinished() returns true.
}

void GetData::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void GetData::blocked() {
}
