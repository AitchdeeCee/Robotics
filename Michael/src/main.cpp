/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\cheda                                            */
/*    Created:      Sun Sep 22 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::motor      backRight(vex::PORT1, vex::gearSetting::ratio18_1, true); 
vex::motor      backLeft(vex::PORT2, vex::gearSetting::ratio18_1, false);
vex::motor      frontRight(vex::PORT3, vex::gearSetting::ratio18_1, true);
vex::motor      frontLeft(vex::PORT4, vex::gearSetting::ratio18_1, false);
vex::motor      leftArm(vex::PORT5, vex::gearSetting::ratio18_1, true);
vex::motor      rightArm(vex::PORT6, vex::gearSetting::ratio18_1, false);
vex::motor      leftIn(vex::PORT20, vex::gearSetting::ratio18_1, true);
vex::motor      rightIn(vex::PORT9, vex::gearSetting::ratio18_1, false);

vex::controller con(vex::controllerType::primary);

// define your global instances of motors and other devices here
void run(double a) {
    frontLeft.startRotateFor(fwd, a, rev, 50, velocityUnits::pct);
    frontRight.startRotateFor(fwd, a, rev, 50, velocityUnits::pct);
    frontLeft.startRotateFor(fwd, a, rev, 50, velocityUnits::pct);
    backLeft.startRotateFor(fwd, a, rev, 50, velocityUnits::pct);
    backRight.rotateFor(fwd, a, rev, 50, velocityUnits::pct);
    vex::task::sleep(1000);
}
void turn(double a){
    frontLeft.startRotateFor(fwd,a*1.5, rev,50,velocityUnits::pct);
    frontRight.startRotateFor(fwd,a*-1.5, rev, 50, velocityUnits::pct);
    backLeft.startRotateFor(fwd, a*1.5, rev, 50, velocityUnits::pct);
    backRight.rotateFor(fwd, -a*1.5, rev, 50, velocityUnits::pct);
    vex::task::sleep(1000);
}
void horizon(double a){
    frontLeft.startRotateFor(fwd,a, rev,50,velocityUnits::pct);
    frontRight.startRotateFor(fwd,-a, rev, 50, velocityUnits::pct);
    backLeft.startRotateFor(fwd,-a, rev, 50, velocityUnits::pct);
    backRight.rotateFor(fwd,a, rev, 50, velocityUnits::pct); 
}
void intake(double a){
    leftIn.startRotateFor(directionType::rev,a,rev,50,velocityUnits::pct);
    rightIn.rotateFor(directionType::rev,a,rev,50,velocityUnits::pct);
    vex::task::sleep(1000);
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void autonomous(void) {
  run(2);
  run(-2);
}


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
        Y1 = (abs(con.Axis3.position())>threshold)?con.Axis3.position():0;
        X1 = (abs(con.Axis4.position())>threshold)?con.Axis4.position():0;
        X2 = (abs(con.Axis1.position())>threshold)?con.Axis1.position():0;
        frontRight.spin(fwd, (Y1-X2+X1), velocityUnits::pct);
        backRight.spin(fwd, (Y1-X2-X1), velocityUnits::pct);
        frontLeft.spin(fwd, (Y1+X2-X1), velocityUnits::pct);
        backLeft.spin(fwd, (Y1+X2+X1), velocityUnits::pct);
        if(con.ButtonL2.pressing()){
          leftArm.spin(directionType::rev, 50, pct);
          rightArm.spin(directionType::rev, 50, pct);
        }else if(con.ButtonL1.pressing()){
          leftArm.spin(fwd, 50, pct);
          rightArm.spin(fwd, 50, pct);
        }else{
          leftArm.stop(hold);
          rightArm.stop(hold);  
        }
        if(con.ButtonR1.pressing()){
          leftIn.spin(directionType::rev, 75, pct);
          rightIn.spin(directionType::rev, 75, pct);
        }else if(con.ButtonR2.pressing()){
          leftIn.spin(directionType::fwd, 75, pct);
          rightIn.spin(directionType::fwd, 75, pct);
        }else{
          leftIn.stop(hold);
          rightIn.stop(hold);
        }
    }
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
