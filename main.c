#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

int main() {
    // Create two 3x3 matrices
    MATRIX *mat1 = Create_matrix(3, 3);
    MATRIX *mat2 = Create_matrix(3, 3);

    MATRIX *mat3 = Create_matrix(2, 2);
    // Initialize matrix1 with some values
    mat1->Matrix[0][0] = 1;
    mat1->Matrix[0][1] = 2;
    mat1->Matrix[0][2] = 3;
    mat1->Matrix[1][0] = 0;
    mat1->Matrix[1][1] = 1;
    mat1->Matrix[1][2] = 4;
    mat1->Matrix[2][0] = 5;
    mat1->Matrix[2][1] = 6;
    mat1->Matrix[2][2] = 0;

    // Initialize matrix2 with some values
    mat2->Matrix[0][0] = 1;
    mat2->Matrix[0][1] = 0;
    mat2->Matrix[0][2] = 5;
    mat2->Matrix[1][0] = 2;
    mat2->Matrix[1][1] = 1;
    mat2->Matrix[1][2] = 0;
    mat2->Matrix[2][0] = 3;
    mat2->Matrix[2][1] = 4;
    mat2->Matrix[2][2] = 1;

    printf("\nMatrix 1:\n");
    Print_matrix(mat1);

    printf("\nMatrix 2:\n");
    Print_matrix(mat2);

    // Transpose of matrix1
    MATRIX *mat1_transposed = Transpose_matrix(mat1);
    printf("\nTranspose of Matrix 1:\n");
    Print_matrix(mat1_transposed);

    // Multiply transposed matrix1 with matrix2
    MATRIX *result = Multiply_matrix(mat1_transposed, mat2);
    if (result != NULL) {
        printf("\nResult of Transpose(Matrix1) * Matrix2:\n");
        Print_matrix(result);
    } else {
        printf("Matrix multiplication failed.\n");
        return 1; // Exit with an error code
    }

    // Scalar multiplication of result by 2.0
    Scalar_mulitplication(result, 2.0);
    printf("\nResult after Scalar Multiplication:\n");
    Print_matrix(result);

    // Calculate the inverse of the result
    MATRIX *inverse = Inverse_matrix(result);
    if (inverse != NULL) {
        printf("\nInverse of Result:\n");
        Print_matrix(inverse);
    } else {
        printf("Matrix is singular. Inverse does not exist.\n");
        return 1; // Exit with an error code
    }

    // Free allocated memory
    free(mat1);
    free(mat2);
    free(mat1_transposed);
    free(result);
    free(inverse); 

    return 0;
}