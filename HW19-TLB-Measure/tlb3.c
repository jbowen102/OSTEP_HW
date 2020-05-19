#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <time.h>
#include "dbg.h"

#define BILLION 1000000000
#define PAGESIZE 4096

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
  check(argc == 3, "Not enough args. Need num_pages and num_trials.");

  // int rc = print_clock_precision(CLOCK_MONOTONIC_RAW);
  // check(rc == 0, "print_clock_precision failed.");
  // int mypid = getpid();

  // pin thread to CPU 0
  cpu_set_t proc_mask;
  CPU_ZERO(&proc_mask);
  CPU_SET(0, &proc_mask);
  sched_setaffinity(0, sizeof(cpu_set_t), &proc_mask);

  int num_pages = atoi(argv[1]);
  int num_trials = atoi(argv[2]);
  debug("page_size: %d", PAGESIZE);
  debug("num_pages: %d", num_pages);
  debug("num_trials: %d", num_trials);

  int ints_per_page = PAGESIZE / sizeof(int);
  int total_int_count = num_pages * ints_per_page;
  // debug("sizeof(int): %lu", sizeof(int));
  debug("ints_per_page: %d", ints_per_page);
  debug("total_int_count: %d", total_int_count);

  int *int_array = calloc(total_int_count, sizeof(int));
  check_mem(int_array);

  int tot_mem_accesses = num_pages * num_trials;
  int j;

  struct timespec ts, ts2;
  clock_gettime(CLOCK_MONOTONIC_RAW, &ts);

  for (j = 0; j < num_trials; j+=1)
  {
    // loops through int_array and touches first int of each page.
    for (int i = 0; i < total_int_count; i+=ints_per_page)
    {
      // debug("Value of ts seconds in main loop: %lu", ts.tv_sec);
      // debug("Value of ts nseconds in main loop: %lu", ts.tv_nsec);
      int_array[i] += 1;
      // single_time_spent = diff_calc(&ts, &ts2);
      // printf("%lu\n", time_spent);

      // printf("%d\n", int_array[i]);
      // asm(""); // trying to stop compiler optimization from ignoring loop.
      // debug("%d", int_array[i]);
    }
  }

  long unsigned avg_time_spent = diff_calc(&ts, &ts2) / tot_mem_accesses;
  // printf("Avg time spent per page for %d pages: %lu ns\n", num_pages, avg_time_spent);
  // printf("%lu\n", avg_time_spent);
  // debug("a[%d]: %d\t\tTime spent: %lu ns", i, int_array[i], avg_time_spent);

  free(int_array);
  return avg_time_spent;
error:
  if (int_array) free(int_array);
  return -1;
}
