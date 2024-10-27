/**
 * @file    MatrixMath.c
 * @author  Nicolas Jorgensen (njorgen1@ucsc.edu)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MatrixMath.h"

void MatrixPrint(float mat[3][3])
{
    printf(" _____________________________\n");
    for(int i = 0;i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            printf("|%9.4f", mat[i][j]);
        }
        printf("|\n _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    }
    printf("\n");
}

/**
 * MatrixEquals checks if the two matrix arguments are equal (to within
 * FP_DELTA).
 * 
 * @param: mat1, pointer to a 3x3 float array
 * @param: mat2, pointer to a 3x3 float array
 *
 * @return: TRUE if and only if every element of mat1 is within FP_DELTA of 
 *          the corresponding element of mat2,  otherwise return FALSE.
 *
 * Neither mat1 nor mat2 is modified by this function.
 */
int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
     for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            if(fabs((mat1[i][j] - mat2[i][j])) > FP_DELTA) {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * MatrixAdd performs an element-wise matrix addition operation on two 3x3 
 * matrices and "returns" the result by modifying the third argument.
 *
 * @param: mat1, pointer to a summand 3x3 matrix
 * @param: mat2, pointer to a summand 3x3 matrix
 * @param: result, pointer to a 3x3 matrix that is modified to contain the 
 *         sum of mat1 and mat2.
 *
 * @return:  None
 *
 * mat1 and mat2 are not modified by this function. result is modified by this
 * function.
 */
void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    for(int i = 0;i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

/**
 * MatrixMultiply performs a matrix-matrix multiplication operation on two 3x3
 * matrices and "returns" the result by modifying the third argument.
 *
 * @param: mat1, pointer to left factor 3x3 matrix
 * @param: mat2, pointer to right factor 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain the matrix 
 *         product of mat1 and mat2.*
 *
 * @return: none
 *
 * mat1 and mat2 are not modified by this function.  result is modified by 
 * this function.
 */
void MatrixMultiply(float A[3][3], float B[3][3], float res[3][3]) 
{
    for(int i = 0;i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            res[i][j] = 0.0; //making sure there's no funny business
            //A shares index i with res, B shares index j
            //k will iterate over the columns of A and rows of B
            for(int k = 0; k < DIM; k++) {
                res[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


/*******************************************************************************
 * Matrix - Scalar Operations
 ******************************************************************************/

/**
 * MatrixScalarAdd performs the addition of a matrix and a scalar.  Each element
 * of the matrix is increased by x. The result is "returned"by modifying the 
 * third argument.
 *
 * @param: x, a scalar float
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 *
 * @return: none
 *
 * x and mat are not modified by this function.  result is modified by this 
 * function.
 */
void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    for(int i = 0;i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            result[i][j] = mat[i][j] + x;
        }
    }
}

/**
 * MatrixScalarMultiply performs the multiplication of a matrix and a scalar.
 * Each element of the matrix is multiplied x.
 * The result is "returned"by modifying the third argument.
 *
 * @param: x, a scalar float
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 *
 * @return: none
 *
 * x and mat are not modified by this function.  result is modified by this 
 * function.
 */
void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    for(int i = 0;i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            result[i][j] = mat[i][j] * x;
        }
    }
}


/*******************************************************************************
 * Unary Matrix Operations
 ******************************************************************************/

/**
 * MatrixTrace calculates the trace of a 3x3 matrix.
 *
 * @param: mat, a pointer to a 3x3 matrix
 *
 * @return: the trace of mat
 */
float MatrixTrace(float mat[3][3]) 
{
    return mat[0][0] + mat[1][1] + mat[2][2];
}

/**
 * MatrixTranspose calculates the transpose of a matrix and "returns" the
 * result through the second argument.
 *
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to transpose of mat
 *
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixTranspose(float mat[3][3], float result[3][3]) 
{
    for(int i = 0;i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            result[i][j] = mat[j][i];
        }
    }
}

/**
 * MatrixSubmatrix finds a submatrix of a 3x3 matrix that is 
 * formed by removing the i-th row and the j-th column.  The 
 * submatrix is "returned" by modifying the final argument.
 * 
 * @param: i, a row of the matrix, INDEXING FROM 0
 * @param: j, a column of the matrix, INDEXING FROM 0
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 2x2 matrix
 *
 * @return: none
 * 
 * mat is not modified by this function.  Result is modified by this function.
 */
void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2])
{
    int row_2x2 = 0;
    for(int m = 0; m < DIM; m++) {
       
        int col_2x2 = 0;

        if(m == i) {
            continue; //skips encoding row i into result
        }

        for(int n = 0; n < DIM; n++) {
           
            if(n == j) {
                continue; //skips encoding column j into result
            }

            result[row_2x2][col_2x2] = mat[m][n];

            col_2x2++;//tracking the current col of smaller matrix
        }

        row_2x2++; //tracking the current row of smaller matrix
    }
}

/**
 * MatrixDeterminant2x2 calculates the determinant of a 2x2 matrix 
 * and returns the value as a float.
 *
 * @param: mat, a pointer to a 2x2 matrix
 *
 * @return: the determinant of mat
 *
 * mat is not modified by this function.
 * */
float MatrixDeterminant2x2(float mat[2][2])
{
    return (mat[0][0]*mat[1][1]) - (mat[0][1]*mat[1][0]);
}

/**
 * MatrixDeterminant calculates the determinant of a 3x3 matrix 
 * and returns the value as a float.
 *
 * @param: mat, a pointer to a 3x3 matrix
 *
 * @return: the determinant of mat
 *
 * mat is not modified by this function.
 * */
float MatrixDeterminant(float mat[3][3]) 
{   
    //submatrices
    float sub_i[2][2],sub_j[2][2],sub_k[2][2];
    //first row of function arg
    float i = mat[0][0], j = mat[0][1], k = mat[0][2];

    MatrixSubmatrix(0, 0, mat, sub_i);
    MatrixSubmatrix(0, 1, mat, sub_j);
    MatrixSubmatrix(0, 2, mat, sub_k);

    i = i*MatrixDeterminant2x2(sub_i);
    j = j*MatrixDeterminant2x2(sub_j);
    k = k*MatrixDeterminant2x2(sub_k);

    return (i - j + k);
}


/* MatrixInverse calculates the inverse of a matrix and
 * "returns" the result by modifying the second argument.
 *
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 3x3 matrix that is modified to contain the 
 *         inverse of mat
 * @return: none
 *
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixInverse(float mat[3][3], float result[3][3])
{
    float minor[3][3], minor_T[3][3], temp_mat[2][2], inv_det, det;

    //calculating the determinant of mat
    det = (MatrixDeterminant(mat));
    //divide by zero handeling
    if(det == 0) {
        return;
    }
    inv_det = 1 / det;
    
    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            
            MatrixSubmatrix(i, j, mat, temp_mat);
            
            //satisfying the weird alternative neg/pos matrix minor property
            if(((i + j) % 2) != 0) {
                minor[i][j] = (-1) * MatrixDeterminant2x2(temp_mat);
            }
            else {
                minor[i][j] = MatrixDeterminant2x2(temp_mat);
            }
        }
    }
    //transposing minor matrix
    MatrixTranspose(minor, minor_T);

    //multipying transposed minor by 1 / determinant
    MatrixScalarMultiply(inv_det, minor_T, result);

}
