#ifndef _FAN_STATE
#define _FAN_STATE

enum state_t {
	SILENT,
	SPEED1,
	SPEED2,
	SPEED3,
	SPEED4,
	SPEED5,
	SPEED6,
	SPEED7,
	DISENGAGED,
	AUTO
};

typedef enum state_t state_t;

state_t speed_from_therm(int therm);
#endif
