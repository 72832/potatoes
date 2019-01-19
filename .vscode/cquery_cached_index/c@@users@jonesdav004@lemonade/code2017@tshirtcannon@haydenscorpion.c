#pragma config(Motor,  port1,           rightmot,      tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           leftmot,       tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           thehamder,     tmotorVex393TurboSpeed_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true){
		motor[leftmot]=vexRT[Ch2];
		motor[rightmot]=vexRT[Ch3];
		if (vexRT[Btn6U]) {
			motor[port3] = 127;
		}
		else if (vexRT[Btn6D])
		{
			motor[port3] = -127;
		}
		else
		{
			motor[port3] = 0;
		}
	}


}
