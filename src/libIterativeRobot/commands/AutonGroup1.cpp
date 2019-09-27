#include "libIterativeRobot/commands/AutonGroup1.h"
#include "libIterativeRobot/commands/AutonGroup2.h"
#include "libIterativeRobot/commands/Delay.h"
#include "libIterativeRobot/commands/MoveIntakeFor.h"
#include "libIterativeRobot/commands/BaseLinearMovement.h"
#include "libIterativeRobot/commands/MoveClawFor.h"
#include "libIterativeRobot/commands/DriveForTime.h"

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
  
  
  
  
  // addSequentialCommand(new BaseLinearMovement(-1000, -1000));
  // addSequentialCommand(new Delay(500));
  // addSequentialCommand(new BaseLinearMovement(1000, -1000));
  // addSequentialCommand(new MoveClawFor(1000));
}

