//Made new header file because did not want to define functions and structures specific to Odometry Calculations

#ifndef _PROS_ROLLERS_H_
#define _PROS__H_





//Function Headers


void toggleRollers(void);


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

#endif  // _PROS_ROLLERS_H_
