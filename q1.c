#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 1000   // Number of rows in the 2D array
#define COLS 1000   // Number of columns in the 2D array
#define NUM_RUNS 10 // Number of times to execute the function for averaging execution time
int main() {
    int arr[ROWS][COLS]; // Declare the 2D array

    // Fill the 2D array with random values
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            arr[i][j] = rand() % 1000000; // Assign random values (0 to 999999)
        }
    }

    // Function to find the maximum element in a 2D array (sequential)
    int findMaxSequential(int arr[ROWS][COLS]) {
        int maxElement = arr[0][0]; // Initialize maxElement with the first element

        // Iterate through the 2D array sequentially to find the maximum element
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (arr[i][j] > maxElement) {
                    maxElement = arr[i][j];
                }
            }
        }
        return maxElement;
    }
    double totalTime = 0.0; // Variable to store total execution time

    // Execute the max-finding function multiple times and measure time
    for (int i = 0; i < NUM_RUNS; ++i) {
        clock_t start = clock(); // Start time measurement
        int maxElement = findMaxSequential(arr); // Find max element sequentially
        clock_t end = clock(); // End time measurement

        double duration = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0; // Convert to milliseconds
        totalTime += duration;

        printf("Sequential Run %d: Max = %d, Time = %.3f ms\n", i + 1, maxElement, duration);
    }
    // Compute and print the average execution time
    printf("Average sequential execution time: %.3f ms\n", totalTime / NUM_RUNS);

    return 0;
}
