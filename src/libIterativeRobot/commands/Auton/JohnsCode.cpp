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
#include "libIterativeRobot/commands/Arm/MoveArmFor.h"

JohnsCode::JohnsCode() { //* Negative is forward
  addSequentialCommand(new MoveArmFor (1000, KMaxMotorSpeed));
  addParallelCommand(new MoveAnglerFor(1500, 50));
  addParallelCommand(new MoveIntakeFor (2500, -KMaxMotorSpeed));
  addParallelCommand(new MoveAnglerFor(1500, -50));
  addParallelCommand(new MoveArmFor (1500, -70));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.25, -KMaxMotorSpeed*0.25, 500));
  addParallelCommand(new MoveIntakeFor(2000, KMaxMotorSpeed));
  addSequentialCommand(new MoveIntakeFor(2000, KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.25, -KMaxMotorSpeed*0.25, 500));
  addParallelCommand(new MoveIntakeFor(2000, KMaxMotorSpeed));
  addSequentialCommand(new MoveIntakeFor(2000, KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.25, -KMaxMotorSpeed*0.25, 500));
  addParallelCommand(new MoveIntakeFor(2000, KMaxMotorSpeed));
  addSequentialCommand(new MoveIntakeFor(2000, KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed*0.25, -KMaxMotorSpeed*0.25, 500));
  addParallelCommand(new MoveIntakeFor(2000, KMaxMotorSpeed));
  addSequentialCommand(new MoveIntakeFor(2000, KMaxMotorSpeed));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed*0.25, KMaxMotorSpeed*0.25, 2500));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed*0.25, KMaxMotorSpeed*0.25, 3500));
  addSequentialCommand(new MoveAnglerFor(3500, 50));
  addParallelCommand(new MoveIntakeFor(2000, -KMaxMotorSpeed));

}
