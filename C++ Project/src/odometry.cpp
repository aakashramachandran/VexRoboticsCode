#include "main.h"
#include "odometry.h"
#include <stdio.h>


int safe = 0;


driveInput joyStick;
driveInput slewing;
driveOutput pos;

pidParams leftParam;
pidParams rightParam;

double dkP = 12;
double dkD =15;
double dkI = 0;//0.0009;

double lError;
double rError;
double lDerivative;
double rDerivative;
double lIntegral;
double rIntegral;
double plError;
double prError;

double lVoltage;
double rVoltage;

double slewV = 6;

double plVoltage;
double prVoltage;

double ltime;
double rtime;

double compensate;
double cError;
double pcError;
double cDerivative;
double cIntegral;

int rSettled;
int lSettled;

//get previous speed
double rpV;
double lpV;

//tells if drive finished
bool lCompleted = false;
bool rCompleted = false;
bool lAtMid = false;
bool rAtMid = false;

void safetyThread (void *params){
  while (true){


    safe+=20;

    pros::delay(20);
  }
}

double scale (double val){
  //y = 1.010101010101x^3 -3.083952846181*10^-16x^2 - 0.01010101010101x
  // 1.010101010101*val*val*val - (3.083952846181*pow(10, -6))*val*val - 0.01010101010101*val;
  return val;
}

driveInput getJoystick (){
  double power;
  double turn;

    power = controller.getAnalog(ControllerAnalog::leftY);

    turn = controller.getAnalog(ControllerAnalog::rightX);




  driveInput joyStick = {scale(power), scale(turn)};
	return joyStick;

}

driveInput slew (double p1, double p, double t1, double t, double slewRate) {
    //p = joyStick
    //p1 = motor speed
     //90 - 20 > 5
	 	if (p - p1 > slewRate) {
	 		p1 += slewRate;
	 	}

		// 70 - 50 > 5
		else if (p1 - p > slewRate) {
			p1 -= slewRate;
		}

    else {
      p1 = p;
      if (fabs(p) < slewRate){
        p1 = 0;
        p = 0;
      }
    }

	 	if (t - t1 > slewRate - 0.02) {
	 		t1 += slewRate;
	 	}
		else if (t1 - t > slewRate - 0.02) {
			t1 -= slewRate;
		}
		if (t == 0){
			t1 = 0;
		}


		driveInput slewing = {p1, t1};
		return slewing;
}

void driver (double pow1, double turn1) {
    //If vision align not happening
    if (R1.isPressed() == false){
      pow1 = pow1*(-200); turn1 = turn1*(-200);
  	  right_back_drive.moveVelocity(pow1-turn1);
  	  right_front_drive.moveVelocity(pow1-turn1);
  	  left_back_drive.moveVelocity(pow1+turn1);
  	  left_front_drive.moveVelocity(pow1+turn1);
      if (pow1 == 0 && turn1 == 0){
        //set brake types too?
        right_back_drive.moveVelocity(0);
        right_front_drive.moveVelocity(0);
        left_back_drive.moveVelocity(0);
        left_front_drive.moveVelocity(0);
      }
    }


 }

//Let us get motor values and print to terminal
driveOutput getPos (void){
  double rDelta = rightOdom.get()/360;
  double lDelta = leftOdom.get()/360;
  double rSpeed = rightOdom.get()/360 - rpV;
  rpV = rightOdom.get();
  double lSpeed = leftOdom.get()/360 - lpV;
  lpV = leftOdom.get();
  rDelta = rDelta*3.141592*2.75;
  lDelta = lDelta*3.141592*2.75;
  driveOutput pos = {rDelta, lDelta, rSpeed, lSpeed};
  return pos;
}

void drivePIDLeft(double dtarget, double midPoint, double maxSpeed, double toExec){
  midPoint = -midPoint;
    if (ltime > toExec){
      left_back_drive.moveVoltage(0); left_front_drive.moveVoltage(0);
      left_back_drive.setBrakeMode(AbstractMotor::brakeMode::coast);
      left_front_drive.setBrakeMode(AbstractMotor::brakeMode::coast);
      lSettled += 20;
      if (lSettled >= 500 || ltime > toExec){
        lCompleted = true;
      }
    }
    else {

      if (abs(getPos().l - midPoint) < 3){
        lAtMid = true;
      }
      lError = -dtarget - getPos().l;
      lIntegral += lError;
      if (lError == 0) lIntegral = 0;
      lDerivative = lError - plError;
      plError = lError;
      lVoltage = dkP*lError + dkD*lDerivative + dkI*lIntegral;
      if (lVoltage > maxSpeed) lVoltage = maxSpeed;
      if (lVoltage < -maxSpeed) lVoltage = -maxSpeed;
      // if 50 - 30 > 10, voltage = 40
      // if -50 - -30 < -10 voltage = -40
      if (lVoltage - plVoltage > slewV) lVoltage = plVoltage + slewV;
      else if (lVoltage - plVoltage  < - slewV) lVoltage = plVoltage - slewV;
      left_back_drive.moveVelocity(lVoltage); left_front_drive.moveVelocity(lVoltage);
      ltime+=20;
      plVoltage = lVoltage;
      ///printf("%f Error: \n", lError);
    }
    pros::lcd::set_text(2, std::to_string(lError));

  }



void drivePIDRight(double dtarget, double midPoint, double maxSpeed, double toExec, bool track){
  midPoint = -midPoint;
    if (rtime > toExec){
      right_back_drive.moveVoltage(0); right_front_drive.moveVoltage(0);
      right_back_drive.setBrakeMode(AbstractMotor::brakeMode::coast);
      right_front_drive.setBrakeMode(AbstractMotor::brakeMode::coast);
      rSettled += 20;
      if (rSettled >= 500 || rtime > toExec){
        rCompleted = true;
        pros::lcd::set_text(4, std::to_string(rError-lError));
      }
    }
    else {

      if (abs(getPos().r - midPoint) < 3){
        rAtMid = true;
        pros::lcd::set_text(3, std::to_string(rError));
      }
      rError = - dtarget - getPos().r;
      cError = getPos().l - getPos().r;
      rIntegral += rError;
      cIntegral += cError;
      if (rError == 0) rIntegral = 0;
      if (cError == 0) cIntegral = 0;
      rDerivative = rError - prError;
      cDerivative = cError - pcError;
      prError = rError;
      pcError = cError;
      rVoltage = dkP*rError + dkD*rDerivative + dkI*rIntegral;
      //TUNE THESE TO MAKE
      //IT DRIVE STRAIGHT
      //I PRINT OUT THE ERROR ON THE LEFT AND RIGHT SIDE
      compensate = +0*cError + 0*cDerivative + 0*cIntegral;
      if (track) {
        rVoltage += compensate;
      }
      if (rVoltage > maxSpeed) rVoltage = maxSpeed;
      if (rVoltage < -maxSpeed) rVoltage = -maxSpeed;

      // if 50 - 30 > 10, voltage = 40
      // if -50 - -30 < -10 voltage = -40
      if (rVoltage - prVoltage > slewV) rVoltage = prVoltage + slewV;
      else if (rVoltage - prVoltage  < - slewV) rVoltage = prVoltage - slewV;
      right_back_drive.moveVelocity(rVoltage); right_front_drive.moveVelocity(rVoltage);
      rtime+=20;
      prVoltage = rVoltage;


    }
    pros::lcd::set_text(3, std::to_string(rError ));


}




void turnPID (double angle, double midAngle, double maxSpeed, double toExec){
  //radius = 6.25
  dkP = 25;
  dkD = 30;
  slewV = 500;
  double botRadius = 3.3225;
  double radians = angle*3.1415926/180;
  double midRadians = midAngle*3.1415926/180;
  double dist = radians*botRadius;
  double midDist = midRadians*botRadius;
  printf("%f dist: \n", dkD);
  setLeftParams(-dist, -midDist, maxSpeed, toExec);
  setRightParams(dist, midDist, maxSpeed, toExec, false);
}

void driveUpdate () {
  drivePIDRight(rightParam.target, rightParam.midPoint, rightParam.maxSpeed,  rightParam.maxTime, rightParam.track);

  drivePIDLeft(leftParam.target, leftParam.midPoint, leftParam.maxSpeed,  leftParam.maxTime);

  //drivePIDRight(10, rightParam.maxSpeed, rightParam.maxSlew, 10000);
}
//is called in auton to reset drive targets
void setLeftParams (double target, double midPoint, double maxSpeed,  double maxTime){
  dkP = 12; dkD = 15;
  leftParam.target = target; leftParam.midPoint = midPoint; leftParam.maxSpeed = maxSpeed; leftParam.maxTime = maxTime;
}
void setRightParams (double target, double midPoint, double maxSpeed, double maxTime, bool track){
  dkP = 12; dkD = 15;
  rightParam.target = target; rightParam.midPoint = midPoint; rightParam.maxSpeed = maxSpeed; rightParam.maxTime = maxTime; rightParam.track = track;
}

void setLeftParamsT (double target, double midPoint, double maxSpeed,  double maxTime){
  dkP = 25; dkD = 30;
  leftParam.target = target; leftParam.midPoint = midPoint; leftParam.maxSpeed = maxSpeed; leftParam.maxTime = maxTime;
}
void setRightParamsT (double target, double midPoint, double maxSpeed, double maxTime, bool track){
  dkP = 25; dkD = 30;
  rightParam.target = target; rightParam.midPoint = midPoint; rightParam.maxSpeed = maxSpeed; rightParam.maxTime = maxTime; rightParam.track = track;
}

//resets wheel encoders
//resets time
void reset () {
  //rStop = true;
  //lStop = true;
  dkP = 12;
  dkD = 15;
  slewV = 6;
  rtime = 0;
  ltime = 0;
  lCompleted = false; lAtMid = false;
  rCompleted = false; rAtMid = false;
  leftOdom.reset(); rightOdom.reset();
  //left_back_drive.tarePosition(); left_front_drive.tarePosition(); right_back_drive.tarePosition(); right_front_drive.tarePosition();
  lVoltage = 0; rVoltage = 0; compensate = 0; plVoltage = 0; prVoltage = 0;
  rSettled = 0; lSettled = 0;
  //NEW
  leftParam.target = 0; rightParam.target = 0;



}
//checks if drive finished
bool getCompleted() {
  if (lCompleted && rCompleted) return true;
  return false;
}
bool getMid() {
  if (lAtMid && rAtMid) return true;
  return false;
}
void drivePIDThread (void *params){
  while (true){
    if (safe < 14980)
    driveUpdate();
    pros::delay(20);
  }
}
void test (void){
  pros::lcd::set_text(2, std::to_string(leftOdom.get()));
  pros::lcd::set_text(1, "hi");
}
