#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "dbg.h"

#define BILLION 1000000000


long unsigned diff_calc(struct timespec *ts1, struct timespec *ts2)
{
  clock_gettime(CLOCK_MONOTONIC_RAW, ts2);
  // debug("Value of ts2 seconds in diff_calc: %lu", ts2->tv_sec);
  // debug("Value of ts2 nseconds in diff_calc: %lu", ts2->tv_nsec);
  long unsigned diff = BILLION * (ts2->tv_sec - ts1->tv_sec) + (ts2->tv_nsec - ts1->tv_nsec);
  return diff;
}


int print_clock_precision(int clock_id)
{
  struct timespec ts;
  int rc = clock_getres(clock_id, &ts);
  check(rc == 0, "clock_getres() failed");
  printf("Precision of clock: %lu ns\n", ts.tv_nsec);

  return 0;
error:
  return -1;
}


int main(int argc, char *argv[])
{
  check(argc == 3, "Not enough args. Need page_size and num_pages.");

  int rc = print_clock_precision(CLOCK_MONOTONIC_RAW);
  check(rc == 0, "print_clock_precision failed.");

  int page_size = atoi(argv[1]);
  int num_pages = atoi(argv[2]);
  debug("page_size: %d", page_size);
  debug("num_pages: %d", num_pages);

  int jump = page_size / sizeof(int);
  // debug("sizeof(int): %lu", sizeof(int));
  debug("jump: %d", jump);
  debug("num_pages * jump: %d", num_pages * jump);

  int *int_array = malloc(num_pages * jump * sizeof(int));
  check_mem(int_array);

  struct timespec ts, ts2;
  long unsigned time_spent;

  for (int i = 0; i < num_pages * jump; i+=jump)
  {
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    // debug("Value of ts seconds in main loop: %lu", ts.tv_sec);
    // debug("Value of ts nseconds in main loop: %lu", ts.tv_nsec);

    int_array[i] += 1;
    time_spent = diff_calc(&ts, &ts2);
    debug("a[%d]: %d\t\tTime spent: %lu ns", i, int_array[i], time_spent);
  }

  free(int_array);
  return 0;
error:
  if (int_array) free(int_array);
  return -1;
}
