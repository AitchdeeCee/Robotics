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
vex::motor      leftIn(vex::PORT8, vex::gearSetting::ratio18_1, true);
vex::motor      rightIn(vex::PORT9, vex::gearSetting::ratio18_1, false);

vex::controller con(vex::controllerType::primary);

// define your global instances of motors and other devices here
int Timepress = 0;
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
int main() {
    int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
    leftArm.setMaxTorque(45, pct);
    rightArm.setMaxTorque(45,pct);
    while(true) {
        Y1 = (abs(con.Axis3.position())>threshold)?con.Axis3.position():0;
        X1 = (abs(con.Axis4.position())>threshold)?con.Axis4.position():0;
        X2 = (abs(con.Axis1.position())>threshold)?con.Axis1.position():0;
        frontRight.spin(fwd, (Y1-X2-X1)/2, velocityUnits::pct);
        backRight.spin(fwd, (Y1-X2+X1)/2, velocityUnits::pct);
        frontLeft.spin(fwd, (Y1+X2+X1)/2, velocityUnits::pct);
        backLeft.spin(fwd, (Y1+X2-X1)/2, velocityUnits::pct);
        if(con.ButtonL1.pressing()){
          leftArm.spin(directionType::rev, 25, pct);
          rightArm.spin(directionType::rev, 25, pct);
        }else if(con.ButtonL2.pressing()){
          leftArm.spin(fwd, 25, pct);
          rightArm.spin(fwd, 25, pct);
        }else{
          leftArm.stop(hold);
          rightArm.stop(hold);  
        }
        if(con.ButtonR1.pressing()){
          leftIn.spin(directionType::rev, 50, pct);
          rightIn.spin(directionType::rev, 50, pct);
        }else if(con.ButtonR2.pressing()){
          leftIn.spin(directionType::fwd, 50, pct);
          rightIn.spin(directionType::fwd, 50, pct);
        }else{
          leftIn.stop(hold);
          rightIn.stop(hold);
        }
    }
}
