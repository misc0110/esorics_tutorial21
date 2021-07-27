#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "cacheutils.h"

#define HISTOGRAM_ENTRIES 1000
#define HISTOGRAM_SCALE 5

#define LOGFILE "histogram.csv"


/* TODO: Return how long it takes to load the value from "address" */
size_t measure_access_time(void* address) {
  uint64_t x = rdtsc();
  maccess(address);
  uint64_t y = rdtsc();
  return y - x;
}

/* TODO: Build a histogram of cache hits */
void measure_hits(void* address, size_t* histogram, size_t number_of_measurements) {
    for(size_t i = 0; i < number_of_measurements; i++) {
        size_t hit = measure_access_time(address);
        if(hit < HISTOGRAM_ENTRIES) histogram[hit]++;
    }
}

/* TODO: Build a histogram of cache misses */
void measure_misses(void* address, size_t* histogram, size_t number_of_measurements) {
    for(size_t i = 0; i < number_of_measurements; i++) {
        flush(address);
        size_t miss = measure_access_time(address);
        if(miss < HISTOGRAM_ENTRIES) histogram[miss]++;
    }
}

/* Memory for histograms */
size_t hit_histogram[HISTOGRAM_ENTRIES], miss_histogram[HISTOGRAM_ENTRIES];
/* Address we measure (exactly one physical page) */
char __attribute__((aligned(4096))) address[4096];

int main(int argc, char* argv[]) {
  /* Define parameters */
  FILE* logfile = fopen(LOGFILE, "w+");
  if (logfile == NULL) {
    fprintf(stderr, "Error: Could not open logfile: %s\n", LOGFILE);
    return -1;
  }

  fprintf(logfile, "Time,Hit,Miss\n");

  /* Initialize address */
  memset(address, 1, 4096);

  /* Measure hits and misses */
  measure_hits(address, hit_histogram, HISTOGRAM_ENTRIES);
  measure_misses(address, miss_histogram, HISTOGRAM_ENTRIES);

  /* Print histogram */
  for (size_t i = 0; i < HISTOGRAM_ENTRIES; i += HISTOGRAM_SCALE) {
    size_t hit = 0, miss = 0;
    for(size_t scale = 0; scale < HISTOGRAM_SCALE; scale++) {
        hit += hit_histogram[i + scale];
        miss += miss_histogram[i + scale];
    }
    fprintf(stdout, "%4zu: %10zu %10zu\n", i, hit, miss);
    if (logfile != NULL) {
      fprintf(logfile, "%zu,%zu,%zu\n", i, hit, miss);
    }
  }

  /* Clean-up */
  fclose(logfile);

  return 0;
}
