#include "main.h"
#include "capController.h"
#include "flywheel.h"
#include "odometry.h"
#include "rollers.h"
int tex = 0;
void redBack () {
  pros::delay(200);
  pros:: Task safeBe (safetyThread, (void*) "safe", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "safeBe");
  pros:: Task drivePID (drivePIDThread, (void*) "drive",  TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "driveControl");
  pros:: Task flywheelPID (flywheelPIDThreadOP, (void*) "Flywheel",  TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "FlywheelControl");

  setRightParams(-41, 0, 200, 1500, true);
  setLeftParams(-41, 0, 200, 1500);
  while (getCompleted() == false) pros::delay(20);
  reset();

  pros::delay(100);

  autonCapControl(150, 100);

  pros::delay(100);



  setRightParams(22, 0, 200, 1000, true);
  setLeftParams(22, 0, 200, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParamsT(6.7, 0, 200, 1000, true);
  setLeftParamsT(-6.7, 0, 200, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(20, 10, 200, 1000, true);
  setLeftParams(20, 10, 200, 1000);
  while (!getMid()) pros::delay(20);
  autonCapControl(320, 100);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(-10, -5, 200, 500, true);
  setLeftParams(-10, -5, 200, 500);
  while (!getMid()) pros::delay(20);
  autonCapControl(0, 100);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(13, 0, 200, 500, true);
  setLeftParams(13, 0, 200, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(-26, 0, 200, 1500, true);
  setLeftParams(-26, 0, 200, 1500);
  while (getCompleted() == false) pros::delay(20);
  reset();
  rollers.moveVelocity(-600);

  setRightParamsT(5.72, 0, 150, 1000, true);
  setLeftParamsT(-5.72, 0, 150, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(18, 0, 170, 1000, true);
  setLeftParams(18, 0, 170, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(-9, 0, 170, 500, true);
  setLeftParams(-9, 0, 170, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(2, 0, 170, 500, true);
  setLeftParams(2, 0, 170, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();



  setRightParamsT(3.6, 0, 150, 750, true);
  setLeftParamsT(-3.6, 0, 150, 750);
  while (getCompleted() == false) pros::delay(20);
  reset();


  autonIndexPosition(150, 200);
  pros::delay(250);
  autonIndexPosition(0, 200);
  flywheelPID.suspend();
  setRightParamsT(2, 0, 150, 750, true);
  setLeftParamsT(-2, 0, 150, 750);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(23, 0, 200, 1000, true);
  setLeftParams(23, 0, 200, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();


  autonIndexPosition(120, 200);

  while (abs(vis.get_by_sig(0, 1).x_middle_coord) > 5 && tex<1000) {
    setRightParamsT(-4.8, 0, 170, 100, true);
    setLeftParamsT(4.8, 0, 170, 100);
    while (getCompleted() == false) pros::delay(20);
    reset();
    tex+=100;
  }
  
  setRightParams(29, 0, 170, 1300, true);
  setLeftParams(29, 0, 170, 1300);
  while (getCompleted() == false) pros::delay(20);
  reset();
  setRightParams(8, 0, 50, 500, true);
  setLeftParams(8, 0, 50, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(-8, 0, 50, 500, true);
  setLeftParams(-8, 0, 50, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();
  pros::delay(100);

  setRightParamsT(-3, 0, 140, 2000, true);
  setLeftParamsT(-18, 0, 140, 2000);
  while (getCompleted() == false) pros::delay(20);
  reset();

  pros::delay(100);

  setRightParams(-21, 0, 170, 1500, true);
  setLeftParams(-21, 0, 170, 1500);
  while (getCompleted() == false) pros::delay(20);
  reset();

  autonCapControl(150, 100);
  rollers.moveVelocity(0);

  setRightParamsT(22, 0, 140, 2000, true);
  setLeftParamsT(7, 0, 140, 2000);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(27, 22, 170, 1300, true);
  setLeftParams(27, 22, 170, 1300);
  while(getMid() == false) pros::delay(20);
  autonCapControl(320, 100);
  while (getCompleted() == false) pros::delay(20);
  reset();


  setRightParams(-8, 0, 170, 500, true);
  setLeftParams(-8, 0, 170, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();
  autonCapControl(0, 100);

  setRightParamsT(9, 0, 150, 1000, true);
  setLeftParamsT(-9, 0, 150, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();
  flywheelPID.suspend();


  setRightParams(23.25, 0, 200, 1000, true);
  setLeftParams(23.25, 0, 200, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();




  setRightParams(10, 0, 100, 500, true);
  setLeftParams(10, 0, 100, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();


  rollers.moveVelocity(-600);*/
  setRightParamsT(-1.5, 0, 200, 500, true);
  setLeftParamsT(1.5, 0, 200, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();
  while (abs(vis.get_by_sig(0, 1).x_middle_coord) > 5) {
    setRightParamsT(-1, 0, 170, 100, true);
    setLeftParamsT(1, 0, 170, 100);
    while (getCompleted() == false) pros::delay(20);
    reset();
  }
  autonDoubleShot();

  reset();
  drivePID.suspend();

}

void redFront () {
  pros::delay(200);
  pros:: Task safeBe (safetyThread, (void*) "safe", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "safeBe");
  pros:: Task drivePID (drivePIDThread, (void*) "drive",  TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "driveControl");
  pros:: Task flywheelPID (flywheelPIDThreadOP, (void*) "Flywheel",  TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "FlywheelControl");


  rollers.moveVelocity(-600);
  setRightParams(29, 0, 170, 1300, true);
  setLeftParams(29, 0, 170, 1300);
  while (getCompleted() == false) pros::delay(20);
  reset();
  setRightParams(8, 0, 50, 500, true);
  setLeftParams(8, 0, 50, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();
  setRightParams(-39, 0, 200, 1500, true);
  setLeftParams(-39, 0, 200, 1500);
  while (getCompleted() == false) pros::delay(20);
  reset();
  setRightParamsT(5.2, 0, 150, 1000, false);
  setLeftParamsT(-5.2, 0, 150, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();


  drivePID.suspend();
  pros::delay(400);
  drivePID.resume();
  autonDoubleShot();
  pros::delay(400);
  reset();

  rollers.moveVelocity(600);
  setRightParamsT(-2.5, 0, 125, 1500, false);
  setLeftParamsT(2.5, 0, 125, 1500);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(18, 0, 100, 2000, false);
  setLeftParams(18, 0, 100, 2000);
  autonIndexPosition(-200, 200);
  while (getCompleted() == false) pros::delay(20);
  reset();

  autonIndexPosition(-390, 100);
  while(indexerSettled() == false) pros::delay(20);
  pros::delay(500);
  setRightParams(-5, -2, 200, 500, false);
  setLeftParams(-5, -2, 200, 500);
  while (getMid() == false) pros::delay(20);
  rollers.moveVelocity(-600);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(-5, -2, 200, 500, false);
  setLeftParams(-5, -2, 200, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();
  //setRightParams(-9, 0, 200, 700, false);
  //setLeftParams(-9, 0, 200, 700);
  //while (getCompleted() == false) pros::delay(20);
  //reset();
  pros::delay(300);
  autonIndexPosition(0, 200);
  while(indexerSettled() == false) pros::delay(20);
  setRightParamsT(-1.0, 0, 125, 1000, false);
  setLeftParamsT(1.0, 0, 125, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();



  drivePID.resume();
  autonDoubleShot();
  pros::delay(300);
  reset();
  flywheelPID.suspend();


  rollers.moveVelocity(300);
  setRightParams(10, 0, 125, 1000, false);
  setLeftParams(10, 0, 125, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParamsT(-4, 0, 200, 800, false);
  setLeftParamsT(4, 0, 200, 800);
  while (getCompleted() == false) pros::delay(20);
  reset();
  rollers.moveVelocity(300);
  flywheelPID.suspend();
  setRightParams(34, 18, 200, 1500, false);
  setLeftParams(34, 18, 200, 1500);
  while (getMid() == false) pros::delay(20);
  autonIndexPosition(-200, 200);
  while (getCompleted() == false) pros::delay(20);
  reset();

  drivePID.suspend();
}

void blueFront(){

    //BLUE BACK AUTON - ADD SECOND CAP + 2 BALLS + Park
    pros::delay(200);
    pros:: Task safeBe (safetyThread, (void*) "safe", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "safeBe");
    pros:: Task drivePID (drivePIDThread, (void*) "drive",  TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "driveControl");
    pros:: Task flywheelPID (flywheelPIDThreadOP, (void*) "Flywheel",  TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "FlywheelControl");


    rollers.moveVelocity(-600);
    setRightParams(29, 0, 170, 1300, true);
    setLeftParams(29, 0, 170, 1300);
    while (getCompleted() == false) pros::delay(20);
    reset();
    setRightParams(8, 0, 50, 500, true);
    setLeftParams(8, 0, 50, 500);
    while (getCompleted() == false) pros::delay(20);
    reset();
    setRightParams(-40, 0, 170, 1500, true);
    setLeftParams(-40, 0, 170, 1500);
    while (getCompleted() == false) pros::delay(20);
    reset();
    setRightParamsT(-5.6, 0, 200, 1000, false);
    setLeftParamsT(5.6, 0, 200, 1000);
    while (getCompleted() == false) pros::delay(20);
    reset();

    pros::delay(100);
    drivePID.resume();
    autonSingleShot();
    pros::delay(100);

    setRightParams(20, 0, 170, 1500, true);
    setLeftParams(20, 0, 170, 1500);
    while (getCompleted() == false) pros::delay(20);
    reset();
    autonSingleShot();

    setRightParams(32, 20, 170, 1500, true);
    setLeftParams(32, 20, 170, 1500);
    while (getCompleted() == false) pros::delay(20);
    reset();

    setRightParamsT(-2, 0, 200, 750, false);
    setLeftParamsT(2, 0, 200, 750);
    while (getCompleted() == false) pros::delay(20);
    reset();

    autonIndexPosition(-200, 200);
    pros::delay(700);
    autonIndexPosition(0, 200);
    pros::delay(200);*/

    setRightParamsT(2, 0, 200, 750, false);
    setLeftParamsT(-2, 0, 200, 750);
    while (getCompleted() == false) pros::delay(20);
    reset();

    
    drivePID.suspend();
    pros::delay(400);
    drivePID.resume();
    autonDoubleShot();
    pros::delay(400);
    reset();

    rollers.moveVelocity(600);
    setRightParamsT(2.9, 0, 125, 1500, false);
    setLeftParamsT(-2.9, 0, 125, 1500);
    while (getCompleted() == false) pros::delay(20);
    reset();

    setRightParams(19.4, 0, 100, 2000, false);
    setLeftParams(19.4, 0, 100, 2000);
    autonIndexPosition(-200, 200);
    while (getCompleted() == false) pros::delay(20);
    reset();

    autonIndexPosition(-390, 100);
    while(indexerSettled() == false) pros::delay(20);
    pros::delay(500);
    setRightParams(-5, -2, 200, 500, false);
    setLeftParams(-5, -2, 200, 500);
    while (getMid() == false) pros::delay(20);
    rollers.moveVelocity(-600);
    while (getCompleted() == false) pros::delay(20);
    reset();
    rollers.moveVelocity(0);

    setRightParams(-5, -2, 200, 500, false);
    setLeftParams(-5, -2, 200, 500);
    while(!getMid()) pros::delay(20);
    rollers.moveVelocity(-600);
    while (getCompleted() == false) pros::delay(20);
    reset();
    //setRightParams(-9, 0, 200, 700, false);
    //setLeftParams(-9, 0, 200, 700);
    //while (getCompleted() == false) pros::delay(20);
    //reset();
    pros::delay(400);
    autonIndexPosition(0, 200);
    while(indexerSettled() == false) pros::delay(20);
    setRightParamsT(1.2, 0, 125, 1000, false);
    setLeftParamsT(-1.2, 0, 125, 1000);
    while (getCompleted() == false) pros::delay(20);
    reset();



    drivePID.resume();
    autonDoubleShot();
    pros::delay(300);
    reset();
    flywheelPID.suspend();

    //setRightParamsT(-1.0, 0, 125, 1000, false);
    //setLeftParamsT(1.0, 0, 125, 1000);
    //while (getCompleted() == false) pros::delay(20);
    //reset();
    rollers.moveVelocity(300);
    setRightParams(19, 0, 125, 1000, false);
    setLeftParams(19, 0, 125, 1000);
    while (getCompleted() == false) pros::delay(20);
    reset();

    setRightParamsT(-4, 0, 200, 800, false);
    setLeftParamsT(4, 0, 200, 800);
    while (getCompleted() == false) pros::delay(20);
    reset();
    rollers.moveVelocity(300);
    flywheelPID.suspend();
    setRightParams(30, 18, 200, 2000, false);
    setLeftParams(30, 18, 200, 1000);
    while (getMid() == false) pros::delay(20);
    autonIndexPosition(-200, 200);
    while (getCompleted() == false) pros::delay(20);
    reset();*/

    flywheelPID.suspend();
    drivePID.suspend();
  }
void blueBack(){

  pros::delay(200);
  pros:: Task safeBe (safetyThread, (void*) "safe", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "safeBe");
  pros:: Task drivePID (drivePIDThread, (void*) "drive",  TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "driveControl");
  pros:: Task flywheelPID (flywheelPIDThreadOP, (void*) "Flywheel",  TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "FlywheelControl");

  setRightParams(-42, 0, 200, 1500, true);
  setLeftParams(-42, 0, 200, 1500);
  while (getCompleted() == false) pros::delay(20);
  reset();

  pros::delay(100);

  autonCapControl(150, 100);

  pros::delay(100);



  setRightParams(19, 0, 200, 1000, true);
  setLeftParams(19, 0, 200, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParamsT(-6.6, 0, 200, 1000, true);
  setLeftParamsT(6.6, 0, 200, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(23, 10, 200, 1000, true);
  setLeftParams(23, 10, 200, 1000);
  while (!getMid()) pros::delay(20);
  autonCapControl(320, 100);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(-10, -5, 200, 500, true);
  setLeftParams(-10, -5, 200, 500);
  while (!getMid()) pros::delay(20);
  autonCapControl(0, 100);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(13, 0, 200, 500, true);
  setLeftParams(13, 0, 200, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(-26, 0, 200, 1300, true);
  setLeftParams(-26, 0, 200, 1300);
  while (getCompleted() == false) pros::delay(20);
  reset();
  rollers.moveVelocity(-600);

  setRightParamsT(-5.72, 0, 150, 800, true);
  setLeftParamsT(5.72, 0, 150, 800);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(17, 0, 200, 800, true);
  setLeftParams(17, 0, 200, 800);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(-6, 0, 170, 500, true);
  setLeftParams(-6, 0, 170, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();

  flywheelPID.suspend();


  setRightParamsT(-5.3, 0, 200, 1000, true);
  setLeftParamsT(5.3, 0, 200, 1000);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(10, 0, 200, 500, true);
  setLeftParams(10, 0, 200, 500);
  while (getCompleted() == false) pros::delay(20);
  reset();

  setRightParams(21, 0, 200, 2000, true);
  setLeftParams(21, 0, 200, 2000);
  while (getCompleted() == false) pros::delay(20);
  reset();
  }

void autonomous() {
  //blueFront();___int_least16_t_defined
  //redBack();

  redBack();
}
