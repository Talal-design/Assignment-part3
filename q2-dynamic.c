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
int main() {
    int arr[ROWS][COLS];  // Declare the 2D array.
    srand(time(NULL));    // Seed the random number generator.

    // Fill the array with random values.
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            arr[i][j] = rand() % 1000000;  // Random numbers between 0 and 999999.
        }
    }
    // Serial Execution (baseline).
    double totalSerialTime = 0.0;
    int maxSerial;
    for (int run = 0; run < NUM_RUNS; run++) {
        clock_t start = clock();  // Start time measurement.
        maxSerial = arr[0][0];
        // Compute maximum element sequentially.
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (arr[i][j] > maxSerial)
                    maxSerial = arr[i][j];
            }
        }
        clock_t end = clock();    // End time measurement.
        totalSerialTime += ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;  // Convert to milliseconds.
    }
    double avgSerialTime = totalSerialTime / NUM_RUNS;
    printf("Serial Execution: Avg Time = %.3f ms, Max = %d\n", avgSerialTime, maxSerial);
    // Define configurations for dynamic scheduling.
    // Here we use the same configurations as for static scheduling:
    // 4 threads with chunk size 100, 16 threads with chunk size 200, 32 threads with chunk size 400.
    int threads[3] = {4, 16, 32};
    int chunks[3]  = {100, 200, 400};
    double avgDynamic[3] = {0.0, 0.0, 0.0};
    int maxVal;
    
    // Loop through each configuration.
    for (int config = 0; config < 3; config++) {
        double totalTime = 0.0;
        for (int run = 0; run < NUM_RUNS; run++) {
            clock_t start = clock();  // Start time measurement.
            maxVal = findMaxDynamic(arr, threads[config], chunks[config]);
            clock_t end = clock();    // End time measurement.
            totalTime += ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
        }
        avgDynamic[config] = totalTime / NUM_RUNS;
        printf("Dynamic Scheduling: %d threads (chunk size = %d): Avg Time = %.3f ms, Max = %d\n", 
               threads[config], chunks[config], avgDynamic[config], maxVal);
    }
    return 0;
}
