#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define ROWS 1000         // Number of rows in the 2D array
#define COLS 1000         // Number of columns in the 2D array
#define NUM_RUNS 10       // Number of runs for averaging execution time
// Function: findMaxDynamic
// Purpose: Finds the maximum element in a 2D array using OpenMP dynamic scheduling.
// Parameters:
//   - arr: The 2D array to search.
//   - numThreads: Number of threads to use.
//   - chunkSize: Number of iterations each thread processes at a time.
int findMaxDynamic(int arr[ROWS][COLS], int numThreads, int chunkSize) {
    int maxElement = arr[0][0];  // Initialize the maximum element.
    omp_set_num_threads(numThreads);  // Set the number of threads.
    
    // The parallel for loop uses:
    //   - collapse(2): to merge the two nested loops for better load balancing.
    //   - schedule(dynamic, chunkSize): to dynamically assign chunks of iterations to threads.
    //   - reduction(max : maxElement): to combine the maximum values computed by each thread.
    #pragma omp parallel for collapse(2) schedule(dynamic, chunkSize) reduction(max : maxElement)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (arr[i][j] > maxElement)
                maxElement = arr[i][j];
        }
    }
    return maxElement;  // Return the overall maximum value.
}
