#include "libIterativeRobot/Robot.h"
#include "libIterativeRobot/commands/Auton/AutonGroup1.h"
#include "libIterativeRobot/commands/Auton/AutonGroup2.h"
#include "libIterativeRobot/commands/Miscellaneous/Delay.h"
#include "libIterativeRobot/commands/Intake/MoveIntakeFor.h"
#include "libIterativeRobot/commands/Base/BaseLinearMovement.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerFor.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerTo.h"
#include "libIterativeRobot/commands/Base/DriveForTime.h"
#include "libIterativeRobot/commands/Miscellaneous/Flipout.h"

AutonGroup1::AutonGroup1() {
  /*addSequentialCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 1000));
  addParallelCommand(new MoveIntakeFor(4000, -KMaxMotorSpeed));
  addSequentialCommand(new Delay(500));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 1000));*/

  /*addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 500));
  addParallelCommand(new MoveIntakeFor(500, KMaxMotorSpeed));
  addSequentialCommand(new Delay(500));
  addParallelCommand(new MoveIntakeFor(500, KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 500));
  addParallelCommand(new MoveIntakeFor(500, KMaxMotorSpeed));*/

  addSequentialCommand(new FlipOut());
  addSequentialCommand(new MoveAnglerTo(Robot::angler->kCollectingPosition));
  //addParallelCommand(new mov)
  /*addSequentialCommand(new MoveIntakeFor(5000, KMaxMotorSpeed));
  addSequentialCommand(new Delay(500));
  addParallelCommand(new MoveIntakeFor(500, KMaxMotorSpeed));
  addSequentialCommand(new BaseLinearMovement(1000, 1000));
  addParallelCommand(new MoveIntakeFor(3000, KMaxMotorSpeed));
  addSequentialCommand(new BaseLinearMovement(-1000, -1000));
  addSequentialCommand(new Delay(500));
  addSequentialCommand(new BaseLinearMovement(0, 500));
  addSequentialCommand(new BaseLinearMovement(3000, 3000));
  addSequentialCommand(new Delay(500));
  addSequentialCommand(new MoveAnglerFor(500, 20));
  addSequentialCommand(new Delay(500));
  addSequentialCommand(new MoveIntakeFor(-500, 30));
  addParallelCommand(new BaseLinearMovement(2000, 2000));*/
}
