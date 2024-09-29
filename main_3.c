#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Function to perform matrix-vector multiplication
void matrix_vector_mult(int rows, int cols, int iterations) {
    // Allocate memory for matrix and vector
    double **matrix = (double **)malloc(rows * sizeof(double *));
    double *vector = (double *)malloc(cols * sizeof(double));
    double *result = (double *)malloc(rows * sizeof(double));

    for (int i = 0; i < rows; i++) {
        matrix[i] = (double *)malloc(cols * sizeof(double));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (double)(i + j);  // Example initialization
        }
    }
    for (int i = 0; i < cols; i++) {
        vector[i] = 1.0;  // Example initialization
    }

    // Perform the multiplication iterations
    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < rows; i++) {
            result[i] = 0.0;
            for (int j = 0; j < cols; j++) {
                result[i] += matrix[i][j] * vector[j];
            }
        }
    }

    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);
}

// Function to get execution time for matrix-vector multiplication
double get_execution_time(int rows, int cols, int iterations) {
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Run the matrix-vector multiplication
    matrix_vector_mult(rows, cols, iterations);

    gettimeofday(&end, NULL);
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6; // seconds
}

// Function to write results to a CSV file
void write_to_csv(int size, double average_time, double normalized_performance) {
    FILE *file = fopen("performance_results.csv", "a");
    if (file != NULL) {
        fprintf(file, "%d,%f,%f\n", size, average_time, normalized_performance);
        fclose(file);
    } else {
        printf("Error opening file for writing.\n");
    }
}

int main() {
    // Parameters
    int increments = 500;
    int max_size = 10000;
    int repetitions = 100;

    // Clear the results file
    FILE *file = fopen("performance_results.csv", "w");
    if (file) {
        fprintf(file, "Size,Average Time (s),Normalized Performance (ops/s)\n");
        fclose(file);
    }

    // Run experiments for each size
    for (int size = 500; size <= max_size; size += increments) {
        double total_time = 0.0;

        // Repeat the experiment 5 times
        for (int run = 0; run < 5; run++) {
            double exec_time = get_execution_time(size, size, repetitions);
            total_time += exec_time;
            printf("Size: %d, Run %d: Execution Time = %f seconds\n", size, run + 1, exec_time);
        }

        // Calculate average execution time
        double average_time = total_time / 5.0;

        // Calculate the number of operations: 2 * size^2
        double total_operations = 2.0 * (double)(size * size * repetitions);
        double normalized_performance = total_operations / average_time; // ops/s

        // Write results to CSV
        write_to_csv(size, average_time, normalized_performance);
        printf("Average Execution Time for Size %d: %f seconds, Normalized Performance: %f ops/s\n", size, average_time, normalized_performance);
    }

    return 0;
}
