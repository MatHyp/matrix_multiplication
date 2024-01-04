#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void readMatrixFromFile(const char *filename, int matrix[MAX_ROWS][MAX_COLS], int *rows, int *cols) {
    FILE *file = fopen(filename, "r");

    // Cannot open a file
    if (file == NULL) {
        fprintf(stderr, "Nie można otworzyć pliku %s.\n", filename);
        exit(1);
    }

    fscanf(file, "%d %d", rows, cols);

    // Check that 
    if (*rows > MAX_ROWS || *cols > MAX_COLS) {
        fprintf(stderr, "Zbyt duża macierz. Zmień rozmiary MAX_ROWS lub MAX_COLS.\n");
        fclose(file);
        exit(1);
    }

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    
    fclose(file);
}

void printMatrix(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void matrixMultiplication(){}

int main() {
    int matrixA[MAX_ROWS][MAX_COLS], matrixB[MAX_ROWS][MAX_COLS], resultMatrix[MAX_ROWS][MAX_COLS];
    int arows, acolumns, brows, bcolumns;
    int i, j, k;
    int sum = 0;

    readMatrixFromFile("matrixA.txt", matrixA, &arows, &acolumns);
    readMatrixFromFile("matrixB.txt", matrixB, &brows, &bcolumns);

    printf("Matrix A:\n");
    printMatrix(matrixA, arows, acolumns);

    printf("\nMatrix B:\n");
    printMatrix(matrixB, brows, bcolumns);

    // Matrix multiplation

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
    printMatrix(resultMatrix,arows,bcolumns);

    return 0;
}