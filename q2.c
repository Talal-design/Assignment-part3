#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define ROWS 1000         // Number of rows in the 2D array
#define COLS 1000         // Number of columns in the 2D array
#define NUM_RUNS 10       // Number of runs for averaging execution time
// Function: findMaxStatic
// Purpose: Finds the maximum element in a 2D array using OpenMP static scheduling.
// Parameters:
//   - arr: The 2D array to search.
//   - numThreads: Number of threads to use.
//   - chunkSize: Number of iterations each thread processes at a time.
int findMaxStatic(int arr[ROWS][COLS], int numThreads, int chunkSize) {
    int maxElement = arr[0][0];  // Initialize the maximum element with the first array element.
    omp_set_num_threads(numThreads);  // Set the desired number of threads.
    
    // The parallel for loop uses:
    //   - collapse(2): to combine the two nested loops into one parallel loop.
    //   - schedule(static, chunkSize): to assign fixed-size chunks of iterations to threads.
    //   - reduction(max : maxElement): to safely compute the maximum value across threads.
    #pragma omp parallel for collapse(2) schedule(static, chunkSize) reduction(max : maxElement)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (arr[i][j] > maxElement)
                maxElement = arr[i][j];
        }
    }
    return maxElement;  // Return the maximum element found.
}
