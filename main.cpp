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
vex::brain      Brain;
vex::motor      backRight(vex::PORT1, vex::gearSetting::ratio18_1, true); 
vex::motor      backLeft(vex::PORT2, vex::gearSetting::ratio18_1, false);
vex::motor      frontRight(vex::PORT3, vex::gearSetting::ratio18_1, true);
vex::motor      frontLeft(vex::PORT4, vex::gearSetting::ratio18_1, false);
vex::motor      leftArm(vex::PORT5, vex::gearSetting::ratio18_1, true);
vex::motor      rightArm(vex::PORT6, vex::gearSetting::ratio18_1, false);

vex::controller con(vex::controllerType::primary);

// define your global instances of motors and other devices here
<<<<<<< HEAD

void run(double a) {
    frontRight.startRotateFor(a, rev);
    frontLeft.startRotateFor(a,rev);
    backLeft.startRotateFor(a,rev);
    backRight.rotateFor(a,rev);
    vex::task::sleep(1000);
}
void turn(double a){
    frontLeft.startRotateFor(a*0.6, rev);
    frontRight.startRotateFor(a*-0.6, rev);
    backLeft.startRotateFor(a*0.6, rev);
    backRight.rotateFor(-a*0.6, rev);
    vex::task::sleep(1000);
}
// If you want to turn right, type in 1
// If you want to turn left, type in -1
// if you want to turn rightward to the opposite side, type in 2
// If you want to turn leftward to the opposite side, type in -2
void controllRun(){
  int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
=======
void run(double a){
    backRight.startRotateFor(a, rev);
    backLeft.startRotateFor(a, rev);
    frontRight.startRotateFor(a, rev);
    frontLeft.rotateFor(a, rev);
    vex::task::sleep(1000);
}
void turn(double a){
    backRight.startRotateFor(a*1.3, rev);
    backLeft.startRotateFor(a*-1.3, rev);
    frontRight.startRotateFor(a*1.3, rev);
    frontLeft.rotateFor(a*-1.3, rev);
    vex::sleep(1000);
}
int main() {
    int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
   
>>>>>>> 69e60ab2e1442e562dd4dbb388608f82bdd9c5d2
    while(true) {
        Y1 = (abs(con.Axis3.position())>threshold)?con.Axis3.position():0;
        X1 = (abs(con.Axis4.position())>threshold)?con.Axis4.position():0;
        X2 = (abs(con.Axis1.position())>threshold)?con.Axis1.position():0;
        frontRight.spin(fwd, Y1-X2+X1, velocityUnits::pct);
        backRight.spin(fwd, Y1-X2-X1, velocityUnits::pct);
        frontLeft.spin(fwd, Y1+X2-X1, velocityUnits::pct);
        backLeft.spin(fwd, Y1+X2+X1, velocityUnits::pct);
    }
}
void controllArms(){
    while(true){
      if(con.ButtonUp.pressing()){
        leftArm.spin(fwd, 50, pct);
        rightArm.spin(fwd, 50, pct);
      }else if(con.ButtonDown.pressing()){
        leftArm.spin(directionType::rev, 50, pct);
        rightArm.spin(directionType::rev, 50, pct);
      }else{
        leftArm.stop(hold);
        rightArm.stop(hold);
      }
    }
}

int main() {
    run(2);
    turn(2);
    run(2);
    Brain.Screen.print("I'M GAY FOR HUYYYYYYYY");
    controllRun();
    controllArms();
}
