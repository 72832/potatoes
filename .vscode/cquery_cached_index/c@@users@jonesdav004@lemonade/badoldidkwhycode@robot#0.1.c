#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(Sensor, in1,    leftLiftPotent, sensorNone)
#pragma config(Sensor, in2,    rightLiftPotent, sensorPotentiometer)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  puncherEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  intakeEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           left1,         tmotorVex393HighSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           left2,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           left3,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           puncher1,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           intake,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           puncher2,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           right1,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           right2,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          right3,        tmotorVex393HighSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//bleebleebloop
//motor left2 = middle
//motor left1 & left3 = sides
//motor right2 = middle
//motor right1 & right 3 = sides

/*--
#prgma config(Motor,  port4,           ballIntake,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           flyWheel1,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           flyWheel2,     tmotorVex393HighSpeed_MC29, openLoop)
--*/
#include "jpearman/SmartMotorLib.c"

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c" //Main competition background code...do not modify!
#pragma systemFile
#include "variables.c"
#include "functions.c"
#include "lcdCodeChooserEx.c"


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
	bStopTasksBetweenModes = false;
	bLCDBacklight = true;									// Turn on LCD Backlight


	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
	//Smart Motor Library-------For more info go to https://renegaderobotics.org/using-jpearmans-smart-motor-library/
	//Enable smart motor library
	SmartMotorsInit();

	//Enable power expander
	//SmartMotorsAddPowerExtender(motorA,motorB,motorC,motorD);

	//Current or PTC Monitor------------------ I chose Current because it estimates motor speed and current
	SmartMotorCurrentMonitorEnable();

	//Smart motor start
	SmartMotorRun();

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
	lcdAuton();
}

/////////////////////////////////////////////////////////////////////////////////////////
//
// User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////


//hi
task usercontrol() {
	// User control code here, inside the loop

	/////////////////////////////////////////////////////////////////////////////////////////
	//
	// Variable Declarations
	//
	/////////////////////////////////////////////////////////////////////////////////////////


	startTask(lcd);

	while(true){
		// This is the main execution loop for the user control program. Each time through the loop
		// your program should update motor + servo values based on feedback from the joysticks.
		//functions
		drive();
		intaking();
		puncher();

		//wait so that there is a slight delay for the cpu to catch up
		wait1Msec(20);
	}
}
