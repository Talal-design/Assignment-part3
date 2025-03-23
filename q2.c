#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define ROWS 1000         // Number of rows in the 2D array
#define COLS 1000         // Number of columns in the 2D array
#define NUM_RUNS 10       // Number of runs for averaging execution time
