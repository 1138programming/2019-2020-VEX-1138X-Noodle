#include "libIterativeRobot/commands/DummyCommand.h"
#include "libIterativeRobot/commands/Delay.h"
#include "libIterativeRobot/Robot.h"

DummyCommand::DummyCommand() {
  //requires(Robot::exampleSubsystem);
}

bool DummyCommand::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void DummyCommand::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  //printf("Dummy command init, status is %d, priority is %d\n", status, priority);
}

void DummyCommand::execute() {
  // Code that runs when this command is scheduled to run
  Command* delay = new Delay(1000);
  delay->run();

  //printf("Address of delay is 0x%x, address of this command is 0x%x\n", delay, this);

  //printf("Dummy command execute, status is %d, priority is %d\n", status, priority);
}

bool DummyCommand::isFinished() {
  return true; // This is the default value anyways, so this method can be removed
}

void DummyCommand::end() {
  // Code that runs when isFinished() returns true.
  //printf("Dummy command end, status is %d, priority is %d\n", status, priority);
}

void DummyCommand::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}
