#pragma config(Sensor, dgtl5,  quad,           sensorQuadEncoder)
#pragma config(Motor,  port3,           m,             tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(DatalogSeries, 0, "", Sensors, Sensor, dgtl5, 1000)
#pragma config(DatalogSeries, 1, "", Timers, time1, T1, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void clearLCD(){
	clearLCDLine(0);
	clearLCDLine(1);
}

void resetEncoders(){
	SensorValue[ quad ] = 0;
}

string mainBattery;

string battery0;

string battery10;

//void lcd display voltage
void lcd(){
		clearLCD();

		//Display the Backup battery voltage
		displayLCDString(1, 0, "Total Dist: ");
		displayNextLCDNumber(SensorValue[quad]);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
}

bool timerBool=true;

float zero=0.0;

float one=0.0;

float two=0.0;

float three=0.0;

float four=0.0;

float five=0.0;

float six=0.0;

float seven=0.0;

float eight=0.0;

float nine=0.0;

float ten=0.0;

task main(){
	battery0=mainBattery;
	resetEncoders();
	while(timerBool){
		motor[m]=127;
		lcd();
		while(timerBool){
			zero=SensorValue[quad];
			wait1Msec(1000);
			one=SensorValue[quad];
			wait1Msec(1000);
			two=SensorValue[quad];
			wait1Msec(1000);
			three=SensorValue[quad];
			wait1Msec(1000);
			four=SensorValue[quad];
			wait1Msec(1000);
			five=SensorValue[quad];
			wait1Msec(1000);
			six=SensorValue[quad];
			wait1Msec(1000);
			seven=SensorValue[quad];
			wait1Msec(1000);
			eight=SensorValue[quad];
			wait1Msec(1000);
			nine=SensorValue[quad];
			wait1Msec(1000);
			ten=SensorValue[quad];
			wait1Msec(1000);
			battery10=mainBattery;
			timerBool=false;
		}
	}
}