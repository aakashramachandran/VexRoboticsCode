#include "main.h"
//Need to include odometry header file to access methods from it
#include "odometry.h"
#include "capController.h"
#include "flywheel.h"
#include "rollers.h"
#include "pros/vision.h"


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 //extern struct MyStruct theVar;
 	double pow1 = 0;
 	double turn1 = 0;
 	double slewRate = .12;
  int speed;





void opcontrol() {
  pros::delay(200);

  extern struct driveInput joyStick;
	extern struct driveInput slewing;
  pros:: Task flywheelPID (flywheelPIDThreadOP, (void*) "Flywheel",  TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "FlywheelControl");
  pros:: Task flywheelShoot (flywheelShootThread, (void*) "FlywheelShoot", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "FlywheelControlShoot");
  pros:: Task visionX (visionXAlignThread, (void*) "XVision",  TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "XVisionControl");


  right_back_drive.moveVoltage(0); right_front_drive.moveVoltage(0);
  right_back_drive.setBrakeMode(AbstractMotor::brakeMode::coast);
  right_front_drive.setBrakeMode(AbstractMotor::brakeMode::coast);
  left_back_drive.moveVoltage(0); left_front_drive.moveVoltage(0);
  left_back_drive.setBrakeMode(AbstractMotor::brakeMode::coast);
  left_front_drive.setBrakeMode(AbstractMotor::brakeMode::coast);
  //pros::delay(1000);
  //testTask.suspend();
	while (true) {


    //getTargetVelocity
    joyStick = getJoystick();
		driveInput slewing = slew(pow1, joyStick.power, turn1, joyStick.turn, slewRate);
		//pros::lcd::set_text(1, std::to_string(joyStick.power));

		pow1 = slewing.power;
		turn1 = slewing.turn;

		//pros::lcd::set_text(1, std::to_string(turn1));

		driver(pow1, turn1);


		capControl();

    toggleRollers();




    pros::lcd::set_text(1, "hello");
    //printf("%f currentReading \n", leftOdom.get()/360);

		pros::delay(25);







	}
}
