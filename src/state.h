#ifndef _STUPIDFAN_STATE_H
#define _STUPIDFAN_STATE_H

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
