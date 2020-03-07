#include "libIterativeRobot/commands/Auton/JohnsCode.h"
#include "libIterativeRobot/commands/Auton/AutonGroup1.h"
#include "libIterativeRobot/commands/Auton/AutonGroup2.h"
#include "libIterativeRobot/commands/Miscellaneous/Delay.h"
#include "libIterativeRobot/commands/Intake/MoveIntakeFor.h"
#include "libIterativeRobot/commands/Base/BaseLinearMovement.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerFor.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerTo.h"
#include "libIterativeRobot/commands/Base/DriveForTime.h"
#include "libIterativeRobot/commands/Base/RotateBase.h"
#include "libIterativeRobot/commands/Miscellaneous/FlipOut.h"
#include "libIterativeRobot/commands/Miscellaneous/Delay.h"
#include "libIterativeRobot/commands/Arm/MoveArmFor.h"
#include "libIterativeRobot/commands/LambdaGroup.h"

JohnsCode::JohnsCode() { //*Negative is forward
  addSequentialCommand(new MoveArmFor(2600, KMaxMotorSpeed));
  addParallelCommand(new MoveIntakeFor(2600, -KMaxMotorSpeed));
  addParallelCommand(new MoveAnglerFor(2650, KMaxMotorSpeed));
  addSequentialCommand(new MoveAnglerFor(2700, -KMaxMotorSpeed));
  addParallelCommand(new MoveIntakeFor(2700, KMaxMotorSpeed));
  addSequentialCommand(new MoveArmFor(2650, -KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed*0.50, KMaxMotorSpeed*0.50, 3000)); 
//addParallelCommand(slipOffRubber);
  addParallelCommand(new MoveIntakeFor(3150, KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.50, -KMaxMotorSpeed*0.50, 950));
  addParallelCommand(new MoveIntakeFor(50, -KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed*0.45, -KMaxMotorSpeed*0.45, 1200)); //* The TURN
  addParallelCommand(new MoveAnglerFor(400, KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed*0.50, KMaxMotorSpeed*0.50, 1050)); 
  addSequentialCommand(new MoveAnglerFor(2400, KMaxMotorSpeed));
  addSequentialCommand(new MoveIntakeFor(750, -KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 500));

  /**
   * How to use RotateBase:
   * addSequentialCommand(new RotateBase(180, 0.127, KMaxMotorSpeed, 5000));
   * 
   * The first number is the clockwise angle to rotate to relative to the base's current heading. For example, if you
   * set the target to 180 the base should do a half turn clockwise. If you then run the same command with a target of -190,
   * it should rotate counterclockwise back to where it started
   *
   * The second number is the slew rate. This is the rate at which the motor's speed can change in milliseconds.
   * A rate of 0.127 means the base motors' speed will increase by 0.127 per second. A larger number here will accelerate
   * the base faster when it rotates.
   *
   * The third number is the maximum speed for the base to rotate at. 127 is the maximum, although you might want
   * to decrease this number to reduce overshoot. Another option to reduce overshoot (or undershoot) is to tune the PID
   * constants in the Base subsystem. Remember to always tune P, then D, then I (if necessary)
   * 
   * The fourth number is the time it takes for the command to time out in case it gets stuck for some reason.
   * For example if you hold the base off the ground, the gyro will never reach 180 degrees, so after 5000
   * milliseconds it will stop trying
   * 
   * 
   * If you don't care about any of the last three numbers, you can leave them out like this:
   * addSequentialCommand(new RotateBase(180, 0.127, KMaxMotorSpeed));
   * addSequentialCommand(new RotateBase(180, 0.127));
   * addSequentialCommand(new RotateBase(180));
   * 
   * The defaults for the slew rate, maximum speed, and duration of the command are 0.127, KMaxMotorSpeed, and 5000 respectively
   * 
   * 
   * One last thing to note: When you start the code, keep the robot still since the inertial sensor has to callibrate.
   * If you run an auton whose first command moves the base immediately after starting the robot, it may not work since
   * I made it so that the base will not move while the inertial sensor is callibrating
   */
}
