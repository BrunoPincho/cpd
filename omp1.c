
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUMITER 30


/* main: process parameters */
int main(int argc, char *argv[]) {

  /* variables */
  int i, tid;

/* create parallel region, make both variable thread private */
omp_set_num_threads(2);
#pragma omp parallel private(i,tid)
  {
      /* get id of thread */
      tid = omp_get_thread_num();
       printf("%d\n", omp_get_num_threads());
/* divide loop iterations evenly by threads */
#pragma omp nowait for
      for(i = 0; i < NUMITER; i++)
	  printf("Thread: %d\titer=%d\n", tid, i);  fflush(stdout);

      /* one of these messages per thread */
      printf("Thread %d, almost..\n", tid);  fflush(stdout);
      #pragma omp barrier
      printf("Thread %d, done!\n", tid);  fflush(stdout);
  }

  /* only master thread prints this one */
  printf("All threads have finished!\n");
}