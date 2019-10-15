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
int Timepress = 0;
bool buttonPressedLastLoop = false;
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
void controlArm(int a){
  vex::controller::button up = (a==0)?(con.ButtonL1):(con.ButtonUp);
  vex::controller::button down = (a==0)?(con.ButtonL2):(con.ButtonDown);
  if(up.pressing()){
    leftArm.spin(fwd, 10, pct);
    rightArm.spin(fwd, 10, pct);
  }else if(down.pressing()){
    leftArm.spin(directionType::rev, 10, pct);
    rightArm.spin(directionType::rev, 10, pct);
  }else{
    leftArm.stop(hold);
    rightArm.stop(hold);
  }
}
int main() {
    int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
    while(true) {
        Y1 = (abs(con.Axis3.position())>threshold)?con.Axis3.position():0;
        X1 = (abs(con.Axis4.position())>threshold)?con.Axis4.position():0;
        X2 = (abs(con.Axis1.position())>threshold)?con.Axis1.position():0;
        frontRight.spin(fwd, (Y1-X2-X1), velocityUnits::pct);
        backRight.spin(fwd, (Y1-X2+X1), velocityUnits::pct);
        frontLeft.spin(fwd, (Y1+X2+X1), velocityUnits::pct);
        backLeft.spin(fwd, (Y1+X2-X1), velocityUnits::pct);
        if (con.ButtonX.pressing() && !buttonPressedLastLoop) {
          buttonPressedLastLoop = true;
          Timepress++;
        } else if (!con.ButtonX.pressing() && buttonPressedLastLoop) {
          buttonPressedLastLoop = false;
          Timepress=0;
        }
        con.Screen.print(Timepress);
        controlArm(Timepress%2);
    }
}
