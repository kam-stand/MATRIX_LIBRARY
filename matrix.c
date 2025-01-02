
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"


MATRIX* Create_matrix(int rows, int cols) {
    MATRIX* mat = (MATRIX*)malloc(sizeof(MATRIX));
    if (mat == NULL) {
        fprintf(stderr, "Memory allocation failed for matrix.\n");
        exit(1); 
    }

    mat->rows = rows;
    mat->columns = cols;

    mat->Matrix = (double**)malloc(rows * sizeof(double*));
    if (mat->Matrix == NULL) {
        fprintf(stderr, "Memory allocation failed for matrix rows.\n");
        free(mat);
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        mat->Matrix[i] = (double*)malloc(cols * sizeof(double));
        if (mat->Matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for matrix column %d.\n", i);
            for (int j = 0; j < i; j++) {
                free(mat->Matrix[j]);
            }
            free(mat->Matrix);
            free(mat);
            exit(1);
        }
    }

    return mat;
}

MATRIX* Copy_matrix(MATRIX *mat){

    MATRIX* ret = Create_matrix(mat->rows, mat->columns);
    for(int i =0; i<mat->rows; i++){
        for(int j = 0; j<mat->columns; j++){
            ret->Matrix[i][j] = mat->Matrix[i][j];
        }
    }

    return ret;

}
void Print_matrix(MATRIX* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->columns; j++) {
            printf("%lf ", mat->Matrix[i][j]);
        }
        printf("\n");
    }
}

void Scalar_mulitplication(MATRIX *mat, double scalar) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->columns; j++) {
            mat->Matrix[i][j] *= scalar; 
        }
    }
    Print_matrix(mat);
    return;
}

MATRIX* Multiply_matrix(MATRIX* mat1, MATRIX* mat2) {
    if (mat1->columns != mat2->rows) {
        printf("Cannot perform matrix multiplication: Incompatible dimensions\n");
        return NULL;
    }

    MATRIX* ret = Create_matrix(mat1->rows, mat2->columns);

    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat2->columns; j++) {
            double sum = 0.0;
            for (int k = 0; k < mat1->columns; k++) {
                sum += mat1->Matrix[i][k] * mat2->Matrix[k][j];
            }
            ret->Matrix[i][j] = sum;
        }
    }

    return ret;
}

MATRIX* Transpose_matrix(MATRIX* mat) {
    if (mat == NULL) {
        printf("Error: Cannot transpose a NULL matrix.\n");
        return NULL;
    }

    MATRIX* transposed = Create_matrix(mat->columns, mat->rows);

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->columns; j++) {
            transposed->Matrix[j][i] = mat->Matrix[i][j];
        }
    }

    return transposed;
}

MATRIX* Remove_row(MATRIX* mat, int row) {
    if (row < 0 || row >= mat->rows) {
        printf("Invalid row index for removal.\n");
        return NULL;
    }

    MATRIX* ret = Create_matrix(mat->rows - 1, mat->columns);

    int new_row = 0;
    for (int i = 0; i < mat->rows; i++) {
        if (i == row) {
            continue;
        }

        for (int j = 0; j < mat->columns; j++) {
            ret->Matrix[new_row][j] = mat->Matrix[i][j];
        }
        new_row++;
    }

    return ret;
}

MATRIX* Remove_column(MATRIX* mat, int col) {
    if (col < 0 || col >= mat->columns) {
        printf("Invalid column index for removal.\n");
        return NULL;
    }

    MATRIX* ret = Create_matrix(mat->rows, mat->columns - 1);

    for (int i = 0; i < mat->rows; i++) {
        int new_col = 0;
        for (int j = 0; j < mat->columns; j++) {
            if (j == col) {
                continue;
            }
            ret->Matrix[i][new_col] = mat->Matrix[i][j];
            new_col++;
        }
    }

    return ret;
}

MATRIX* splice_matrix(MATRIX* mat, int row, int col) {
    if (!mat) {
        return NULL;
    }

    MATRIX* ret1 = Remove_row(mat, row);
    if (!ret1) {
        return NULL;
    }

    MATRIX* ret2 = Remove_column(ret1, col);
    if (!ret2) {
        free(ret1);
        return NULL;
    }

    return ret2;
}

double determinant(MATRIX* mat) {
    if (mat->rows == 1) {
        return mat->Matrix[0][0];
    }
    if (mat->rows == 2) {
        return mat->Matrix[0][0] * mat->Matrix[1][1] - mat->Matrix[0][1] * mat->Matrix[1][0];
    }

    double det = 0;
    for (int i = 0; i < mat->rows; i++) {
        MATRIX* minor = splice_matrix(mat, 0, i);
        double cofactor = pow(-1, i) * mat->Matrix[0][i] * determinant(minor);
        det += cofactor;
        free(minor); // Free the minor matrix to avoid memory leaks
    }

    return det;
}

MATRIX* Cofactor_matrix(MATRIX *mat){
    MATRIX *ret = Create_matrix(mat->rows, mat->columns);

    for(int i = 0; i < mat->rows; i++){
        for(int j = 0; j < mat->columns; j++){
            double sign = pow(-1, (double)(i+j));
            ret->Matrix[i][j] = sign * determinant(splice_matrix(mat, i, j)); 
        }
    }

    return ret;
}

MATRIX* Adjoint_matrix(MATRIX *mat){
    MATRIX* adj = Transpose_matrix(Cofactor_matrix(mat));
    return adj;
}

MATRIX* Inverse_matrix(MATRIX *mat) {
    MATRIX *ret = Copy_matrix(mat); // copy the matrix

    double det = determinant(mat); // find the determinant

    // Check for singularity
    if (fabs(det) < 1e-10) { // Check if determinant is approximately zero
        printf("Matrix is singular. Inverse does not exist.\n");
        return NULL;
    }

    ret = Adjoint_matrix(ret); // find the adjoint

    Scalar_mulitplication(ret, (double)(1/det));

    return ret;
}