#include <stdio.h>
//
#include "fsm.h"

#define TRESHOLD_HI		10
#define TRESHOLD_LO		5
//
#define REPORT_INTERVAL	3


enum IrrigationModes mode = IDLE_MODE;
sensorState_t SensorState = INIT;

int reportTimer = 0;
int reportCnt = 0;
int sleepMode = 0;
int readVal = 7;		// dummy sensor READ-value.


static enum SensorStates CheckChangeOfState(enum SensorStates previousState)
{
	if (previousState == SLEEP)
	{
		return READ_SENSORS;					// TODO: what's the point - SIMPLIFY! (use a helper state or whatever ...)
	}
	else if (previousState == READ_SENSORS)
	{
		if (mode == IRRIGATION_MODE)
		{
			reportTimer++;
			printf("reportTimer is now %d\r\n", reportTimer);

			if (readVal >= TRESHOLD_HI)
			{
				// pass
			}
			else
			{
				if ( readVal <= TRESHOLD_LO )
				{
					return PROCESS_IOT;
				}
				else
				{
					printf("Pressure between HI- and LO-threshold. No action ...\r\n");
					// pass...
				}
			}

			if ( reportTimer >= REPORT_INTERVAL )	// Time to report?
			{
				printf("Time to report: sequence counter increment!\r\n");
				reportTimer = 0;
				reportCnt++;
				//printf("NORMAL mode, report!\r\n");
				//printf("Starting up IoT state-machine ...\r\n");
				return PROCESS_IOT;
			}
			return PREPARE_SLEEP;	// mode == IRR_MODE && pressure > HI
		}
		else
			return PROCESS_IOT;		// mode != IRR_MODE --> mode == EXTRACT or IDLE
	}
	else	// current: state != READ_SENSORS && state != SLEEP (or, woken up from sleep)
	{
		return PREPARE_SLEEP;		// TODO: craziness - SINGLE POINT OF RETURN in state-change logic! Modify!!
	}
}


/* Global functions */

const char stateNameTable[7][12] = { "DEFAULT", "INIT", "GPSWAIT", "PROCESS_IOT", "READ", "PREP_SLEEP", "SLEEP" };

void PrintState(sensorState_t state)
{
	int idx = (int)state + 1;

	printf("%s", stateNameTable[idx]);
}


sensorState_t sensor_StateMachine(void)
{
	static enum SensorStates SensorState = INIT;

	switch (SensorState)
	{
		case INIT:									// 1) Initial state
			printf("state = INIT\r\n");
			SensorState = PREPARE_SLEEP;
			break;

		case READ_SENSORS:
			printf("Reading sensors ...\r\n");

			/* DUMMY READ */
			// readVal = rand(max, min);

			SensorState = CheckChangeOfState(READ_SENSORS);

			if (SensorState == PROCESS_IOT)
			{
				//printf("State=PROCESS_IOT\r\n");
			}

			break;

		case PROCESS_IOT:									// 5)  from READ_SENSORS (5) or PREPARE_SLEEP (2)
			//printf("State = PROCESS_IOT\r\n");

			// Transfer data:
//			if ( gprsState == GPRS_SLEEP )
//			{
//				SensorState = PREPARE_SLEEP;
//			}

			//printf("Sending data ... done!\r\n");
			SensorState = PREPARE_SLEEP;
			break;

		case PREPARE_SLEEP:										// 2)  from INIT (1) or PROCESS_IOT (5)
			printf("State = PREPARE_SLEEP\r\n");

			SensorState = SLEEP;
			//printf("Next state = SLEEP         (reportTimer=%d)\r\n", reportTimer);

			break;

		case SLEEP:												// 3)  from  PREPARE_SLEEP (2)
			//printf("State = SLEEP ..... zzzzzzz ....\r\n");
			//sleep(random(min,max));
			//printf("WAKEUP!\r\n");
			SensorState = CheckChangeOfState(SLEEP);		//SensorState = CheckChangeOfState(SensorState);   ???
			break;

		default:
			SensorState = SLEEP;
			break;
	}

	if (SensorState == SLEEP || SensorState == PREPARE_SLEEP)
		return SENSOR_STATE_SLEEP;
	else
		return SENSOR_STATE_DEFAULT;
}


