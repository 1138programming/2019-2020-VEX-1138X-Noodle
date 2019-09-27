#include "libIterativeRobot/Robot.h"
#include "libIterativeRobot/events/EventScheduler.h"
#include "libIterativeRobot/events/JoystickButton.h"
#include "libIterativeRobot/events/JoystickChannel.h"

#include "libIterativeRobot/commands/StopBase.h"
#include "libIterativeRobot/commands/StopClaw.h"
#include "libIterativeRobot/commands/StopLift.h"
#include "libIterativeRobot/commands/DriveWithJoy.h"
#include "libIterativeRobot/commands/BaseLinearMovement.h"
#include "libIterativeRobot/commands/ClawControl.h"
#include "libIterativeRobot/commands/LiftControl.h"
#include "libIterativeRobot/commands/MoveLiftFor.h"
#include "libIterativeRobot/commands/MoveLiftTo.h"

#include "libIterativeRobot/commands/AutonGroup1.h"
#include "libIterativeRobot/commands/AutonGroup2.h"

Robot* Robot::instance = 0;

Base*  Robot::base = 0;
Claw*   Robot::claw = 0;
Lift*  Robot::lift = 0;

AutonChooser* Robot::autonChooser = 0;

pros::Controller* Robot::mainController = 0;
pros::Controller* Robot::partnerController = 0;

Robot::Robot() {
  printf("Overridden robot constructor!\n");

  // Initialize any subsystems
  base = new Base();
  claw  = new Claw();
  lift = new Lift();

  autonChooser = AutonChooser::getInstance();

  mainController = new pros::Controller(pros::E_CONTROLLER_MASTER);
  partnerController = new pros::Controller(pros::E_CONTROLLER_PARTNER);

  // Define buttons and channels
  libIterativeRobot::JoystickChannel* LeftYMain = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_LEFT_Y);
  libIterativeRobot::JoystickChannel* RightXMain = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_RIGHT_X);
  libIterativeRobot::JoystickChannel* LeftYPartner = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_LEFT_Y);
  libIterativeRobot::JoystickChannel* RightYPartner = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  // Add commands to be run to buttons
  LeftYMain->setThreshold(50);
  RightXMain->setThreshold(50);
  DriveWithJoy* driveCommand = new DriveWithJoy();
  LeftYMain->whilePastThreshold(driveCommand);
  RightXMain->whilePastThreshold(driveCommand);

  LiftControl* liftControl = new LiftControl();
  LeftYPartner->whilePastThreshold(liftControl);

  ClawControl* clawControl = new ClawControl();
  RightYPartner->whilePastThreshold(clawControl);
}

void Robot::robotInit() {
  printf("Robot created.\n");
  //autonChooser->addAutonCommand(new AutonGroup1(), "AutonGroup1");
  autonChooser->addAutonCommand(new AutonGroup1(), "Auton test 1");
  autonChooser->addAutonCommand(new BaseLinearMovement(1000, 1000), "Linear movement test");
}

void Robot::autonInit() {
  autonChooser->uninit();
  autonChooser->getAutonCommand()->run();
}

void Robot::autonPeriodic() {
  Motor::periodicUpdate();
  PIDController::loopAll();
}

void Robot::teleopInit() {
  //BaseLinearMovement* c = new BaseLinearMovement(1000, 1000);
  //c->run();
}

void Robot::teleopPeriodic() {
  //printf("Teleop periodic\n");
  Motor::periodicUpdate();
  PIDController::loopAll();
}

void Robot::disabledInit() {
  autonChooser->uninit();
}

void Robot::disabledPeriodic() {
}

Robot* Robot::getInstance() {
    if (instance == NULL) {
        instance = new Robot();
    }
    return instance;
}
