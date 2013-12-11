#include <msp430.h> 
#include "Lab6_Robot_Movement/Robot_Movement.h"
#include "Lab7_Robot_Sensors/Robot_Sensors.h"

/*
 * main.c
 */

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    initMotor();
    initSensors();
    moveRobotForward();
    unsigned int myLeftReading;
    unsigned int myRightReading;
    unsigned int myCenterReading;

    while(1)
    {
		myLeftReading = checkLeftSensor();
		myRightReading = checkRightSensor();
		myCenterReading = checkCenterSensor();

		if (myRightReading > 0x380) //gets away from right wall
		{
			moveRobotSmallLeft();
			__delay_cycles(10000);
			stopRobot();
			__delay_cycles(10000);


		}
		else if (myCenterReading >= 0x2F0) //turns left if something is in front of it
		{
			moveRobotBackward();
			__delay_cycles(10000);


			stopRobot();
			__delay_cycles(500000);

			moveRobotSmallLeft();
			__delay_cycles(400000);

		}
		else if ((myRightReading > 0x300) && (myCenterReading < 0x2A0)) //moves forward if not too far away
		{																//from right wall

			moveRobotForward();
			__delay_cycles(30000);
			stopRobot();
			__delay_cycles(20000);


		}
		else						//does looping right if too far away from right wall
		{
			moveRobotForward();
			__delay_cycles(2000);

			moveRobotBigRight();
			__delay_cycles(1000);

			stopRobot();
			__delay_cycles(1000);


		}


    }
	return 0;
}
