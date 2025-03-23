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
int main() {
    int arr[ROWS][COLS];  // Declare the 2D array.
    srand(time(NULL));    // Seed the random number generator.

    // Fill the 2D array with random values.
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            arr[i][j] = rand() % 1000000;  // Random numbers between 0 and 999999.
    // Serial Execution: Baseline measurement.
    double totalSerialTime = 0.0;
    int maxSerial;
    for (int run = 0; run < NUM_RUNS; run++) {
        clock_t start = clock();  // Start time measurement.
        maxSerial = arr[0][0];
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                if (arr[i][j] > maxSerial)
                    maxSerial = arr[i][j];
        clock_t end = clock();    // End time measurement.
        totalSerialTime += ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;  // Convert to milliseconds.
    }
    double avgSerialTime = totalSerialTime / NUM_RUNS;
    printf("Serial Execution: Avg Time = %.3f ms, Max = %d\n", avgSerialTime, maxSerial);
    // Define configurations for static scheduling.
    // Testing with 4, 16, and 32 threads using chunk sizes 100, 200, and 400 respectively.
    int threads[3] = {4, 16, 32};
    int chunks[3]  = {100, 200, 400};
    double avgStatic[3] = {0.0, 0.0, 0.0};
    int maxVal;

    // Loop through each configuration.
    for (int config = 0; config < 3; config++) {
        double totalTime = 0.0;
        for (int run = 0; run < NUM_RUNS; run++) {
            clock_t start = clock();
            maxVal = findMaxStatic(arr, threads[config], chunks[config]);
            clock_t end = clock();
            totalTime += ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
        }
        avgStatic[config] = totalTime / NUM_RUNS;
        printf("Static Scheduling: %d threads (chunk size = %d): Avg Time = %.3f ms, Max = %d\n", 
               threads[config], chunks[config], avgStatic[config], maxVal);
    }
