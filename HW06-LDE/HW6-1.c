#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>


int main(int argc, char *argv[])
{

	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("Start: %ld\n", tv.tv_sec);

	int fd;
	fd = open("./HW6-LDE_output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	int i;
	void *buffer;
	for (i = 0; i < 10000000; i++) {
		read(fd, buffer, 0);
		// printf("i: %d\n", i);
	}

	struct timeval tv2;
	gettimeofday(&tv2, NULL);
	printf("End: %ld\n", tv2.tv_sec);

	return 0;
}


// Result:
// Start: 1584912818
// End: 1584912818

// https://stackoverflow.com/questions/5362577/c-gettimeofday-for-computing-time
// https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
