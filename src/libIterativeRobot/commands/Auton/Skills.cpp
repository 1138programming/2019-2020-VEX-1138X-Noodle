#include "libIterativeRobot/commands/Auton/Skills.h"
#include "libIterativeRobot/commands/Miscellaneous/Delay.h"
#include "libIterativeRobot/commands/Base/DriveForTime.h"

Skills::Skills() {
    addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 1200)); 
    addSequentialCommand(new DriveForTime(KMaxMotorSpeed*0.9, K50MotorSpeed*0.9, 500));
}
