#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void matrix_vector_mult(int rows, int cols, int iterations) {
    // Allocate and initialize matrix and vector
    double **matrix = malloc(rows * sizeof(double *));
    double *vector = malloc(cols * sizeof(double));
    double *result = malloc(rows * sizeof(double));
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(double));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100; // Random initialization
        }
    }
    
    for (int i = 0; i < cols; i++) {
        vector[i] = rand() % 100; // Random initialization
    }

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

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Usage: %s <rows> <cols> <iterations>\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int iterations = atoi(argv[3]);

    struct timeval start, end;

    gettimeofday(&start, NULL);
    matrix_vector_mult(rows, cols, iterations);
    gettimeofday(&end, NULL);

    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    printf("Execution time: %.6f seconds\n", elapsed);
    return 0;
}
