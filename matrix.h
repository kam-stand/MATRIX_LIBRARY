/**
 * @file matrix.h
 * @brief This file contains the definition of the MATRIX structure and the function prototypes for the matrix operations.
 *
 */

#ifndef MATRIX_H
#define MATRIX_H

/**
 *
 * @brief The MATRIX structure represents a matrix.
 *
 * The MATRIX structure contains the number of rows and columns in the matrix, and a 2D array to store the matrix elements.
 *
 */

struct MATRIX
{
    int rows;
    int columns;
    double **Matrix;
};

typedef struct MATRIX MATRIX;

/**
 * @brief Creates a matrix with the specified number of rows and columns.
 *
 * This function creates a matrix with the specified number of rows and columns, and initializes all elements to zero.
 * @return A pointer to the MATRIX structure representing the created matrix.
 */

MATRIX *Create_matrix(int rows, int cols);

/**
 * @brief Copies the given matrix.
 *
 * This function takes a matrix as input and creates a copy of it.
 *
 * @param mat A pointer to the MATRIX structure to be copied.
 * @return A pointer to the MATRIX structure representing the copied matrix.
 */
MATRIX *Copy_matrix(MATRIX *mat);

/**
 * @brief Adds mulitplies matrices.
 *
 * This function takes two matrices as input and returns a new matrix that is the multiplication of the two input matrices.
 *
 * @param mat1 A pointer to the first MATRIX .
 * @param mat2 A pointer to the second MATRIX structure to be multiplied with first.
 * @return A pointer to the MATRIX structure representing the sum of the two input matrices.
 */

MATRIX *Multiply_matrix(MATRIX *mat1, MATRIX *mat2);

MATRIX *Transpose_matrix(MATRIX *mat);
/**
 * @brief Removes a specified row from the given matrix.
 *
 * This function takes a matrix and a row index, and removes the row at the specified index from the matrix.
 *
 * @param mat A pointer to the MATRIX structure from which the row will be removed.
 * @param row The index of the row to be removed.
 * @return A pointer to the MATRIX structure after the row has been removed.
 */
MATRIX *Remove_row(MATRIX *mat, int row);
/**
 * @brief Removes a specified column from the given matrix.
 *
 * This function takes a matrix and a column index, and removes the column at the specified index from the matrix.
 *
 * @param mat A pointer to the MATRIX structure from which the column will be removed.
 * @param col The index of the column to be removed.
 * @return A pointer to the MATRIX structure after the column has been removed.
 *
 */
MATRIX *Remove_column(MATRIX *mat, int col);

/**
 * @brief Splices a matrix.
 *
 * This function takes a matrix and a row and column index, and returns a new matrix that is the result of removing the specified row and column from the input matrix.
 *
 * @param mat A pointer to the MATRIX structure to be spliced.
 * @param row The index of the row to be removed.
 * @param col The index of the column to be removed.
 * @return A pointer to the MATRIX structure representing the spliced matrix.
 */

MATRIX *splice_matrix(MATRIX *mat, int row, int col);
/**
 * @brief Calculates the determinant of a matrix.
 *
 * This function takes a matrix as input and calculates the determinant of the matrix.
 *
 * @param mat A pointer to the MATRIX structure for which the determinant will be calculated.
 * @return The determinant of the matrix.
 */
double determinant(MATRIX *mat);
/**
 * @brief Calculates the cofactor matrix of a matrix.
 *
 * This function takes a matrix as input and calculates the cofactor matrix of the matrix.
 *
 * @param mat A pointer to the MATRIX structure for which the cofactor matrix will be calculated.
 * @return A pointer to the MATRIX structure representing the cofactor matrix.
 */
MATRIX *Cofactor_matrix(MATRIX *mat);
/**
 * @brief Calculates the inverse of a matrix.
 *
 * This function takes a matrix as input and calculates the inverse of the matrix.
 *
 * @param mat A pointer to the MATRIX structure for which the inverse will be calculated.
 * @return A pointer to the MATRIX structure representing the inverse of the matrix.
 */
MATRIX *Inverse_matrix(MATRIX *mat);
/**
 * @brief Calculates the adjoint matrix of a matrix.
 *
 * This function takes a matrix as input and calculates the adjoint matrix of the matrix.
 *
 * @param mat A pointer to the MATRIX structure for which the adjoint matrix will be calculated.
 * @return A pointer to the MATRIX structure representing the adjoint matrix.
 */
MATRIX *Adjoint_matrix(MATRIX *mat);
/**
 * @brief Scales a matrix by a scalar value.
 *
 * This function takes a matrix and a scalar value as input, and scales the matrix by the scalar value.
 *
 * @param mat A pointer to the MATRIX structure to be scaled.
 * @param scalar The scalar value by which the matrix will be scaled.
 */
void Scalar_mulitplication(MATRIX *mat, double scalar);
/**
 * @brief Prints the matrix.
 *
 * This function takes a matrix as input and prints the matrix to the console.
 *
 * @param mat A pointer to the MATRIX structure to be printed.
 */
void Print_matrix(MATRIX *mat);

#endif // MATRIX_H