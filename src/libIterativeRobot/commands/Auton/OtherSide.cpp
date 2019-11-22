#include "libIterativeRobot/commands/Auton/OtherSide.h"
#include "libIterativeRobot/commands/Auton/AutonGroup1.h"
#include "libIterativeRobot/commands/Auton/AutonGroup2.h"
#include "libIterativeRobot/commands/Miscellaneous/Delay.h"
#include "libIterativeRobot/commands/Intake/MoveIntakeFor.h"
#include "libIterativeRobot/commands/Base/BaseLinearMovement.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerFor.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerTo.h"
#include "libIterativeRobot/commands/Base/DriveForTime.h"
#include "libIterativeRobot/commands/Miscellaneous/FlipOut.h"
#include "libIterativeRobot/commands/Miscellaneous/Delay.h"
#include "libIterativeRobot/commands/Arm/MoveArmFor.h"
#include "libIterativeRobot/commands/LambdaGroup.h"

OtherSide::OtherSide() { //*Negitive is forward
  //libIterativeRobot::LambdaGroup* slipOffRubber = new libIterativeRobot::LambdaGroup();
  //slipOffRubber->addSequentialCommand(new MoveAnglerTo(-1800, KMaxMotorSpeed, 1500));
  //slipOffRubber->addSequentialCommand(new MoveAnglerTo(0, KMaxMotorSpeed, 1500));
  addSequentialCommand(new MoveArmFor(1100, KMaxMotorSpeed));
  addSequentialCommand(new Delay(400));
  addSequentialCommand(new MoveArmFor(1100, -KMaxMotorSpeed));
  addParallelCommand(new DriveForTime(-KMaxMotorSpeed*0.25, -KMaxMotorSpeed*0.25, 3400));
  //addParallelCommand(slipOffRubber);
  addParallelCommand(new MoveIntakeFor(4600, KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed*0.50, KMaxMotorSpeed*0.50, 950));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.25, KMaxMotorSpeed*0.25, 13));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.25, -KMaxMotorSpeed*0.25, 1600));
  addSequentialCommand(new MoveAnglerTo(-2200, 85, 2000));
  addParallelCommand(new MoveIntakeFor(1000, -50));
  addSequentialCommand(new MoveIntakeFor(1500, -KMaxMotorSpeed));
  addParallelCommand(new Delay(500));
  addSequentialCommand(new MoveIntakeFor(1000, -KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 950));
  
}
