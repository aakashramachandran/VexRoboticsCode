//Made new header file because did not want to define functions and structures specific to Odometry Calculations

#ifndef _PROS_ODOMETRY_H_
#define _PROS__H_

#include "api.h"

/**
 * You should add more #includes here
 */
 #include "api.h"

 /**
  * You should add more #includes here
  */
 #include "okapi/api.hpp"
 //#include "pros/api_legacy.h"
 #include "pros/apix.h"

 using namespace okapi;

//Function Headers
struct pidParams {
  double target;
  double midPoint;
  double maxSpeed;
  double maxTime;
  bool track;
};
struct driveOutput {
  double r;
  double l;
  double rV;
  double lV;
};
struct driveInput {
 double power;
 double turn;
};

driveInput slew (double p1, double p, double t1, double t, double slewRate);
void driver (double pow1, double turn1);
driveInput getJoystick ();
driveOutput getPos();
void drivePIDLeft(double target, double midPoint, double maxSpeed, double toExec);
//track determines whether or not to perform DRIVE STRAIGHT CORRECTION
void drivePIDRight(double target, double midPoint, double maxSpeed, double toExec, bool track);

void turnPID(double angle, double midAngle, double maxSpeed, double toExec);
/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
 extern void drivePIDThread(void *params);
 extern void safetyThread (void *params);

 //these methods set the parameters for the PIDs
 extern void setLeftParams (double target, double midPoint, double maxSpeed,  double maxTime);
 extern void setRightParams (double target, double midPoint, double maxSpeed,  double maxTime, bool track);

 extern void setLeftParamsT (double target, double midPoint, double maxSpeed,  double maxTime);
 extern void setRightParamsT (double target, double midPoint, double maxSpeed,  double maxTime, bool track);

 //reset drive
 extern void reset();
 //tell if drive done
 extern bool getCompleted();
 extern bool getMid();

 extern ADIEncoder leftOdom;
 extern ADIEncoder rightOdom;

 extern void test (void);
#ifdef __cplusplus
extern "C" {
#endif
//functions here
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

#endif  // _PROS_ODOMETRY_H_
