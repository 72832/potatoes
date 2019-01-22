#pragma config(Sensor, in1,    liftRight,      sensorPotentiometer)
#pragma config(Sensor, in2,    liftLeft,       sensorPotentiometer)
#pragma config(Sensor, in3,    flipPotent,     sensorPotentiometer)
#pragma config(Sensor, in4,    ballIntake,     sensorLineFollower)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           lift,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           intake,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           right3,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           right2,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           right1,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           left1,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           left2,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           left3,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           puncher,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          flipper,       tmotorVex393HighSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

// SmartMotorLibrary
#include "jpearman/SmartMotorLib.c"

//auton vars
//Left
float  pid_Kp = 0.7;
float  pid_Ki = 0.09;
float  pid_Kd = 0.5;

//Right
float  pd_Kp = 0.7;
float  pd_Ki = 0.09;
float  pd_Kd = 0.5;

/*
float  pid_Lift_Kp = 2;
float  pid_Lift_Ki = 0.04;
float  pid_Lift_Kd = 0.5;
*/

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void resetEncoders(){
	SensorValue[ leftEncoder ] = 0;
  SensorValue[ rightEncoder ] = 0;
}

//after ints
//sensor encoders int
int leftEncode(){
	return(SensorValue[leftEncoder]);
}

int rightEncode(){
	return(SensorValue[rightEncoder]);
}

/*
int liftLPotent(){
	return(SensorValue[liftLeft]);
}

int liftRPotent(){
	return(SensorValue[liftRight]);
}
*/

void delayFunc(int time){
	wait1Msec(time);
}

string mainBattery, backupBattery;

// User control drive functions
void leftFunc(int speed1){
	speed1*=1.1;
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

bool driveReverse=false;

void drive(){
	if(driveReverse==true){
		leftFunc(vexRT[Ch2]*-1);
		rightFunc(vexRT[Ch3]*-1);
	} else if(driveReverse==false){
		rightFunc(vexRT[Ch2]);
		leftFunc(vexRT[Ch3]);
	}
}

void puncherFunc(int power){
	motor[puncher]=power;
}

void intakeFunc(int power){
	motor[intake]=power;
}

void flipperFunc(int power){
	motor[flipper]=power;
}

//lcd clear
void clearLCD(){
	clearLCDLine(0);
	clearLCDLine(1);
}

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
	clearLCD();
	while(true){
		displayLCDPos(0,0);
		displayNextLCDString("> Enc: ");
		displayNextLCDNumber(rightEncode());
		displayLCDPos(1,0);
		displayNextLCDString("< Enc:  ");
		displayNextLCDNumber(leftEncode());
	}
}

task lcdPWM(){
	clearLCD();
	while(true){
		displayLCDPos(0,0);
		displayNextLCDString("Right PWM: ");
		displayNextLCDNumber(vexRT[Ch3]);
		displayLCDPos(1,0);
		displayNextLCDString("Left PWM: ");
		displayNextLCDNumber(vexRT[Ch2]);
	}
}

/*
//Wait for Press--------------------------------------------------
void waitForPress()
{
while(nLCDButtons == 0){}
wait1Msec(5);
}
//----------------------------------------------------------------
//Wait for Release------------------------------------------------
void waitForRelease()
{
while(nLCDButtons != 0){}
wait1Msec(5);
}
//----------------------------------------------------------------
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
void menuFunc(){
	clearLCD();
	displayLCDCenteredString(0,"------STOP------");
	displayLCDCenteredString(1,"----PROGRAM?----");
	waitForPress();
	if(nLCDButtons==centerButton){
		waitForRelease();
		stopTask(usercontrol);
		stopTask(autonomous);
		clearLCD();
		displayLCDCenteredString(0,"----PROGRAM-----");
		displayLCDCenteredString(1,"----STOPPED-----");
	}
	clearLCD();
	displayLCDCenteredString(0,"-----START------");
	displayLCDCenteredString(1,"----PROGRAM?----");
	waitForPress();
	if(nLCDButtons==centerButton){
		waitForRelease();
		startTask(usercontrol);
		clearLCD();
		displayLCDCenteredString(0,"----PROGRAM-----");
		displayLCDCenteredString(1,"----RUNNING-----");
	}
}
*/

//lcd driver control
task lcd(){
	clearLCD();

	lcdBattery();
	delayFunc(1500);
	clearLCD();
	if( nVexRCReceiveState & 0x02 )
	{
		// second joystick is connected
		displayLCDCenteredString(0,"--PARTNER CTRl--");
		displayLCDCenteredString(1,"----WORKING ----");
		delayFunc(1000);
		clearLCD();
	}else{
		// second joystick is connected
		displayLCDCenteredString(0,"--PARTNER CTRl--");
		displayLCDCenteredString(1,"--NOT WORKING---");
		delayFunc(1000);
		clearLCD();
	}

	while(true){
//		if(nLCDButtons!=0){
//			waitForRelease();
//			menuFunc();
//		}else{


			startTask(lcdEncode);
			delayFunc(1000);
			stopTask(lcdEncode);
			clearLCD();

			startTask(lcdPWM);
			delayFunc(1000);
			stopTask(lcdPWM);
			clearLCD();
//		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

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

#define PID_DRIVE_MAX       80
#define PID_DRIVE_MIN     (-80)

// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"

static int   pidRunning = 1;
static float pidRequestedValue;

static int   pdRunning = 1;
static float pdRequestedValue;

bool taskRunning=false;
// These could be constants but leaving


// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  pid control task                                                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task leftPIDController()
{
		taskRunning=true;
    float  pidSensorCurrentValue;
    float  pidError;
    float  pidLastError;
    float  pidIntegral;
    float  pidDerivative;
    float  pidDrive;

    float  pdSensorCurrentValue;
    float  pdError;
    float  pdLastError;
    float  pdIntegral;
    float  pdDerivative;
    float  pidDrive2;

    // If we are using an encoder then clear it
    if( SensorType[ LEFT_SENSOR_INDEX ] == sensorQuadEncoder )
        SensorValue[ LEFT_SENSOR_INDEX ] = 0;

    if( SensorType[ RIGHT_SENSOR_INDEX ] == sensorQuadEncoder )
        SensorValue[ RIGHT_SENSOR_INDEX ] = 0;

    // Init the variables - thanks Glenn :)
    pidLastError  = 0;
    pidIntegral   = 0;

    pdLastError  = 0;
    pdIntegral   = 0;

    while( true ){
    	if( pidRunning ){
        if(pidSensorCurrentValue==pidRequestedValue){
        	taskRunning = false;
        	stopTask(leftPIDController);
      	}

        // Is PID control active ?
        if( pdRunning )
            {
            // Read the sensor value and scale
            pdSensorCurrentValue = SensorValue[ RIGHT_SENSOR_INDEX ] * PID_SENSOR_SCALE;

                        // Read the sensor value and scale
            pidSensorCurrentValue = SensorValue[ LEFT_SENSOR_INDEX ] * PID_SENSOR_SCALE;


            // calculate error
            pidError = pidSensorCurrentValue - pidRequestedValue;

            // calculate error
            pdError = pdSensorCurrentValue - pdRequestedValue;

            // integral - if Ki is not 0
            if( pd_Ki != 0 )
                {
                // If we are inside controlable window then integrate the error
                if( abs(pdError) < PD_INTEGRAL_LIMIT )
                    pdIntegral = pdIntegral + pdError;
                else
                    pdIntegral = 0;
                }
            else
                pdIntegral = 0;

                        // integral - if Ki is not 0
            if( pid_Ki != 0 )
                {
                // If we are inside controlable window then integrate the error
                if( abs(pidError) < PID_INTEGRAL_LIMIT )
                    pidIntegral = pidIntegral + pidError;
                else
                    pidIntegral = 0;
                }
            else
                pidIntegral = 0;

						// calculate the derivative
            pidDerivative = pidError - pidLastError;
            pidLastError  = pidError;

            // calculate the derivative
            pdDerivative = pdError - pdLastError;
            pdLastError  = pdError;

            // calculate drive
            pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);

            pidDrive2 = (pd_Kp * pidError) + (pd_Ki * pidIntegral) + (pd_Kd * pidDerivative);

            // limit drive
            if( pidDrive > PID_DRIVE_MAX )
                pidDrive = PID_DRIVE_MAX;
            if( pidDrive < PID_DRIVE_MIN )
                pidDrive = PID_DRIVE_MIN;

            if( pidDrive2 > PID_DRIVE_MAX )
                pidDrive2 = PID_DRIVE_MAX;
            if( pidDrive2 < PID_DRIVE_MIN )
                pidDrive2 = PID_DRIVE_MIN;

            leftFunc(pidDrive);
						rightFunc(pidDrive2);
					}
      	}else{
            // clear all
            pidError      = 0;
            pidLastError  = 0;
            pidIntegral   = 0;
            pidDerivative = 0;

            // clear all
            pdError      = 0;
            pdLastError  = 0;
            pdIntegral   = 0;
            pdDerivative = 0;

            leftFunc(0);
            rightFunc(0);
            }

        // Run at 50Hz
        wait1Msec( 25 );
        }
}

/*-----------------------------------------------------------------------------*/
/*
*/
/*  main task
/*
*/
/*-----------------------------------------------------------------------------*/

void drivePID(int clicks, int clicks2){

	// send the motor off somewhere
  pidRequestedValue= clicks*-1;
  pdRequestedValue=  clicks2*-1;

	// start the PID task
  startTask( leftPIDController );
  taskRunning=true;
	//	startTask( rightPIDController );

  // use joystick to modify the requested position
  while(taskRunning){
  	// maximum change for pidRequestedValue will be 127/4*20, around 640 counts per second
  	// free spinning motor is 100rmp so 1.67 rotations per second
		// 1.67 * 360 counts is 600
  	wait1Msec(20);
  }
	stopTask(leftPIDController);
}

////////////////////////////////////////////////////////////////////////////////

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

task driveOn(){
	while(true){
		leftFunc(-127);
		rightFunc(-127);
	}
}

task driveOff(){
	while(true){
		leftFunc(0);
		rightFunc(0);
	}
}


task intakeUp(){
	while(true){
		intakeFunc(127);
	}
}

task intakeOff(){
	while(true){
		intakeFunc(0);
	}
}

task intakeDown(){
	while(true){
		intakeFunc(-127);
	}
}

/*----------------------------------------------------------------------------------------------------*\
|*                                   - Point Turns with Encoders -                                    *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to turn left, and then right, using feedback from the encoders   *|
|*  to determine how much.  There is a 2 second pause at the beginning of the program.                *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" model, but may not be needed for all robot configurations.                      *|
|*    2)  Whichever encoder is being used for feedback should be cleared just before it starts        *|
|*        counting by using the "SensorValue(encoder) = 0;".  This helps ensure consistancy.          *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor   - Port 2    rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor   - Port 3    leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital - Port 1,2  rightEncoder        VEX Shaft Encoder     Right side                        *|
|*    Digital - Port 3,4  leftEncoder         VEX Shaft Encoder     Left side                         *|
\*----------------------------------------------------------------------------------------------------*/


void turnLeft(int leftVal){
	resetEncoders();
  while(SensorValue(rightEncoder) < leftVal)//rightEncoder has counted less than 1800 counts
	{
		//Turn Left
		rightFunc(127);  //Motor on port2 is run at full (127) power forward
		leftFunc(-127);       //Motor on port3 is run at full (-127) power reverse
	}
}

void turnRight(int rightVal){
	resetEncoders();
  while(SensorValue(leftEncoder) < rightVal)//While leftEncoder has counted less than 1800 counts
	{
		//Turn Right
    rightFunc(-127);// port2 is run at full (127) power forward
		leftFunc(127);      //Motor on port3 is run at full (-127) power reverse	}
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//auton functions
//forward slightly

//auton
void auton(){
	//1200 from place to flag or to alliance park
	//2000 from place to center

	startTask(puncherOn);
	delayFunc(800);
	stopTask(puncherOn);
	startTask(puncherOff);
	stopTask(puncherOff);

	drivePID(1150,1150);
	drivePID(-2000,-2000);
  // If we are using an encoder then clear it
	resetEncoders();

	turnRight(205);

	startTask(driveOff);
	stopTask(driveOff);

	delayFunc(500);

	startTask(driveOn);
	delayFunc(750);
	stopTask(driveOn);
	startTask(driveOff);
	stopTask(driveOff);

	drivePID(1200,1200);
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

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

void pre_auton()
{
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

	// Drive motors
	SmartMotorLinkMotors(left1,left2);
	SmartMotorLinkMotors(left1,left3);
	SmartMotorLinkMotors(right1,right2);
	SmartMotorLinkMotors(right1,right3);
	// Current monitor
	SmartMotorCurrentMonitorEnable();
	// Smart motor start
	SmartMotorRun();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	//(find in leftPID.c)
	auton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// User control code here, inside the loop

// This is the main execution loop for the user control program.
// Each time through the loop your program should update motor + servo
// values based on feedback from the joysticks.

// ........................................................................
// Insert user code here. This is where you use the joystick values to
// update your motors, etc.
// ........................................................................

task usercontrol(){
	bLCDBacklight = true;									// Turn on LCD Backlight

	startTask(lcd);   //(find in leftPID.c)

	resetEncoders();  //(find in functions.c)

	// Drive program
	while(true){
		// drive program (find in functions.c)
		drive();

/*		if( nVexRCReceiveState & 0x02 )
		{
			// second joystick is connected
			// Intake program
			if (vexRT[Btn6UXmtr2]==1){
				motor[intake]=127;
				}else if (vexRT[Btn6DXmtr2]==1){
				motor[intake]=-127;
				} else{
				motor[intake]=0;
			}
			if(vexRT[Btn7UXmtr2]==1){
				auton();
			}
			// Puncher program
			if (vexRT[Btn5UXmtr2]==1){
				motor[puncher1]=127;
				motor[puncher2]=127;
				} else{
				motor[puncher1]=0;
				motor[puncher2]=0;
			}
		}else{
			// Intake program
			if (vexRT[Btn5UXmtr2]==1){
				motor[puncher1]=127;
				motor[puncher2]=127;
				}else{
				motor[puncher1]=0;
				motor[puncher2]=0;
			}
*/

			bool intakeToggle = false;

			//lift program (find in functions.c)
			if(vexRT[Btn5UXmtr2]==1){
				if(intakeToggle==false){
					waitUntil(vexRT[Btn5DXmtr2]==0);
					intakeFunc(127);
					intakeToggle=true;
				} else if(intakeToggle==true){
					waitUntil(vexRT[Btn5DXmtr2]==0);
					intakeFunc(0);
					intakeToggle=false;
				}
			}else if (vexRT[Btn5DXmtr2]==1){
				if(intakeToggle==true){
					waitUntil(vexRT[Btn5UXmtr2]==0);
					intakeFunc(0);
					intakeToggle=false;
					delayFunc(500);
					intakeFunc(127);
					intakeToggle=true;
				}else if(intakeToggle==false){
					waitUntil(vexRT[Btn5UXmtr2]==0);
					intakeToggle=true;
					intakeFunc(-127);
				}
			}else{
				intakeFunc(0);
			}
/*
			//flipper
			if(vexRT[Btn8R]==1){
				flipperFunc(127);
			}else if (vexRT[Btn8L]==1){
				flipperFunc(-127);
			}else{
				flipperFunc(0);
			}
*/
			// Puncher program (find in functions.c)
			if (vexRT[Btn6UXmtr2]==1){
					startTask(puncherOn);
			}else{
				puncherFunc(0);
			}

			if (vexRT[Btn6U]==1){
					startTask(puncherOn);
			}else{
				puncherFunc(0);
			}
/*
			if(vexRT[Btn5U]==1){
				liftFunc(127);
			}else if(vexRT[Btn5D]==1){
				liftFunc(-127);
			} else {
				liftFunc(0);
			}
*/

			//reverse drive so that you can easily flip caps (find in functions.c)
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

			//reverse drive so that you can easily flip caps (find in functions.c)
			if(vexRT[Btn8DXmtr2]==1){
				if(driveReverse==false){
					waitUntil(vexRT[Btn8D]==0);
					driveReverse=true;
					delayFunc(500);
				}
				else if(driveReverse==true){
					waitUntil(vexRT[Btn8DXmtr2]==0);
					driveReverse=false;
					delayFunc(500);
				}
			}

			//if button pressed run auton (auton is in leftPID.c)
			if(vexRT[Btn7U]==1){
				auton();
			}

			//if button pressed reset Encoders (to find this function look at functions.c)
			if(vexRT[Btn7D]==1){
				resetEncoders();
			}

		delayFunc(20);

	}
}