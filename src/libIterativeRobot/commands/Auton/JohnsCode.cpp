#include "libIterativeRobot/commands/Auton/JohnsCode.h"
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

JohnsCode::JohnsCode() { //*Negitive is forward
  //libIterativeRobot::LambdaGroup* slipOffRubber = new libIterativeRobot::LambdaGroup();
  //slipOffRubber->addSequentialCommand(new MoveAnglerTo(-1800, KMaxMotorSpeed, 1500));
  //slipOffRubber->addSequentialCommand(new MoveAnglerTo(0, KMaxMotorSpeed, 1500));
  addSequentialCommand(new MoveArmFor(1100, KMaxMotorSpeed));
  addParallelCommand(new MoveIntakeFor(2300, -KMaxMotorSpeed));
  addParallelCommand(new MoveAnglerFor(2500, KMaxMotorSpeed));
  addSequentialCommand(new MoveAnglerFor(2400, -KMaxMotorSpeed));
  addParallelCommand(new MoveIntakeFor(2400, KMaxMotorSpeed));
  addSequentialCommand(new MoveArmFor(1100, -KMaxMotorSpeed));
  addParallelCommand(new DriveForTime(-KMaxMotorSpeed*0.25, -KMaxMotorSpeed*0.25, 3000));
  //addParallelCommand(slipOffRubber);
  addParallelCommand(new MoveIntakeFor(3350, KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed*0.40, KMaxMotorSpeed*0.40, 950));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed*0.25, -KMaxMotorSpeed*0.25, 1500));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.40, -KMaxMotorSpeed*0.40, 1500));
  addSequentialCommand(new MoveAnglerFor(2300, KMaxMotorSpeed));
  addSequentialCommand(new MoveIntakeFor(1500, -KMaxMotorSpeed));
  addParallelCommand(new Delay(500));
  addSequentialCommand(new MoveIntakeFor(1000, -KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 500));
  
  
}
