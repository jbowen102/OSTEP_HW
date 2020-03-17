#include <stdio.h>        // needed for printf() and fprintf()
#include <stdlib.h>       // needed for exit()
#include <unistd.h>       // needed for fork()
#include <fcntl.h>      // needed for the arguments to the open()
#include <sys/wait.h>     // needed for wait()
#include <string.h>     // needed for strlen

int main(int argc, char *argv[])
{
  int fd = open("./HW5-2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
      // fd: file descriptor
      // https://pubs.opengroup.org/onlinepubs/9699919799/functions/open.html
  if (fd < 0) {
    fprintf(stderr, "File can't be opened.\n");
  }

  int rc = fork();

  if (rc < 0) {             // error
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {    // child process
    printf("I am child (PID %d). 1\n", getpid());
    char buf[] = {'a', 'b', 'c', '\0'};
    write(fd, buf, strlen(buf));
    printf("I am child (PID %d). 2\n", getpid());
    // https://en.wikipedia.org/wiki/Write_(system_call)
  } else {                // parent process
    wait(NULL);
    printf("I am parent (PID %d). 1\n", getpid());
    char buf2[] = {'d', 'e', 'f', '\0'};
    write(fd, buf2, strlen(buf2));
    printf("I am parent (PID %d). 2\n", getpid());
  }

  close(fd);

  return 0;
}
