#include "libIterativeRobot/Robot.h"
#include "libIterativeRobot/events/EventScheduler.h"
#include "libIterativeRobot/events/JoystickButton.h"
#include "libIterativeRobot/events/JoystickChannel.h"

#include "libIterativeRobot/commands/StopBase.h"
#include "libIterativeRobot/commands/StopClaw.h"
#include "libIterativeRobot/commands/StopIntake.h"
#include "libIterativeRobot/commands/DriveWithJoy.h"
#include "libIterativeRobot/commands/BaseLinearMovement.h"
#include "libIterativeRobot/commands/ClawControl.h"
#include "libIterativeRobot/commands/IntakeControl.h"
#include "libIterativeRobot/commands/MoveClawFor.h"
#include "libIterativeRobot/commands/MoveClawTo.h"

#include "libIterativeRobot/commands/AutonGroup1.h"
#include "libIterativeRobot/commands/AutonGroup2.h"

Robot* Robot::instance = 0;

Base*  Robot::base = 0;
Claw*   Robot::claw = 0;
Intake*  Robot::intake = 0;

AutonChooser* Robot::autonChooser = 0;

pros::Controller* Robot::mainController = 0;
pros::Controller* Robot::partnerController = 0;

Robot::Robot() {
  printf("Overridden robot constructor!\n");

  // Initialize any subsystems
  base = new Base();
  claw  = new Claw();
  intake = new Intake();

  autonChooser = AutonChooser::getInstance();

  mainController = new pros::Controller(pros::E_CONTROLLER_MASTER);
  partnerController = new pros::Controller(pros::E_CONTROLLER_PARTNER);

  // Define buttons and channels
  libIterativeRobot::JoystickChannel* RightY = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  libIterativeRobot::JoystickChannel* LeftY = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_LEFT_Y);
  libIterativeRobot::JoystickChannel* RightX = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_RIGHT_X);
  libIterativeRobot::JoystickChannel* LeftX = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_LEFT_X);
  libIterativeRobot::JoystickButton* ClawDown = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_R1);
  libIterativeRobot::JoystickButton* ClawUp = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_R2);
  libIterativeRobot::JoystickButton* IntakeOpen = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_L1);
  libIterativeRobot::JoystickButton* IntakeClose = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_L2);
  libIterativeRobot::JoystickButton* ClawToStart = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_DOWN);
  libIterativeRobot::JoystickButton* ClawToHorizontal = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_RIGHT);
  libIterativeRobot::JoystickButton* ClawToTop = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_UP);
  libIterativeRobot::JoystickButton* ClawToBack = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_LEFT);

  // Add commands to be run to buttons
  LeftX->setThreshold(50);
  LeftY->setThreshold(50);
  DriveWithJoy* driveCommand = new DriveWithJoy();
  LeftX->whilePastThreshold(driveCommand);
  LeftY->whilePastThreshold(driveCommand);

  ClawUp->whileHeld(new ClawControl(true));
  ClawDown->whileHeld(new ClawControl(false));

  IntakeControl* intakeOpen = new IntakeControl(true);
  IntakeControl* intakeClose = new IntakeControl(false);
  IntakeOpen->whenPressed(intakeOpen);
  IntakeOpen->whenPressed(intakeClose, libIterativeRobot::Action::STOP);
  IntakeClose->whenPressed(intakeClose);
  IntakeClose->whenPressed(intakeOpen, libIterativeRobot::Action::STOP);
  IntakeOpen->whenReleased(intakeOpen, libIterativeRobot::Action::STOP);
  IntakeClose->whenReleased(intakeClose, libIterativeRobot::Action::STOP);

  ClawToStart->whenPressed(new MoveClawTo(0));
  ClawToHorizontal->whenPressed(new MoveClawTo(680));
  ClawToTop->whenPressed(new MoveClawTo(1520));
  ClawToBack->whenPressed(new MoveClawTo(2360));
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
