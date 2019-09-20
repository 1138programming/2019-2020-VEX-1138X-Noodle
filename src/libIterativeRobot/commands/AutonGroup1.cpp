#include "libIterativeRobot/commands/AutonGroup1.h"
#include "libIterativeRobot/commands/AutonGroup2.h"
#include "libIterativeRobot/commands/Delay.h"
#include "libIterativeRobot/commands/MoveIntakeFor.h"
#include "libIterativeRobot/commands/BaseLinearMovement.h"
#include "libIterativeRobot/commands/MoveAnglerFor.h"

AutonGroup1::AutonGroup1() {
  addSequentialCommand(new BaseLinearMovement(1000, 1000));
  addParallelCommand(new MoveIntakeFor(2000));
  addSequentialCommand(new Delay(500));
  // addSequentialCommand(new BaseLinearMovement(-1000, -1000));
  // addSequentialCommand(new Delay(500));
  // addSequentialCommand(new BaseLinearMovement(1000, -1000));
  // addSequentialCommand(new MoveAnglerFor(1000));
}
