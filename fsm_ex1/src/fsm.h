#ifndef FSM_H_
#define FSM_H_


enum IrrigationModes
{
	IDLE_MODE = 1,
	IRRIGATION_MODE = 2,
	EXTRACT_MODE = 3,
};


enum SensorStates
{
	INIT,
	GPS_WAIT_FOR_FIX,
	PROCESS_IOT,
	READ_SENSORS,
	PREPARE_SLEEP,
	SLEEP,
};

typedef enum
{
	SENSOR_STATE_DEFAULT = -1,
	SENSOR_STATE_INIT = INIT,
	SENSOR_STATE_GPSWAIT = GPS_WAIT_FOR_FIX,
	SENSOR_STATE_PROCESS = PROCESS_IOT,
	SENSOR_STATE_READSENSORS = READ_SENSORS,
	SENSOR_STATE_PREP_SLEEP = PREPARE_SLEEP,
	SENSOR_STATE_SLEEP = SLEEP,
} sensorState_t;


void PrintState(sensorState_t state);
sensorState_t sensor_StateMachine(void);


#endif /* FSM_H_ */
