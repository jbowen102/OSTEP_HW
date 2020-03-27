#include <stdio.h>        // needed for printf() and fprintf()
#include <stdlib.h>       // needed for exit()
#include <unistd.h>       // needed for fork()
#include <sys/wait.h>     // needed for wait()


int main(int argc, char *argv[])
{
  int rc = fork();  // rc: return code

  if (rc < 0) {             // error
    fprintf(stderr, "fork failed\n");
    exit(1);
  // } else if (rc > 0) {
  //   printf("goodbye\n");
  } else if (rc == 0) {    // child process
    printf("hello\n");
  } else {                // parent process
    // wait(NULL);
    // pause();
    usleep(10 * 1000);
    printf("goodbye\n");
  }

  return 0;
}
