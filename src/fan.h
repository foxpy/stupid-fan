#ifndef _STUPIDFAN_FAN_H
#define _STUPIDFAN_FAN_H

#include "state.h"

#define WATCHDOG_FORMAT_STR "watchdog %u"

int fan_watchdog(int fd, unsigned timeout);
int set_fan_speed(int fd, state_t speed);

#endif
