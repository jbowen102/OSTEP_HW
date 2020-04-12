#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "dbg.h"


int main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("Wrong number of arguments. Need three (including MB of mem and seconds to run).\n");
    return -1;
  } else {

    char *mem_size_str = argv[1];
    int mem_size = atoi(mem_size_str)*1000000L;
    // printf("Memory to use: %s MB\n", mem_size);

    char *my_mem = malloc(mem_size);
    char *my_mem_ptr2 = my_mem;    // This does not alias.

    printf("Location of malloc'd my_mem: %p\n", my_mem);
    // printf("Location second ptr to this spot: %p\n", my_mem_ptr2);


    struct timespec ts;
    // clock_gettime(CLOCK_BOOTTIME, &ts);
    // clock_gettime(CLOCK_REALTIME, &ts);
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);

    // printf("Start time val: %lu ms\n", ts.tv_nsec/1000000L);
    // printf("Start time val: %lu micros\n", ts.tv_nsec/1000);
    printf("Start time val: %lu seconds\n", ts.tv_sec);

    struct timespec ts2;
    long unsigned runtime_s = atoi(argv[2]);
    // clock_gettime(CLOCK_REALTIME, &ts2);
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts2);

    for (int i = 0; (ts2.tv_sec - ts.tv_sec) < runtime_s; i++) {
      // debug("Entered loop.\n");
      if (i % 2 == 0) {
        // *my_mem_ptr2++;
        my_mem_ptr2[i]++;
      } else {
        // *my_mem_ptr2--;
        my_mem_ptr2[i]--;
      }
      clock_gettime(CLOCK_MONOTONIC_RAW, &ts2);

      if (i > mem_size - 1) {
        // reset
        i = 0;
        my_mem_ptr2 = my_mem;
      }
    }

    printf("End time val: %lu seconds\n", ts2.tv_sec);
    // printf("Time val: %ld ns\n", ts2.tv_nsec);
    // // printf("Difference: %ld ns\n", ts2.tv_nsec - ts.tv_nsec);
    // printf("Difference: %ld ms\n", (ts2.tv_nsec - ts.tv_nsec)/1000000);

    // fgetc(my_mem);
    free(my_mem);
    return 0;

error:
  if (my_mem)
    free(my_mem);
  return -1;
}

}


// https://stackoverflow.com/questions/3523442/difference-between-clock-realtime-and-clock-monotonic
// https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html
