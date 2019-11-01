#include "libIterativeRobot/commands/Miscellaneous/FlipOut.h"
#include "libIterativeRobot/commands/Arm/MoveArmTo.h"
#include "libIterativeRobot/commands/Arm/MoveArmFor.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerTo.h"

FlipOut::FlipOut() {
  addSequentialCommand(new MoveAnglerTo(-2500, 1000));
  addSequentialCommand(new MoveArmFor(300, 127));
  addSequentialCommand(new MoveArmTo(0, 1000));
  addSequentialCommand(new MoveArmFor(300, 127));
  addSequentialCommand(new MoveArmTo(0, 1000));
  addSequentialCommand(new MoveAnglerTo(0));
}
