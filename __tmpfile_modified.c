#include <stdio.h>
#include <fcntl.h>
#include "stdio_impl.h"

#define MAXTRIES 100

char *__randname(char *);

FILE *__tmpfile_modified(void)
{
	char s[] = "/tmpfile_XXXXXX";
	int fd;
	FILE *f;
	int try;
	for (try=0; try<MAXTRIES; try++) {
		__randname(s+13);
		fd = sys_open(s, O_RDWR|O_CREAT|O_EXCL, 0600);
		if (fd >= 0) {
			f = __fdopen(fd, "w+");
			if (!f) __syscall(SYS_close, fd);
			return f;
		}
	}
	return 0;
}