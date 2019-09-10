#include "libIterativeRobot/Robot.h"
#include "libIterativeRobot/events/EventScheduler.h"
#include "libIterativeRobot/events/JoystickButton.h"
#include "libIterativeRobot/events/JoystickChannel.h"

#include "libIterativeRobot/commands/StopBase.h"
#include "libIterativeRobot/commands/StopAngler.h"
#include "libIterativeRobot/commands/StopIntake.h"
#include "libIterativeRobot/commands/DriveWithJoy.h"
#include "libIterativeRobot/commands/BaseLinearMovement.h"
#include "libIterativeRobot/commands/AnglerControl.h"
#include "libIterativeRobot/commands/IntakeControl.h"
#include "libIterativeRobot/commands/MoveAnglerFor.h"
#include "libIterativeRobot/commands/MoveAnglerTo.h"

#include "libIterativeRobot/commands/AutonGroup1.h"
#include "libIterativeRobot/commands/AutonGroup2.h"

Robot* Robot::instance = 0;

Base*  Robot::base = 0;
Angler*   Robot::angler = 0;
Intake*  Robot::intake = 0;

AutonChooser* Robot::autonChooser = 0;

pros::Controller* Robot::mainController = 0;
pros::Controller* Robot::partnerController = 0;

Robot::Robot() {
  printf("Overridden robot constructor!\n");

  // Initialize any subsystems
  base = new Base();
  angler  = new Angler();
  intake = new Intake();

  autonChooser = AutonChooser::getInstance();

  mainController = new pros::Controller(pros::E_CONTROLLER_MASTER);
  partnerController = new pros::Controller(pros::E_CONTROLLER_PARTNER);

  // Define buttons and channels
  libIterativeRobot::JoystickChannel* RightY = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  libIterativeRobot::JoystickChannel* LeftY = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_LEFT_Y);
  libIterativeRobot::JoystickButton* AnglerUp = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_R1);
  libIterativeRobot::JoystickButton* AnglerDown = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_R2);
  libIterativeRobot::JoystickButton* IntakeOpen = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_L1);
  libIterativeRobot::JoystickButton* IntakeClose = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_L2);
  libIterativeRobot::JoystickButton* AnglerToStart = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_DOWN);
  libIterativeRobot::JoystickButton* AnglerToHorizontal = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_RIGHT);
  libIterativeRobot::JoystickButton* AnglerToTop = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_UP);
  libIterativeRobot::JoystickButton* AnglerToBack = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_LEFT);

  // Add commands to be run to buttons
  RightY->setThreshold(50);
  LeftY->setThreshold(50);
  DriveWithJoy* driveCommand = new DriveWithJoy();
  RightY->whilePastThreshold(driveCommand);
  LeftY->whilePastThreshold(driveCommand);

  AnglerUp->whileHeld(new AnglerControl(true));
  AnglerDown->whileHeld(new AnglerControl(false));

  IntakeControl* intakeOpen = new IntakeControl(true);
  IntakeControl* intakeClose = new IntakeControl(false);
  IntakeOpen->whenPressed(intakeOpen);
  IntakeOpen->whenPressed(intakeClose, libIterativeRobot::Action::STOP);
  IntakeClose->whenPressed(intakeClose);
  IntakeClose->whenPressed(intakeOpen, libIterativeRobot::Action::STOP);
  IntakeOpen->whenReleased(intakeOpen, libIterativeRobot::Action::STOP);
  IntakeClose->whenReleased(intakeClose, libIterativeRobot::Action::STOP);

  AnglerToStart->whenPressed(new MoveAnglerTo(0));
  AnglerToHorizontal->whenPressed(new MoveAnglerTo(680));
  AnglerToTop->whenPressed(new MoveAnglerTo(1520));
  AnglerToBack->whenPressed(new MoveAnglerTo(2360));
}

void Robot::robotInit() {
  printf("Robot created.\n");
  //autonChooser->addAutonCommand(new AutonGroup1(), "AutonGroup1");
  autonChooser->addAutonCommand(new BaseLinearMovement(1000, 1000), "Linear movement test");
}

void Robot::autonInit() {
  // autonChooser->uninit();
  // autonChooser->getAutonCommand()->run();
}

void Robot::autonPeriodic() {
  Motor::periodicUpdate();
  PIDController::loopAll();
}

void Robot::teleopInit() {
  BaseLinearMovement* c = new BaseLinearMovement(1000, 1000);
  c->run();
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
