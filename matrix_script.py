def print_matrix(matrix):
    """Prints the given matrix."""
    for row in matrix:
        print(row)

def remove_row(matrix, row):
    """Removes the specified row from the matrix."""
    return [matrix[i] for i in range(len(matrix)) if i != row]

def remove_col(matrix, col):
    """Removes the specified column from the matrix."""
    return [[row[j] for j in range(len(row)) if j != col] for row in matrix]

def splice_matrix(matrix, row, col):
    """Removes the specified row and column from the matrix."""
    return remove_col(remove_row(matrix, row), col)

def determinant(matrix):
    """Calculates the determinant of the given matrix."""
    if len(matrix) == 1:
        # Base case for 1x1 matrix
        return matrix[0][0]
    elif len(matrix) == 2:
        # Base case for 2x2 matrix
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]

    det = 0
    for i in range(len(matrix)):
        cofactor = ((-1) ** i) * matrix[0][i] * determinant(splice_matrix(matrix, 0, i))
        det += cofactor
    return det

def cofactor(matrix):
    """Calculates the cofactor matrix of the given matrix."""
    rows = len(matrix)
    cols = len(matrix[0])
    cofactor_matrix = [[0] * cols for _ in range(rows)] 

    for i in range(rows):
        for j in range(cols):
            sign = ((-1) ** (i + j))
            cofactor_matrix[i][j] = sign * determinant(splice_matrix(matrix, i, j))

    return cofactor_matrix

# Test cases
matrix = [[1]]
matrix2 = [
    [1, 2],
    [3, 4]
]

matrix3 = [
    [6, 1, 1],
    [4, -2, 5],
    [2, 8, 7]
]

print("Original Matrix:")
print_matrix(matrix2)
print("\nDeterminant of matrix2:", determinant(matrix2))

print("\nSpliced Matrix (Remove row 0, col 1):")
spliced = splice_matrix(matrix2, 0, 1)
print_matrix(spliced)

print("\nDeterminant of matrix3:", determinant(matrix3))

print("\nCofactor Matrix of matrix3:")
cofactor_matrix = cofactor(matrix3)
print_matrix(cofactor_matrix)