#include "libIterativeRobot/commands/Auton/REDCODE.h"
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

REDCODE::REDCODE() { //* Negative is forward
  //libIterativeRobot::LambdaGroup* slipOffRubber = new libIterativeRobot::LambdaGroup();
  //slipOffRubber->addSequentialCommand(new MoveAnglerTo(-1800, KMaxMotorSpeed, 1500));
  //slipOffRubber->addSequentialCommand(new MoveAnglerTo(0, KMaxMotorSpeed, 1500));

addSequentialCommand(new MoveArmFor(1000, KMaxMotorSpeed));addSequentialCommand(new MoveArmFor(1500, -70));
addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.35, -KMaxMotorSpeed*0.35, 3000));
//addParallelCommand(slipOffRubber);
addParallelCommand(new MoveIntakeFor(3700, KMaxMotorSpeed));
addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 1300));
addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.25, KMaxMotorSpeed*0.25, 1420));
addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.75, -KMaxMotorSpeed*0.75, 900));
addSequentialCommand(new MoveAnglerTo(-2000, 70, 2000));
addSequentialCommand(new MoveIntakeFor(1500, -KMaxMotorSpeed*0.5));
addParallelCommand(new Delay(100));
addSequentialCommand(new MoveIntakeFor(500, KMaxMotorSpeed));
addParallelCommand(new DriveForTime(KMaxMotorSpeed*0.25, KMaxMotorSpeed*0.25, 1000));
}
