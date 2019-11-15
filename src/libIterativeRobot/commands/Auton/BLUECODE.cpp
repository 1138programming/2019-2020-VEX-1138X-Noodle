#include "libIterativeRobot/commands/Auton/BLUECODE.h"
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

BLUECODE::BLUECODE() { //* Negative is forward
  //libIterativeRobot::LambdaGroup* slipOffRubber = new libIterativeRobot::LambdaGroup();
  //slipOffRubber->addSequentialCommand(new MoveAnglerTo(-1800, KMaxMotorSpeed, 1500));
  //slipOffRubber->addSequentialCommand(new MoveAnglerTo(0, KMaxMotorSpeed, 1500));
  addSequentialCommand(new FlipOut());
addSequentialCommand(new DriveForTime(KMaxMotorSpeed,KMaxMotorSpeed, 2000));
addSequentialCommand(new DriveForTime(-KMaxMotorSpeed,-KMaxMotorSpeed, 2000));
//   addSequentialCommand(new MoveArmFor(1000, KMaxMotorSpeed));
//   addSequentialCommand(new MoveArmFor(1500, -70));
//   addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.25, -KMaxMotorSpeed*0.25, 3400));
//   //addParallelCommand(slipOffRubber);
//   addParallelCommand(new MoveIntakeFor(4500, KMaxMotorSpeed));
//   addSequentialCommand(new DriveForTime(KMaxMotorSpeed*0.25, KMaxMotorSpeed*0.25, 1700));
//   addSequentialCommand(new DriveForTime(KMaxMotorSpeed*0.25, -KMaxMotorSpeed*0.25, 1450));
//   addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.25, -KMaxMotorSpeed*0.25, 1490));
//   addSequentialCommand(new MoveIntakeFor(1000, KMaxMotorSpeed*0.75))
//   addSequentialCommand(new MoveAnglerTo(-2000, 75, 2000));
//   addParallelCommand(new MoveIntakeFor(1000, KMaxMotorSpeed*0.5));
//   addParallelCommand(new DriveForTime(KMaxMotorSpeed*0.25, KMaxMotorSpeed*0.25, 1000));
}
