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


int main() {
    int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
   
    while(true) {

        if(abs(con.Axis3.position())>threshold)
        Y1 = con.Axis3.position();
        else
        Y1 = 0;
        if(abs(con.Axis4.position())>threshold)
        X1 = con.Axis4.position();
        else
        X1 = 0;
        if(abs(con.Axis1.position())>threshold)
        X2 = con.Axis1.position();
        else
        X2 = 0;

        frontRight.spin(fwd,Y1-X2-X1, velocityUnits::pct);
        backRight.spin(fwd, Y1-X2+X1, velocityUnits::pct);
        frontLeft.spin(fwd, Y1+X2+X1, velocityUnits::pct);
        backLeft.spin(fwd, Y1+X2-X1, velocityUnits::pct);

    }
}
