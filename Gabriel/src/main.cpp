
#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::motor      backRight(vex::PORT1, vex::gearSetting::ratio18_1, true); 
vex::motor      backLeft(vex::PORT2, vex::gearSetting::ratio18_1, false);
vex::motor      frontRight(vex::PORT3, vex::gearSetting::ratio18_1, true);
vex::motor      frontLeft(vex::PORT4, vex::gearSetting::ratio18_1, false);
vex::motor      stack(vex::PORT5, vex::gearSetting::ratio18_1, true);
vex::motor      leftIn(vex::PORT10, vex::gearSetting::ratio18_1, true);
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
    vex::task::sleep(1000);
}
void intake(double a){
    leftIn.startRotateFor(directionType::rev,a,rev,50,velocityUnits::pct);
    rightIn.rotateFor(directionType::rev,a,rev,50,velocityUnits::pct);
    vex::task::sleep(1000);
}
void stacker(double a){
    stack.startRotateFor(directionType::rev,a,rev,50,velocityUnits::pct);
    vex::task::sleep(1000);
}
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void autonomous(void) {
    run(-2);
    run(3);
}

void usercontrol(void) {
  int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
    while(true) {
        Y1 = (abs(con.Axis3.position())>threshold)?con.Axis3.position():0;
        X1 = (abs(con.Axis4.position())>threshold)?con.Axis4.position():0;
        X2 = (abs(con.Axis1.position())>threshold)?con.Axis1.position():0;
        frontRight.spin(fwd, (Y1-X2-X1), velocityUnits::pct);
        backRight.spin(fwd, (Y1-X2+X1), velocityUnits::pct);
        frontLeft.spin(fwd, (Y1+X2+X1), velocityUnits::pct);
        backLeft.spin(fwd, (Y1+X2-X1), velocityUnits::pct);
        if(con.ButtonL1.pressing()){
          stack.spin(directionType::rev, 20, pct);
        }else if(con.ButtonL2.pressing()){
          stack.spin(fwd, 20, pct);
        }else{
          stack.stop(hold);  
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
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  
  // Run the pre-autonomous function.
  pre_auton();

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
