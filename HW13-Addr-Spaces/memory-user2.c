#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "dbg.h"

#define BILLION 1000000000


long unsigned diff_calc(struct timespec *ts1, struct timespec *ts2)
{
  clock_gettime(CLOCK_MONOTONIC_RAW, ts2);
  debug("Value of ts2 seconds in diff_calc: %lu", ts2->tv_sec);
  debug("Value of ts2 nseconds in diff_calc: %lu", ts2->tv_nsec);
  long unsigned diff = BILLION * (ts2->tv_sec - ts1->tv_sec) + (ts2->tv_nsec - ts1->tv_nsec);
  return diff/BILLION;
}

int main(int argc, char *argv[])
{
  check(argc == 3, "Wrong number of arguments. Need three (including MB of mem and seconds to run).")

  long unsigned runtime_s = atoi(argv[2]);

  char *mem_size_str = argv[1];
  int mem_size = atoi(mem_size_str)*1000000;
  // printf("Memory to use: %s MB\n", mem_size);

  // char *my_mem = calloc(1, mem_size+1);
  char *my_mem = malloc(mem_size);
  check_mem(my_mem);
  char *my_mem_ptr2 = my_mem;    // This does not alias.

  log_info("Location of malloc'd my_mem: %p", my_mem);
  // printf("Location second ptr to this spot: %p\n", my_mem_ptr2);

  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC_RAW, &ts);

  // printf("Start time val: %lu ms\n", ts.tv_nsec/1000000L);
  // printf("Start time val: %lu micros\n", ts.tv_nsec/1000);
  log_info("Start time val: %lu seconds, %lu ns", ts.tv_sec, ts.tv_nsec);

  struct timespec ts2;

  for (int i = 0; diff_calc(&ts, &ts2) < runtime_s; i++) {
    debug("Entered loop.");
    if (i % 2 == 0) {
      // *my_mem_ptr2++;
      my_mem_ptr2[i]++;
    } else {
      // *my_mem_ptr2--;
      my_mem_ptr2[i]--;
    }

    if (i > mem_size - 1) {
      // reset
      i = 0;
      my_mem_ptr2 = my_mem;
    }
  }

  log_info("End time val: %lu seconds, %lu ns", ts2.tv_sec, ts2.tv_nsec);
  // printf("Time val: %ld ns\n", ts2.tv_nsec);
  // // printf("Difference: %ld ns\n", ts2.tv_nsec - ts.tv_nsec);
  // printf("Difference: %ld ms\n", (ts2.tv_nsec - ts.tv_nsec)/1000000);

  // fgetc(my_mem);
  free(my_mem);
  return 0;

error:
  if (my_mem) free(my_mem);
  return -1;
}


// https://stackoverflow.com/questions/3523442/difference-between-clock-realtime-and-clock-monotonic
// https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html
