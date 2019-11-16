#include "libIterativeRobot/Robot.h"
#include "libIterativeRobot/commands/Auton/TopRedStack.h"
#include "libIterativeRobot/commands/Auton/AutonGroup2.h"
#include "libIterativeRobot/commands/Miscellaneous/Delay.h"
#include "libIterativeRobot/commands/Intake/MoveIntakeFor.h"
#include "libIterativeRobot/commands/Base/BaseLinearMovement.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerFor.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerTo.h"
#include "libIterativeRobot/commands/Base/DriveForTime.h"
#include "libIterativeRobot/commands/Miscellaneous/FlipOut.h"
#include "libIterativeRobot/commands/Arm/MoveArmFor.h"

TopRedStack::TopRedStack() {
addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 1000));
addSequentialCommand(new Delay(500));
addSequentialCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 1000));
}
