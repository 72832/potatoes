#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    leftLiftPotent, sensorPotentiometer)
#pragma config(Sensor, in2,    rightLiftPotent, sensorNone)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  puncherEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           puncher,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           liftLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           left1,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           left2,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           left3,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           right1,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           right2,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           right3,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           liftRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          flipper,       tmotorVex393_HBridge, openLoop)
#pragma config(DatalogSeries, 0, "leftEncodeDatalog", Sensors, Sensor, dgtl1, 50)
#pragma config(DatalogSeries, 1, "rightEncodeDatalog", Sensors, Sensor, dgtl3, 50)
#pragma config(DatalogSeries, 2, "rightLiftDatalog", Sensors, Sensor, in2, 50)
#pragma config(DatalogSeries, 3, "leftEncodeDatalog", Sensors, Sensor, in1, 50)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//bleebleebloop
//motor left2 = middle
//motor left1 & left3 = sides
//motor right2 = middle
//motor right1 & right 3 = sides

/*--
#pragma config(Motor,  port4,           ballIntake,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           flyWheel1,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           flyWheel2,     tmotorVex393HighSpeed_MC29, openLoop)
--*/

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "variables.c"
#include "Vex_Competition_Includes.c" //Main competition background code...do not modify!
#include "functions.c"



/////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton(){
// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
bStopTasksBetweenModes = true;

// All activities that occur before the competition starts
// Example: clearing encoders, setting servo positions, ...
clearAll(actOnSensors);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
// Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////



task autonomous() {

}

/////////////////////////////////////////////////////////////////////////////////////////
//
// User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////



task usercontrol() {
// User control code here, inside the loop

/////////////////////////////////////////////////////////////////////////////////////////
//
// Variable Declarations
//
/////////////////////////////////////////////////////////////////////////////////////////

while (true) {
// This is the main execution loop for the user control program. Each time through the loop
// your program should update motor + servo values based on feedback from the joysticks.

		//drive program
		drive();


	}
}
