#include "main.h"
#include "capController.h"

//Sets up array of heights to raise cap_scorer
const int NUM_HEIGHTS = 3;
const int height1 = 0;
const int height2 = 150;
const int height3 = 320;
//Sachin2001
const int flipHeight = 100;
const int heights[NUM_HEIGHTS] = {height1, height2, height3};
int goalHeight = 0;
bool interfere = true;


//sets up a controller that uses the motor's own pid
  //lets you control maximum velocity
  //SHOULD TRY WITH MOTIONPROFILE

void capControl() {
  auto liftController = AsyncControllerFactory::posIntegrated(cap_Scorer);
  if (UP.changedToPressed()){
    liftController.tarePosition();
  }
  if (L1.changedToPressed()) {
      // If the goal height is not at maximum and the up button is pressed, increase the setpoint
      goalHeight++;
      if (goalHeight == 3) goalHeight = 0;
      if (goalHeight ==1) liftController.setMaxVelocity(100);
      else liftController.setMaxVelocity(100);
      liftController.setTarget(heights[goalHeight]);
    }
  else if (L2.changedToPressed()){
      goalHeight--;
      if (goalHeight == -1) goalHeight = 2;
      liftController.setTarget(heights[goalHeight]);
    }

  else if (LEFT.isPressed()){
      cap_Scorer.moveVelocity(-99);
    }
  else if (RIGHT.isPressed()){
      cap_Scorer.moveVelocity(99);
    }
  else if (cap_Scorer.getTargetVelocity() == 99 || cap_Scorer.getTargetVelocity() == -99 || cap_Scorer.getTargetVelocity() == 0){
    cap_Scorer.moveVelocity(0);
    cap_Scorer.setBrakeMode(AbstractMotor::brakeMode::hold);

  }

    /*else if (cap_Scorer.getTargetPosition() != 850 && cap_Scorer.getTargetPosition() != 200 && cap_Scorer.getTargetPosition() != 0){
      cap_Scorer.moveVelocity(0);
      cap_Scorer.setBrakeMode(AbstractMotor::brakeMode::brake);
    }*/


    //pros::lcd::set_text(1, std::to_string(cap_Scorer.getTargetPosition()));




    //pros::delay(10);
}

void autonCapControl(int target, int speed) {
  auto autonLiftController = AsyncControllerFactory::posIntegrated(cap_Scorer);
  autonLiftController.setMaxVelocity(speed);
  autonLiftController.setTarget(target);
}

bool capScorerSettled () {
  if (cap_Scorer.getActualVelocity() == 0) {
    return true;
  }
  return false;
}
