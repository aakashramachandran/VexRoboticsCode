//control rollers
#include "main.h"
#include "rollers.h"
#include <iostream>
#include <array>


std::array<int,2> intakeArray = {-600, 0};
int intakeIndex = 0;
std:: array<int, 2> outtakeArray = {300, 0};
int outtakeIndex = 0;
bool intaking;
bool outtaking;

void toggleRollers (){
  if (R2.changedToPressed()){
    if (outtaking) {
      intakeIndex = 0;
      outtaking = false;
    }
    rollers.move_velocity(intakeArray[intakeIndex]);
    intakeIndex++;
    intaking = true;
    if (intakeIndex == intakeArray.size()){
      intakeIndex = 0;
    }
  }

  if (B.changedToPressed()){
    if (intaking) {
      outtakeIndex = 0;
      intaking = false;
    }
    rollers.move_velocity(outtakeArray[outtakeIndex]);
    outtakeIndex++;
    outtaking = true;
    if (outtakeIndex == outtakeArray.size()){
      outtakeIndex = 0;
    }
  }

}


//Autonomous Functions
