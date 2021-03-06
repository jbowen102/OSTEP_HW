#include <stdio.h>        // needed for printf() and fprintf()
#include <stdlib.h>       // needed for exit()
#include <unistd.h>       // needed for fork()
#include <sys/wait.h>     // needed for wait()


int main(int argc, char *argv[])
{
  int rc = fork();  // rc: return code
  int rc2 = fork();  // rc: return code
  int rcs[2];

  (void) pipe(rcs);

  if (rc < 0) {             // error
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {    // child process
    printf("I am child (PID %d).\n", getpid());
  } else {                // parent process
    printf("I am parent (PID %d). rc = %d\n", getpid(), rc2);
  }

  return 0;
}
