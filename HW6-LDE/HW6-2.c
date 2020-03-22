#include <stdio.h>        // needed for printf() and fprintf()
#include <stdlib.h>       // needed for exit()
#include <unistd.h>       // needed for fork()
#include <sys/wait.h>     // needed for wait()
#include <sched.h>


int main(int argc, char *argv[])
{
  int rc = fork();  // rc: return code
  int rc2 = fork();  // rc: return code
  int rcs[2] = {rc , rc2};
  int rcs2[2] = {rc2 , rc};

  (void) pipe(rcs);
  (void) pipe(rcs2);

  if (rc < 0) {             // error
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {    // child process
    char buffer[30];
    int i;
    for (i = 0; i < 12; i++) {
      // odesc = open(stdin)
  		read(STDIN_FILENO, buffer, 29);
      printf("I am child (PID %d).\n", getpid());
  		// printf("i: %d\n", i);
  	}
  } else {                // parent process
    wait(NULL);
    printf("I am parent (PID %d). rc = %d\n", getpid(), rc);
  }

  return 0;
}
