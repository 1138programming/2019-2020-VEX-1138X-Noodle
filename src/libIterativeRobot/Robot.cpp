#include "libIterativeRobot/Robot.h"
#include "libIterativeRobot/events/EventScheduler.h"
#include "libIterativeRobot/events/JoystickButton.h"
#include "libIterativeRobot/events/JoystickChannel.h"

#include "libIterativeRobot/commands/Base/StopBase.h"
#include "libIterativeRobot/commands/Angler/StopAngler.h"
#include "libIterativeRobot/commands/Intake/StopIntake.h"
#include "libIterativeRobot/commands/Base/DriveWithJoy.h"
#include "libIterativeRobot/commands/Base/BaseLinearMovement.h"
#include "libIterativeRobot/commands/Base/RotateBase.h"
#include "libIterativeRobot/commands/Miscellaneous/GetData.h"
#include "libIterativeRobot/commands/Miscellaneous/TuneLinearProfile.h"
#include "libIterativeRobot/commands/Miscellaneous/FlipOut.h"
#include "libIterativeRobot/commands/Angler/AnglerControl.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerTo.h"
#include "libIterativeRobot/commands/Intake/IntakeControl.h"
#include "libIterativeRobot/commands/Arm/ArmControl.h"
#include "libIterativeRobot/commands/Arm/MoveArmTo.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerFor.h"
#include "libIterativeRobot/commands/Angler/MoveAnglerTo.h"

#include "libIterativeRobot/commands/LambdaGroup.h"
#include "libIterativeRobot/commands/Auton/AutonGroup1.h"
#include "libIterativeRobot/commands/Auton/AutonGroup2.h"
#include "libIterativeRobot/commands/Auton/JohnsCode.h"
#include "libIterativeRobot/commands/Auton/OtherSide.h"
#include "libIterativeRobot/commands/Auton/TopRedStack.h"
#include "libIterativeRobot/commands/Auton/REDCODE.h"
#include "libIterativeRobot/commands/Auton/Push.h"
#include "libIterativeRobot/commands/Auton/Skills.h"

Robot* Robot::instance = 0;

Angler* Robot::angler = 0;
Arm* Robot::arm = 0;
Base* Robot::base = 0;
Intake* Robot::intake = 0;

AutonChooser* Robot::autonChooser = 0;

pros::Controller* Robot::mainController = 0;
pros::Controller* Robot::partnerController = 0;

Robot::Robot() {
  printf("Overridden robot constructor!\n");

  // Initialize any subsystems
  base = new Base();
  angler  = new Angler();
  intake = new Intake();
  arm = new Arm();

  /**
   * You can tune the base's rotation PID constants here. The numbers are the P, I, and D constants.
   * Tune them in this order:
   * 
   * The P constant is the main one. If the robot is getting to the setpoint, try increasing it. If the robot overshoots its setpoint,
   * decrease it.
   * 
   * The D constant decreases the overshoot and oscillations. You can have a slightly higher P value if you tune the D value correctly
   * 
   * The I constant gets rid of steady state error, or error that doesn't go away with just the P and D constants. For example,
   * if the base doesn't get fully to its setpoint, you might need to increase the I constant. Most likely you won't have to though.
   */
  base->setRotationPIDConstants(0.6, 0, 0);

  autonChooser = AutonChooser::getInstance();

  mainController = new pros::Controller(pros::E_CONTROLLER_MASTER);
  partnerController = new pros::Controller(pros::E_CONTROLLER_PARTNER);

  // Define buttons and channels
  libIterativeRobot::JoystickChannel* RightY = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  libIterativeRobot::JoystickChannel* LeftY = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_LEFT_Y);
  libIterativeRobot::JoystickChannel* RightX = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_RIGHT_X);
  libIterativeRobot::JoystickChannel* LeftX = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_LEFT_X);
  libIterativeRobot::JoystickButton* ArmToLowTower = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_B);
  libIterativeRobot::JoystickButton* ArmToMidTower = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_A);
  libIterativeRobot::JoystickButton* AnglerDown = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_R1);
  libIterativeRobot::JoystickButton* AnglerUp = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_R2);
  libIterativeRobot::JoystickButton* IntakeOpen = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_L2);
  libIterativeRobot::JoystickButton* IntakeClose = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_L1);
  libIterativeRobot::JoystickButton* AnglerToStart = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_DOWN);
  libIterativeRobot::JoystickButton* AnglerToHorizontal = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_RIGHT);
  libIterativeRobot::JoystickButton* AnglerToTop = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_UP);
  libIterativeRobot::JoystickButton* AnglerToBack = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_LEFT);
  libIterativeRobot::JoystickButton* Turn180 = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_X);

  // Add commands to be run to buttons
  LeftX->setThreshold(50);
  LeftY->setThreshold(50);
  DriveWithJoy* driveCommand = new DriveWithJoy();
  LeftX->whilePastThreshold(driveCommand);
  LeftY->whilePastThreshold(driveCommand);

  RightY->setThreshold(20);
  ArmControl* armControl = new ArmControl();
  RightY->whilePastThreshold(armControl);

  //MoveAnglerTo* anglerToCollectingPos = new MoveAnglerTo(angler->kCollectingPosition);
  //RightY->whenPassingThresholdForward(anglerToCollectingPos);

  ArmToLowTower->whenPressed(new MoveArmTo(Arm::kLowTowerPos));
  ArmToMidTower->whenPressed(new MoveArmTo(Arm::kMidTowerPos));

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
  AnglerToTop->whenPressed(new MoveAnglerTo(8000, 100));
  AnglerToBack->whenPressed(new MoveAnglerTo(8000, 100));

  //RotateBase* c = new RotateBase(180, 0.127, KMaxMotorSpeed, 100000);
  //Turn180->whenPressed(c);
}

void Robot::robotInit() {
  printf("Robot created.\n");
  autonChooser->addAutonCommand(new JohnsCode(), "JohnsCode");
  autonChooser->addAutonCommand(new REDCODE(), "REDCODE");
  autonChooser->addAutonCommand(new Push(), "Push" );
  //autonChooser->addAutonCommand(new AutonGroup1(), "AutonGroup1");
  //autonChooser->addAutonCommand(new FlipOut(), "FlipOut");
}

void Robot::autonInit() {
  printf("Auton init, auton command is %x\n", autonChooser->getAutonCommand());
  autonChooser->uninit();
  autonChooser->runAuton();
}

void Robot::autonPeriodic() {
  Motor::periodicUpdate();
}

void Robot::teleopInit() {
  //base->zeroEncoders();

  //RotateBase* c = new RotateBase(180, 0.127, KMaxMotorSpeed, 100000);
  //BaseLinearMovement* c = new BaseLinearMovement(5000, 5000, 2, 0.001, true);
  
  //BaseLinearMovement* c = new BaseLinearMovement(3000, 3000);
  //GetData* c = new GetData();

  //TuneLinearProfile* c = new TuneLinearProfile(base->getLeftProfiler(), LeftFrontBaseData, base, 3000);

  /*libIterativeRobot::LambdaGroup* c = new libIterativeRobot::LambdaGroup();
  TuneLinearProfile* leftBackprop = new TuneLinearProfile(base->getLeftProfiler(), LeftFrontBaseData, base, 3000);
  TuneLinearProfile* rightBackprop = new TuneLinearProfile(base->getRightProfiler(), RightFrontBaseData, base, 3000);

  for (int i = 0; i < 1; i++) {
    c->addSequentialCommand(leftBackprop);
    c->addParallelCommand(rightBackprop);
  }*/

  autonChooser->init();
  //autonChooser->runAuton();
  //FlipOut* c = new FlipOut();
  //c->run();
}

void Robot::teleopPeriodic() {
  //printf("Teleop periodic\n");
  Motor::periodicUpdate();
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
