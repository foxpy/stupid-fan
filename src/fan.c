#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "fan.h"
#include "state.h"

static char* levels[] = {
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"disengaged",
	"auto"
};

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
	sprintf(speed_str, "level %s", levels[speed]);

	if (write(fd, speed_str, strlen(speed_str)) == -1)
		return -1;
	return EXIT_SUCCESS;
}
