#include <stdio.h>        // needed for printf() and fprintf()
#include <stdlib.h>       // needed for exit()
#include <unistd.h>       // needed for fork()
#include <fcntl.h>      // needed for the arguments to the open()
#include <sys/wait.h>     // needed for wait()


int main(int argc, char *argv[])
{
  int fd = open("./HW5-2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
      // fd: file descriptor
      // https://pubs.opengroup.org/onlinepubs/9699919799/functions/open.html

  int rc = fork();

  if (rc < 0) {             // error
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {    // child process
    printf("I am child. PID = %d\n", getpid());
    write(fd, , );
    // https://en.wikipedia.org/wiki/Write_(system_call)
  } else {                // parent process
    // wait(NULL);
    // write(fd, , );
    printf("I am parent. PID = %d\n", getpid());
  }

  return 0;
}
