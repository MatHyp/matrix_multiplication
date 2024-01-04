#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void readMatrixFromFile(const char *filename, int ***matrix, int *rows, int *cols) {
    FILE *file = fopen(filename, "r");

    // Cannot open a file
    if (file == NULL) {
        fprintf(stderr, "Nie można otworzyć pliku %s.\n", filename);
        exit(1);
    }

    fscanf(file, "%d %d", rows, cols);

    *matrix = (int **)malloc(*rows * sizeof(int *));
    for (int i = 0; i < *rows; i++) {
        (*matrix)[i] = (int *)malloc(*cols * sizeof(int));
    }

    // Check that
    if (*rows > MAX_ROWS || *cols > MAX_COLS) {
        fprintf(stderr, "Zbyt duża macierz. Zmień rozmiary MAX_ROWS lub MAX_COLS.\n");
        fclose(file);
        exit(1);
    }

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%d", &(*matrix)[i][j]);
        }
    }

    fclose(file);
}

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void matrixMultiplication() {}

void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void writeMatrixToFile(const char *filename, int **matrix, int rows, int cols) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        fprintf(stderr, "Nie można otworzyć pliku %s do zapisu.\n", filename);
        exit(1);
    }

    fprintf(file, "%d %d\n", rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}


int main() {
    int **matrixA, **matrixB, **resultMatrix;
    int arows, acolumns, brows, bcolumns;
    int i, j, k;
    int sum = 0;

    readMatrixFromFile("matrixA.txt", &matrixA, &arows, &acolumns);
    readMatrixFromFile("matrixB.txt", &matrixB, &brows, &bcolumns);

    resultMatrix = (int **)malloc(arows * sizeof(int *));
    for (int i = 0; i < arows; i++) {
        resultMatrix[i] = (int *)malloc(bcolumns * sizeof(int));
    }

    printf("Matrix A:\n");
    printMatrix(matrixA, arows, acolumns);

    printf("\nMatrix B:\n");
    printMatrix(matrixB, brows, bcolumns);

    // Matrix multiplication

    for (i = 0; i < arows; i++) {
        for (j = 0; j < bcolumns; j++) {
            sum = 0; // Reset sum for each element in the result matrix
            for (k = 0; k < brows; k++) {
                sum += matrixA[i][k] * matrixB[k][j];
            }
            resultMatrix[i][j] = sum;
        }
    }

    printf("Result:\n");
    printMatrix(resultMatrix, arows, bcolumns);
    writeMatrixToFile("resultMatrix.txt", resultMatrix, arows, bcolumns);

    // Free allocated memory
    freeMatrix(matrixA, arows);
    freeMatrix(matrixB, brows);
    freeMatrix(resultMatrix, arows);

    return 0;
}