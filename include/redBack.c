/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

/** ------------------- 72832S autonomous functions -----------------*/

/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

		startTask(intakeOnTask);
		delay();
    punch();
    delay();
    driveTurn(false, 7.75, 50);
    delay();
    driveBackward(0.3);
    delay();
		driveForward(1.5);
		delay();
    driveTurn(true, 7.75, 50);
    delay();
    driveForward(0.3);
    delay();
    driveBackward(0.5);
    delay();
    punch();
    delay();
    driveTurn(false, 7.75, 50);
    delay();
    driveBackward(1);
    delay();
    driveTurn(true, 7.75, 50);
    delay();
    driveForward(1.5);
