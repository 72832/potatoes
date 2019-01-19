#pragma config(Sensor, in3,    autonPotent,    sensorPotentiometer)
#pragma config(Sensor, in4,    ballIntake,     sensorLineFollower)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           intake1,       tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           left1,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           left2,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           left3,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           right3,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           right2,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           right1,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           noUse,         tmotorNone, openLoop)
#pragma config(Motor,  port9,           puncher,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          intake2,       tmotorVex393TurboSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

////////////////////////////////////////////////////////////////////////////////////////

// Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

// SmartMotorLibrary
#include "jpearman/SmartMotorLib.c"


#include "Vex_Competition_Includes.c"  // Main competition background code...do not modify!
#pragma systemFile

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

// Main competition background code...do not modify!

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

//PID
//Drive Top Level
// PID using optical shaft encoder
//
// Shaft encoder has 360 pulses per revolution
#define PID_INTEGRAL_LIMIT  50
#define PD_INTEGRAL_LIMIT  50

#define LEFT_SENSOR_INDEX    leftEncoder
#define RIGHT_SENSOR_INDEX   rightEncoder
#define PID_SENSOR_SCALE     -1

#define LEFT_MOTOR_INDEX    left1
#define RIGHT_MOTOR_INDEX   right1
#define PID_MOTOR_SCALE     -1

#define PID_DRIVE_MAX       60
#define PID_DRIVE_MIN     (-60)

// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"

//auton vars
//Left
float  pid_Kp = 0.7;
float  pid_Ki = 0.09;
float  pid_Kd = 0.5;

static int   pidRunning = 1;
static float pidRequestedValue;

bool taskRunning=false;

bool driveReverse=false;

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////

void delayFunc(int time){
	wait1Msec(time);
}

void puncherFunc(int power){
	motor[puncher]=power;
}

void intake1Func(int power1){
	motor[intake1]=power1;
}

void intake2Func(int power2){
	motor[intake2]=power2;
}

void intakeFunc(int power1, int power2){
	intake1Func(power1);
	intake2Func(power2);
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  pid control task                                                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

void leftFunc(int speed1){
	speed1*=1.0;
	SetMotor(left1,speed1);
	SetMotor(left2,speed1);
	SetMotor(left3,speed1);
}

void rightFunc(int speed2){
	speed2*=1.0;
	SetMotor(right1,speed2);
	SetMotor(right2,speed2);
	SetMotor(right3,speed2);
}

void drive(){
	if(driveReverse==true){
		leftFunc(vexRT[Ch2]);
		rightFunc(vexRT[Ch3]*-1);
	}else if(driveReverse==false){
		rightFunc(vexRT[Ch2]);
		leftFunc(vexRT[Ch3]*-1);
	}
}

void resetEncoders(){
	SensorValue[ leftEncoder ] = 0;
  SensorValue[ rightEncoder ] = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton(){
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
	// Enable smart motor library
	SmartMotorsInit();

	// Define motors plugged into power expander
	// SmartMotorsAddPowerExtender( motorA, motorB, motorC, motorD );

	// Link motors
	SmartMotorLinkMotors(left1,left2);
	SmartMotorLinkMotors(right1,right2);
	// Current monitor
	SmartMotorCurrentMonitorEnable();
	// Smart motor start
	SmartMotorRun();

	resetEncoders();
}

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////

#include "auton.c"

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////

task puncherOn(){
	while(true){
		puncherFunc(127);
	}
}

task puncherOff(){
	while(true){
		puncherFunc(0);
	}
}

task intakeOn(){
	while(true){
		intakeFunc(127,127);
	}
}

task intakeOff(){
	while(true){
		intakeFunc(0,0);
	}
}

/*--

task upIntakeOn(){
	while(true){
		intake2Func(-127);
	}
}

task upIntakeOff(){
	while(true){
		intake2Func(0);
	}
}

--*/

void punch(){
	//puncher on
	startTask(puncherOn);
	delayFunc(2000);
	stopTask(puncherOn);
	startTask(puncherOff);
	stopTask(puncherOff);
}

//auton
void auton(){
	//1200 from place to flag or to alliance park
	//2000 from place to center
	punch();

	if(SensorValue[autonPotent]>=3000){
		turnLeft();
	}else if(SensorValue[autonPotent]<=1000){
		turnRight();
	}

	//intake on
	startTask(intakeOn);

	//drive forward to toggle small flag
	drivePID(1000);

	drivePID(-1000);

	//intake stop
	stopTask(intakeOn);
	startTask(intakeOff);
	stopTask(intakeOff);

	if(SensorValue[autonPotent]>=3000){
		turnRight();
	}else if(SensorValue[autonPotent]<=1000){
		turnLeft();
	}

	punch();

/*--

	//drive backwards
	drivePID(-1150,-1150);

	//drive turn 90
	drivePID(600,-600);

	//intake on
	startTask(intakeOn);

	//forward 2.5 squares
	drivePID(1500,1500);

	//wait until ballIntake sensor ==correct value
	waitUntil(SensorValue[ballIntake]==SensorValue[ballIntake]);

	//delete this when ballIntake sensor works
	delayFunc(600);

	//intake off
	stopTask(intakeOn);
	startTask(intakeOff);
	stopTask(intakeOff);

	//top intake on backwards
	startTask(upIntakeOn);
	delayFunc(500);

	//top intake stop
	stopTask(upIntakeOn);
	startTask(upIntakeOff);
	stopTask(upIntakeOff);

	//drive backwards one square
	drivePID(-600,-600);

	//turn a little bit
	drivePID(200,-200);

	//puncher on
	startTask(puncherOn);
	delayFunc(600);

	//puncher off
	stopTask(puncherOn);
	startTask(puncherOff);
	stopTask(puncherOff);

	//unturn a little bit
	drivePID(-200,200);

	//drive backwards to platform
	drivePID(-600,-600);

--*/

}

//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////

task autonomous(){
	auton();
}

//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////

void clearLCD(){
	clearLCDLine(0);
	clearLCDLine(1);
}

string mainBattery, backupBattery;

bool lcdEncodeBool=false;

//void lcd display voltage
void lcdBattery(){
		clearLCD();

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Display the Backup battery voltage
		displayLCDString(1, 0, "Backup: ");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		displayNextLCDString(backupBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
}

task lcdEncode(){
	while(true){
		clearLCD();
		displayLCDPos(0,0);
		displayNextLCDString("> Enc: ");
		displayNextLCDNumber(SensorValue[rightEncoder]);
		displayLCDPos(1,0);
		displayNextLCDString("< Enc:  ");
		displayNextLCDNumber(SensorValue[leftEncoder]);
		delayFunc(100);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////

task usercontrol(){

	//display battery voltage
	lcdBattery();

	bLCDBacklight = true;									// Turn on LCD Backlight

	while(true){
	// drive program
	drive();

	// Puncher program
	if (vexRT[Btn6U]==1){
		puncherFunc(127);
	}else{
		puncherFunc(0);
	}

	if(vexRT[Btn8U]==1){
		auton();
	}

	if (vexRT[Btn7D]){
		lcdBattery();
	}

	if(vexRT[Btn7U]==1){
		if(lcdEncodeBool==1){
			stopTask(lcdEncode);
			lcdEncodeBool=false;
			waitUntil(vexRT[Btn7D]==0);
		}else if(lcdEncodeBool==0){
			startTask(lcdEncode);
			lcdEncodeBool=true;
			waitUntil(vexRT[Btn7D]==0);
		}
	}

	//reverse drive so that you can easily flip caps (find in functions)
	if(vexRT[Btn8D]==1){
		if(driveReverse==false){
			waitUntil(vexRT[Btn8D]==0);
			driveReverse=true;
			delayFunc(500);
		}else if(driveReverse==true){
			waitUntil(vexRT[Btn8D]==0);
			driveReverse=false;
			delayFunc(500);
		}
	}

	// Intake program
	if (vexRT[Btn5U]==1){
		 intake1Func(127);
		 intake2Func(127);
		}else if (vexRT[Btn6D]==1){
			intake1Func(-127);
		}else if(vexRT[Btn5D]==1){
			intake2Func(-127);
		}else{
			intake1Func(0);
			intake2Func(0);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
