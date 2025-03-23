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
