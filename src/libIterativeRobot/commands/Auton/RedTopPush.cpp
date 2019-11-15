#include "libIterativeRobot/commands/Auton/AutonGroup2.h"
#include "libIterativeRobot/commands/Miscellaneous/Delay.h"
#include "libIterativeRobot/commands/Base/DriveForTime.h"

AutonGroup2::AutonGroup2() {//*Negitive is forward
addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 1200)); 
}
