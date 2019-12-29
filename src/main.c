#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include "fan.h"
#include "thermal.h"
#include "state.h"

#define FAN_PATH   "/proc/acpi/ibm/fan"
#define THERM_PATH "/sys/class/thermal/thermal_zone1/temp"

#define LOOP_TIMEOUT     4
#define WATCHDOG_TIMEOUT 5

int fan_fd, therm_fd;

void sig_handler(int signo)
{
	int status;

	status = EXIT_SUCCESS;
	switch (signo) {
	case SIGINT:
		if (fan_watchdog(fan_fd, 0) == -1) {
			fputs("Warning: fan watchdog still on\n", stderr);
			status = EXIT_FAILURE;
		}
		if (set_fan_speed(fan_fd, AUTO) == -1) {
			fputs("Warning: fan speed is not controlled by BIOS\n",
			      stderr);
			status = EXIT_FAILURE;
		}
		exit(status);
	}
}

int main(void)
{
	int therm;

	if (signal(SIGINT, sig_handler) == SIG_ERR) {
#ifdef DEBUG
		fputs("Warning: failed to set SIGINT handler\n", stderr);
#endif
	}

	if ((fan_fd = open(FAN_PATH, O_WRONLY)) == -1) {
		perror("Fan: open");
		return EXIT_FAILURE;
	}
	if ((therm_fd = open(THERM_PATH, O_RDONLY)) == -1) {
		perror("Thermal: open");
		return EXIT_FAILURE;
	}

	if (fan_watchdog(fan_fd, WATCHDOG_TIMEOUT) == -1) {
		fputs("Failed to setup watchdog\n", stderr);
		return EXIT_FAILURE;
	}

	while(sleep(LOOP_TIMEOUT) == 0) {
		if ((therm = read_therm(therm_fd)) == -1) {
			fputs("Failed to read therm\n", stderr);
			return EXIT_FAILURE;
		}
		if (set_fan_speed(fan_fd, speed_from_therm(therm)) == -1) {
			fputs("Failed to set fan speed\n", stderr);
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
