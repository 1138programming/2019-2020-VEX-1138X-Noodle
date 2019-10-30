#include "libIterativeRobot/commands/Auton/AutonGroup1.h"
#include "libIterativeRobot/commands/Auton/AutonGroup2.h"
#include "libIterativeRobot/commands/Miscellaneous/Delay.h"
#include "libIterativeRobot/commands/Intake/MoveIntakeFor.h"
#include "libIterativeRobot/commands/Base/BaseLinearMovement.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerFor.h"
#include "libIterativeRobot/commands/Base/DriveForTime.h"

AutonGroup1::AutonGroup1() {
  /*addSequentialCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 1000));
  addParallelCommand(new MoveIntakeFor(4000, -KMaxMotorSpeed));
  addSequentialCommand(new Delay(500));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 1000));*/

  addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 500));
  addParallelCommand(new MoveIntakeFor(500, KMaxMotorSpeed));
  addSequentialCommand(new Delay(500));
  addParallelCommand(new MoveIntakeFor(500, KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 500));
  addParallelCommand(new MoveIntakeFor(500, KMaxMotorSpeed));
}
