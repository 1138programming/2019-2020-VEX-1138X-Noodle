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
  addSequentialCommand(new MoveArmFor(700, KMaxMotorSpeed));
  addParallelCommand(new MoveIntakeFor(700, -KMaxMotorSpeed));
  addParallelCommand(new MoveAnglerFor(900, KMaxMotorSpeed));
  addSequentialCommand(new MoveAnglerFor(900, -KMaxMotorSpeed));
  addParallelCommand(new MoveIntakeFor(700, KMaxMotorSpeed));
  addSequentialCommand(new MoveArmFor(700, -KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.25, -KMaxMotorSpeed*0.25, 3000));
//addParallelCommand(slipOffRubber);
  addParallelCommand(new MoveIntakeFor(3050, KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed*0.45, KMaxMotorSpeed*0.45, 900));
  addParallelCommand(new MoveIntakeFor(50, -KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.25, KMaxMotorSpeed*0.25, 1400));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.40, -KMaxMotorSpeed*0.40, 1000));
  addSequentialCommand(new MoveAnglerFor(2300, KMaxMotorSpeed));
  addSequentialCommand(new MoveIntakeFor(600, -KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 500));
  
}
