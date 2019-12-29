#include <stdlib.h>
#include <unistd.h>

int read_therm(int fd)
{
	char buf[32];
	ssize_t size;

	if ((size = read(fd, buf, sizeof(buf)-1)) == -1)
		return -1;
	buf[size] = '\0';
	lseek(fd, 0, SEEK_SET);
	return atoi(buf)/1000;
}
