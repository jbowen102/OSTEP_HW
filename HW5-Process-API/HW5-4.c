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
  } else if (rc == 0) {    // child process
    printf("I am child (PID %d).\n", getpid());
    char *arg_list[2];
    arg_list[0] = "/bin/ls";
    arg_list[1] = "";
    arg_list[2] = '\0';
    // execl(arg_list[0], arg_list[1], arg_list[2]);
    execl(arg_list[0], arg_list[1], (char *) NULL);
  } else {                // parent process
    // wait(NULL);
    printf("I am parent (PID %d).\n", getpid());
  }

  return 0;
}
