#include "main.h"
#include "flywheel.h"
#include "capController.h"

const int indexFlip[2] = {-390, 0};
int t;
int i;
int velocity = 487;
double kP = 20;
double kD = 0;
double kI = 5;
int target = 2250;
int error;

int derivative;
int prevError = 0;
int integral;
int voltage;
int cSpeed;
int pSpeed = 0;
int tSpeed;
int setTarget = target;
int prevVoltage;

int threshold = 100000; //threshold for bang bang
int rpmError, targetRPM, currentRPM;
int currentReading;
double kSF = 1300;
double kF = 3.83375; //Calculate this
int previousReading = 0;
double motorPower1;
double pidCorrection;
int xCoord;
//int time;
/*void takeReading (void *p ){

  currentReading= sensor.get();
  pros::delay(50);

  printf("%d currentReading \n", currentReading);
}*/





void turnDrive(int i){
  //if i > 0 turn left //if i < 0 turn right
  right_back_drive.moveVelocity(i); left_back_drive.moveVelocity(-i);
  right_front_drive.moveVelocity(i); left_front_drive.moveVelocity(-i);
}

void visionXAlignThread (void *params) {
  while (true){
    if (R1.isPressed() && vis.get_object_count() != 0){

      for (int i = 0; i < 8; i++){
        if (abs(vis.get_by_sig(i, 1).x_middle_coord) < 80){
          xCoord = vis.get_by_sig(i, 1).x_middle_coord;
        }
      }

      int yCoord = vis.get_by_sig(0,1).y_middle_coord;
      pros::lcd::set_text(2, std::to_string(xCoord));
      pros::lcd::set_text(2, vis.get_by)



      if (xCoord > 20) turnDrive(15);
      else if (xCoord < -20) turnDrive(-15);
      else turnDrive(0);
    }



    pros::delay(20);
  }

}

void flywheelPIDThreadOP (void *params){
    target = 2250;
    okapi::MedianFilter<5> medianFilter;
    while (true){

      cSpeed = -medianFilter.filter(sensor.get());
      tSpeed = 60*(((cSpeed-pSpeed)/360.0)*20*5);
      //#revs/20ms =
      error = target - tSpeed;
      integral += error;
      derivative = error - prevError;
      prevError = error;
      if (error == 0){
        integral = 0;
      }
      pidCorrection = kP*error + kD*derivative + kI*integral;


      if (error <  100){
        motorPower1 = kSF + (kF * target) + pidCorrection;

      }

      else {
        motorPower1 = 12000;
      }
      flywheel.moveVoltage(motorPower1);
      //flywheel.moveVelocity(440);

      printf("%d Error \n", error);
      printf("%f motorPower \n", motorPower1);








      pSpeed = cSpeed;
      setTarget = target;


      pros::delay(50);

      //time += 20;

    }
  }


void flywheelPIDThreadAuton (void *params){




  okapi::MedianFilter<5> medianFilter;
    while (true){

      cSpeed = -medianFilter.filter(sensor.get());
      tSpeed = 60*(((cSpeed-pSpeed)/360.0)*50*5);
      pros::lcd::set_text(1, "Current Velocity: " + std::to_string(tSpeed));
      pros::lcd::set_text(2, "Target: " + std::to_string(target));
      pros::lcd::set_text(3, "Error: " + std::to_string(target-tSpeed));
      pros::lcd::set_text(4, "Voltage: " + std::to_string(voltage));
      pros::lcd::set_text(6, "Previous Voltage: " + std::to_string(prevVoltage));

      //PID
      //printf("%d Error \n", error);

      error = target - tSpeed;
      integral = integral + error;

      if (error == 0){
        integral = 0;
      }

      derivative = error - prevError;
      prevError = error;

      voltage += kP*error + kD*derivative + kI*integral;
      if (voltage < 0) voltage = 0;
      if (voltage > 12000) voltage = 12000;
      pSpeed = cSpeed;
      if (voltage != 0) prevVoltage = voltage;

      flywheel.moveVoltage(-voltage);
      //flywheel.moveVoltage(-12000);
}







      /*currentRPM = ((currentReading - previousReading)/50);

      rpmError = targetRPM-currentRPM;

      if (abs(rpmError) >  threshold){
        motorPower = kSF + (kF * targetRPM) + pidCorrection;
        flywheel.moveVoltage(-motorPower);
      }
      else{
        flywheel.moveVoltage(-12000);
      }*/

      //pros::delay(10);







void autonSingleShot() {
  auto autonIndexController = AsyncControllerFactory::posIntegrated(indexer);
  autonIndexController.setTarget(150);
  pros::delay(150);
  autonIndexController.setTarget(0);
}
void autonDoubleShot() {
  auto autonIndexController = AsyncControllerFactory::posIntegrated(indexer);
  autonIndexController.setTarget(150);
  pros::delay(200);
  //rollers.moveVelocity(-600);
  autonIndexController.setTarget(0);
  autonCapControl(57, 50);
  pros::delay(300);//200
  autonIndexController.setTarget(150);
  pros::delay(300);
  //rollers.moveVelocity(-600);
  autonIndexController.setTarget(0);
  autonCapControl(0, 30);
}



void flywheelShootThread (void*params) {
  while (true){
    auto indexController = AsyncControllerFactory::posIntegrated(indexer);
    if (R1.changedToPressed()){


      //rollers.setBrakeMode(AbstractMotor::brakeMode::hold);
      //rollers.moveVelocity(0);
      indexController.setTarget(150);
      pros::delay(150);
      //rollers.moveVelocity(-600);
      indexController.setTarget(0);

    }
    else if (X.changedToPressed()){
      //autonCapControl(42);
      indexController.setTarget(150);
      pros::delay(200);
      //rollers.moveVelocity(-600);
      indexController.setTarget(0);
      autonCapControl(43, 50);
      pros::delay(1000);//200
      indexController.setTarget(150);
      pros::delay(1000);
      //rollers.moveVelocity(-600);
      indexController.setTarget(0);
      autonCapControl(0, 30);

    }
    //Single shot from middle tiles (cuts power)
    else if (Y.isPressed()){
      indexController.setTarget(-390);
    }
    else if (A.isPressed()){
      //autonIndexPosition(-300);
      indexController.setTarget(-290);
    }
    else {
      indexController.setTarget(0);
    }
    pros::delay(20);

  }


  /*if (X.isPressed()){
    indexer.moveVelocity(200);
    target = 0;
  }
  else if (DOWN.isPressed()){
    indexer.moveVelocity(200);

  }
  else {
    indexer.moveVelocity(0);
    target = setTarget;
    voltage = prevVoltage;
  }
  */
}




void autonIndexPosition (int target, int speed) {
  auto autonIndexController = AsyncControllerFactory::posIntegrated(indexer);
  autonIndexController.setMaxVelocity(speed);
  autonIndexController.setTarget(target);
}
bool indexerSettled () {
  if (indexer.getActualVelocity() == 0) {
    return true;
  }
  return false;
}
