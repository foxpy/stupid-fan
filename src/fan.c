#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "fan.h"
#include "state.h"

int fan_watchdog(int fd, unsigned timeout)
{
	char watchdog_str[32];
	int size;

	if (timeout > 120)
		return -1;

	size = snprintf(watchdog_str, sizeof(watchdog_str),
	                WATCHDOG_FORMAT_STR, timeout);
	if (write(fd, watchdog_str, size) == -1)
		return -1;

	return EXIT_SUCCESS;
}

int set_fan_speed(int fd, state_t speed)
{
	char speed_str[32];

	strcpy(speed_str, "level ");
	switch (speed) {
	case SILENT:
		strcat(speed_str, "0");
		break;
	case SPEED1:
		strcat(speed_str, "1");
		break;
	case SPEED2:
		strcat(speed_str, "2");
		break;
	case SPEED3:
		strcat(speed_str, "3");
		break;
	case SPEED4:
		strcat(speed_str, "4");
		break;
	case SPEED5:
		strcat(speed_str, "5");
		break;
	case SPEED6:
		strcat(speed_str, "6");
		break;
	case SPEED7:
		strcat(speed_str, "7");
		break;
	case DISENGAGED:
		strcat(speed_str, "disengaged");
		break;
	case AUTO:
		strcat(speed_str, "auto");
		break;
	}

	if (write(fd, speed_str, strlen(speed_str)) == -1)
		return -1;
	return EXIT_SUCCESS;
}
