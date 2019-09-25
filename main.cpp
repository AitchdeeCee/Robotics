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
vex::motor      backLeft(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::motor      frontRight(vex::PORT11, vex::gearSetting::ratio18_1, true);
vex::motor      frontLeft(vex::PORT20, vex::gearSetting::ratio18_1, false);
vex::controller con(vex::controllerType::primary);

// define your global instances of motors and other devices here
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
   
    while(true) {
        Y1 = (abs(con.Axis3.position())>threshold)?con.Axis3.position():0;
        X1 = (abs(con.Axis4.position())>threshold)?con.Axis4.position():0;
        X2 = (abs(con.Axis1.position())>threshold)?con.Axis1.position():0;
        frontRight.spin(fwd,Y1-X2-X1, velocityUnits::pct);
        backRight.spin(fwd, Y1-X2+X1, velocityUnits::pct);
        frontLeft.spin(fwd, Y1+X2+X1, velocityUnits::pct);
        backLeft.spin(fwd, Y1+X2-X1, velocityUnits::pct);
    }
}
