#include <stdlib.h>
#include <stdio.h>

#include "state.h"

state_t speed_from_therm(int therm)
{
	static state_t state = SILENT;
	switch (state) {
	case SILENT:
		if (therm > 60) state = SPEED1;
		break;
	case SPEED1:
		if (therm > 62) state = SPEED2;
		if (therm < 55) state = SILENT;
		break;
	case SPEED2:
		if (therm > 64) state = SPEED3;
		if (therm < 57) state = SPEED1;
		break;
	case SPEED3:
		if (therm > 66) state = SPEED4;
		if (therm < 59) state = SPEED2;
		break;
	case SPEED4:
		if (therm > 68) state = SPEED5;
		if (therm < 61) state = SPEED3;
		break;
	case SPEED5:
		if (therm > 70) state = SPEED6;
		if (therm < 63) state = SPEED4;
		break;
	case SPEED6:
		if (therm > 72) state = SPEED7;
		if (therm < 65) state = SPEED5;
		break;
	case SPEED7:
		if (therm > 75) state = DISENGAGED;
		if (therm < 67) state = SPEED6;
		break;
	case DISENGAGED:
		if (therm < 70) state = SPEED7;
		break;
	case AUTO:
		fputs("Panic: control flow reached unreachable code\n", stderr);
		exit(EXIT_FAILURE);
	}

	return state;
}
