//Made new header file because did not want to define functions and structures specific to Odometry Calculations

#ifndef _PROS_FLYWHEEL_H_
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
void singleShot(void);
void turnDrive(int i);
//auton stuff
bool indexerSettled();
void autonIndexPosition (int i, int speed);

extern void visionXAlignThread(void *params);

extern void flywheelPIDThreadAuton(void *params);
extern void flywheelPIDThreadOP(void *params);

extern void flywheelShootThread(void *params);

extern ADIEncoder sensor;


/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
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

#endif  // _PROS_FLYWHEEL_H_
