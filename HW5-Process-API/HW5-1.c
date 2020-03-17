#include <stdio.h>        // needed for printf() and fprintf()
#include <stdlib.h>       // needed for exit()
#include <unistd.h>       // needed for fork()
#include <sys/wait.h>     // needed for wait()


int main(int argc, char *argv[])
{
  int x = 5;
  int rc = fork();  // rc: return code

  if (rc < 0) {             // error
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {    // child process
    x += 100;   // results in 105
    printf("I am child. x = %d\n", x);
  } else {                // parent process
    // wait(NULL);
    x += 1;     // results in 6
    printf("I am parent. x = %d\n", x);
  }

  return 0;
}
