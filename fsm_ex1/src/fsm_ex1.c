/*
 ============================================================================
 Name        : fsm_ex1.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//
#include "fsm.h"


extern int reportCnt;
extern enum IrrigationModes mode;


int main(void)
{
	sensorState_t state;

	for (int i=0; i<25; i++)
	{
		printf("State check (iteration=%d):\r\n", i);
		printf("================\r\n");
		printf("state = ");
		PrintState(state);
		printf("\r\n");
		printf("ReportCnt = %d\r\n\r\n", reportCnt);
		// Update STATE:
		if (i>5 && i<20)
		{
			mode = IRRIGATION_MODE;
		}

		state = sensor_StateMachine();
	}

	return EXIT_SUCCESS;
}
