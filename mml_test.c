/**
 * @file    mml_test.c
 * @author  Nicolas Jorgensen (njorgen1@ucsc.edu)
 */
// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// User libraries:
#include "MatrixMath.h"

#define TOTAL_TESTS 27

// Module-level variables:

int main()
{
    float results_track = 0.0;
    int working_funcs = 0;
    float print_test[3][3] = {
            {55.55, 999.0, 12.21},
            {-1.5, -900.50, 44.421},
            {-0.1, 5.0, 0.5}
        };

    printf(
        "Beginning CRUZID's mml test harness, compiled on %s %s\n",
        __DATE__,
        __TIME__
    );
    
    //MatrixEquals unit test
    {    
        int passed = 0;
        // Test case 1: Two identical matrices
        float mat1[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        float mat2[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        
        passed += MatrixEquals(mat1, mat2);

        // Test case 2: Two matrices that are equal within tolerance (FP_DELTA)
        float mat3[3][3] = {
            {1.0, 2.0, 3.0},
            {4.00009, 5.0, 6.0},
            {7.0, 8.0, 9.00009}
        };
        float mat4[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };

        passed += MatrixEquals(mat3, mat4);

        // Test case 3: Matrices with one element different (outside of FP_DELTA)
        float mat5[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0002}, // Slightly larger than mat4
            {7.0, 8.0, 9.0}
        };
        float mat6[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0000}, // Slightly smaller than mat3
            {7.0, 8.0, 9.0}
        };

        if(!MatrixEquals(mat5, mat6)) { //if MatrixEquals returns 0
            passed++;
        }
        
        // Test case 3: Matrices with multiple different elements
        float mat7[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.1, 8.0, 9.0}
        };
        float mat8[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
      
        if(!MatrixEquals(mat7, mat8)) { //if MatrixEquals returns 0
            passed++;
        }
        
        printf("PASSED (%d/4): MatrixEquals()\n", passed);
        
        results_track += passed;
       
        if(passed == 4) {
            working_funcs++;
        }
    }

    //MatrixScalarAdd unit test
    {
        int passed = 0;

        // Test case 1: Add scalar 0 (result should equal the original matrix)
        float mat1[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        float expected1[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        float result1[3][3];
        MatrixScalarAdd(0, mat1, result1);
        passed += MatrixEquals(expected1, result1);

        // Test case 2
        float expected2[3][3] = {
            {2.0, 3.0, 4.0},
            {5.0, 6.0, 7.0},
            {8.0, 9.0, 10.0}
        };
        float result2[3][3];
        MatrixScalarAdd(1, mat1, result2);
        passed += MatrixEquals(expected2, result2);

        // Test case 3
        float expected3[3][3] = {
            {-1.0, 0.0, 1.0},
            {2.0, 3.0, 4.0},
            {5.0, 6.0, 7.0}
        };
        float result3[3][3];
        MatrixScalarAdd(-2, mat1, result3);
        passed += MatrixEquals(expected3, result3);

        // Test case 4
        float expected4[3][3] = {
            {1.5, 2.5, 3.5},
            {4.5, 5.5, 6.5},
            {7.5, 8.5, 9.5}
        };
        float result4[3][3];
        MatrixScalarAdd(0.5, mat1, result4);
        passed += MatrixEquals(expected4, result4);

        printf("PASSED (%d/4): MatrixScalarAdd()\n", passed);
        
        results_track += passed;

        if (passed == 4) {
            working_funcs++;
        }
    }

    //MatrixScalarMultiply test
    {
        int passed = 0;

        // Test case 1
        float mat1[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        float expected1[3][3] = {
            {-1.0, -2.0, -3.0},
            {-4.0, -5.0, -6.0},
            {-7.0, -8.0, -9.0}
        };
        float result1[3][3];
        MatrixScalarMultiply(-1, mat1, result1);
        passed += MatrixEquals(expected1, result1);

        // Test case 2
        float expected2[3][3] = {
            {2.0, 4.0, 6.0},
            {8.0, 10.0, 12.0},
            {14.0, 16.0, 18.0}
        };
        float result2[3][3];
        MatrixScalarMultiply(2, mat1, result2);
        passed += MatrixEquals(expected2, result2);

        printf("PASSED (%d/2): MatrixScalarMultiply()\n", passed);
        
        results_track += passed;

        if (passed == 2) {
            working_funcs++;
        }
    }
    
    //MatrixAdd test
    {
        int passed = 0;

        // Test case 1: Add two matrices with integers
        float mat1[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        float mat2[3][3] = {
            {9, 8, 7},
            {6, 5, 4},
            {3, 2, 1}
        };
        float expected1[3][3] = {
            {10, 10, 10},
            {10, 10, 10},
            {10, 10, 10}
        };
        float result1[3][3] = {{},{},{}};
        MatrixAdd(mat1, mat2, result1);
        passed += MatrixEquals(expected1, result1);

        // Test case 2: Add two matrices with decimals
        float mat3[3][3] = {
            {1.5, 2.25, 3.75},
            {4.5, 5.125, 6.25},
            {7.75, 8.875, 9.125}
        };
        float mat4[3][3] = {
            {0.5, 0.75, 1.25},
            {1.5, 2.875, 3.75},
            {4.25, 5.125, 6.875}
        };
        float expected2[3][3] = {
            {2.0, 3.0, 5.0},
            {6.0, 8.0, 10.0},
            {12.0, 14.0, 16.0}
        };
        float result2[3][3] = {{},{},{}};
        MatrixAdd(mat3, mat4, result2);
        passed += MatrixEquals(expected2, result2);

        // Test case 3: Add two matrices with negative values
        float mat5[3][3] = {
            {-1, -2, -3},
            {-4, -5, -6},
            {-7, -8, -9}
        };
        float mat6[3][3] = {
            {9, 8, 7},
            {6, 5, 4},
            {3, 2, 1}
        };
        float expected3[3][3] = {
            {8, 6, 4},
            {2, 0, -2},
            {-4, -6, -8}
        };
        float result3[3][3] = {{},{},{}};
        MatrixAdd(mat5, mat6, result3);
        passed += MatrixEquals(expected3, result3);

        printf("PASSED (%d/3): MatrixAdd()\n", passed);
        
        results_track += passed;

        if (passed == 3) {
            working_funcs++;
        }
    }
    
    //MatrixMultiply test
    {
        int passed = 0;
        float result[3][3] = {{},{},{}};

        // Test case 1: Multiplying with identity matrix
        float mat1[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        float mat2[3][3] = {
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0}
        };
        MatrixMultiply(mat1, mat2, result);
        float expected1[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        passed += MatrixEquals(result, expected1);

        // Test case 2: Multiplying with a zero matrix
        float mat3[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        float mat4[3][3] = {
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}
        };
        MatrixMultiply(mat3, mat4, result);
        float expected2[3][3] = {
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}
        };
        passed += MatrixEquals(result, expected2);

        // Test case 3: Multiplying two non-identity matrices
        float mat5[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        float mat6[3][3] = {
            {1.0, 2.0, 3.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0}
        };
        MatrixMultiply(mat5, mat6, result);
        float expected3[3][3] = {
            {1.0*1.0 + 2.0*0.0 + 3.0*0.0,
             1.0*2.0 + 2.0*1.0 + 3.0*0.0, 
             1.0*3.0 + 2.0*0.0 + 3.0*1.0},
            {4.0*1.0 + 5.0*0.0 + 6.0*0.0,
             4.0*2.0 + 5.0*1.0 + 6.0*0.0, 
             4.0*3.0 + 5.0*0.0 + 6.0*1.0},
            {7.0*1.0 + 8.0*0.0 + 9.0*0.0, 
             7.0*2.0 + 8.0*1.0 + 9.0*0.0, 
             7.0*3.0 + 8.0*0.0 + 9.0*1.0}
        };

        passed += MatrixEquals(result, expected3);

        printf("PASSED (%d/3): MatrixMultiply()\n", passed);

        results_track += passed;
        
        if (passed == 3) {
            working_funcs++;
        }
    }

    //MatrixTrace unit test
    {
        int passed = 0;
        // Test case 1: Standard 3x3 matrix
        float mat1[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        
        float expected1 = 15.0;
        if (MatrixTrace(mat1) == expected1) {
            passed++;
        }

        // Test case 2: Matrix with negative numbers
        float mat2[3][3] = {
            {-1.0, -2.0, -3.0},
            {4.0, -5.0, 6.0},
            {7.0, 8.0, -9.0}
        };
        
        float expected2 = -15.0;
        if (MatrixTrace(mat2) == expected2) {
            passed++;
        }

        printf("PASSED (%d/2): MatrixTrace()\n", passed);
        
        results_track += passed;

        if (passed == 2) {
            working_funcs++;
        }
    }
    
    //Transpose unit test
    {
        int passed = 0;

        // Test case 1: Standard matrix
        float mat1[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.99}
        };
        float expected1[3][3] = {
            {1.0, 4.0, 7.0},
            {2.0, 5.0, 8.0},
            {3.0, 6.0, 9.99}
        };
        float result1[3][3] = {{}, {}, {}};

        MatrixTranspose(mat1, result1);
        if (MatrixEquals(result1, expected1)) {
            passed++;
        }

        // Test case 2: Matrix with negative numbers
        float mat2[3][3] = {
            {-1.0, -2.05, -3.0},
            {4.0, 5.0, 6.0},
            {7.0, -8.0, 9.0}
        };
        float expected2[3][3] = {
            {-1.0, 4.0, 7.0},
            {-2.05, 5.0, -8.0},
            {-3.0, 6.0, 9.0}
        };
        float result2[3][3] = {{}, {}, {}}; 

        MatrixTranspose(mat2, result2);
        if (MatrixEquals(result2, expected2)) {
            passed++;
        }

        printf("PASSED (%d/2): MatrixTranspose()\n", passed);
        
        results_track += passed;

        if (passed == 2) {
            working_funcs++;
        }
    }
   
    //Submatrix test harness
    {
        int passed = 0;
        float result_2x2[2][2] = {{}, {}};
        float result_3x3[3][3] = {{}, {}, {}};
        
        // Test case 1: Removing the 0th row and 0th column
        float mat1[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        float expected1[3][3] = {
            {5.0, 6.0, 0.0},
            {8.0, 9.0, 0.0},
            {0.0, 0.0, 0.0}  // Third row/column set to zero
        };
      

        MatrixSubmatrix(0, 0, mat1, result_2x2);

        // Copy the result into the 3x3 matrix
        result_3x3[0][0] = result_2x2[0][0];
        result_3x3[0][1] = result_2x2[0][1];
        result_3x3[1][0] = result_2x2[1][0];
        result_3x3[1][1] = result_2x2[1][1];
        
        //using MatrixEquals to compare
        passed += MatrixEquals(result_3x3, expected1);

        // Test case 2: Removing the 1st row and 1st column
        float expected2[3][3] = {
            {1.0, 3.0, 0.0},
            {7.0, 9.0, 0.0},
            {0.0, 0.0, 0.0}  // Third row/column set to zero
        };
        MatrixSubmatrix(1, 1, mat1, result_2x2);

        // Copy the result into the 3x3 matrix
        result_3x3[0][0] = result_2x2[0][0];
        result_3x3[0][1] = result_2x2[0][1];
        result_3x3[1][0] = result_2x2[1][0];
        result_3x3[1][1] = result_2x2[1][1];

        // Compare the result matrix with the expected matrix
        passed += MatrixEquals(result_3x3, expected2);

        // Test case 3: Removing the 2nd row and 2nd column
        float expected3[3][3] = {
            {1.0, 2.0, 0.0},
            {4.0, 5.0, 0.0},
            {0.0, 0.0, 0.0}  // Third row/column set to zero
        };

        MatrixSubmatrix(2, 2, mat1, result_2x2);

        // Copy the result into the 3x3 matrix
        result_3x3[0][0] = result_2x2[0][0];
        result_3x3[0][1] = result_2x2[0][1];
        result_3x3[1][0] = result_2x2[1][0];
        result_3x3[1][1] = result_2x2[1][1];

        // Compare the result matrix with the expected matrix
        passed += MatrixEquals(result_3x3, expected3);

        printf("PASSED (%d/3): MatrixSubmatrix()\n", passed);
        
        results_track += passed;
        if (passed == 3) {
            working_funcs++;
        }
    }

    //Determinant test harness
    {
        int passed = 0;
        float diff;

        // Test case 1: Matrix with positive integers
        float mat1[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        
        float expected1 = 0.0; // Determinant of mat1 should be 0

        float result1 = MatrixDeterminant(mat1);
        
        //using fabs equiv without math.h
        diff = result1 - expected1;
        if(diff < 0) {
            diff = -diff;
        }

        if (diff < FP_DELTA) { // Check if result is within tolerance
            passed++;
        }

        // Test case 2: Matrix with a mix of positive, negative, and decimal values
        float mat2[3][3] = {
            {3.5, 2.2, -4.1},
            {0.0, 1.1, 0.5},
            {2.0, -3.3, 1.0}
        };

        float expected2 = 20.845; // Pre-calculated determinant of mat2

        float result2 = MatrixDeterminant(mat2);

        //fabs again
        diff = result2 - expected2;
        if(diff < 0) {
            diff = -diff;
        }

        if (diff < FP_DELTA) { // Check if result is within tolerance
            passed++;
        }

        printf("PASSED (%d/2): MatrixDeterminant()\n", passed);

        results_track += passed;
        if (passed == 2) {
            working_funcs++;
        }
    }

    //Inverse test harness
    {
        int passed = 0;

        //Test 1
        float mat1[3][3] = {
            {2.0, 1.0, 1.0},
            {1.0, 3.0, 2.0},
            {1.0, 0.0, 0.5}
        };

        // Result matrix for storing the inverse
        float result[3][3] = {{},{},{}};
        
        // Identity matrix for comparison
        float identity[3][3] = {
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0}
        };

        // Calculate the inverse of the original matrix
        MatrixInverse(mat1, result);
        
        // Multiply the original matrix with its inverse
        float product[3][3] = {{},{},{}};
        MatrixMultiply(mat1, result, product);
        
        // Check if the product is the identity matrix
        passed += MatrixEquals(product, identity);
        
        //Test 2
        float mat2[3][3] = {
            {55.55, 999.0, 12.21},
            {-1.5, -900.50, 44.421},
            {-0.1, 5.0, 0.5}
        };
 
        MatrixInverse(mat2, result);
        
        MatrixMultiply(mat2, result, product);
        
        passed += MatrixEquals(product, identity);

        printf("PASSED (%d/2): MatrixInverse()\n", passed);

        results_track += passed;
        if (passed == 2) {
            working_funcs++;
        }
    }
    printf("- - - - - - - - - - - - - - - - - \n");
    printf("%d out of 10 functions passed (%.1lf%%).\n", working_funcs, 100* results_track/TOTAL_TESTS);
  

    printf("\nOutput of MatrixPrint():\n");
    MatrixPrint(print_test);
    printf("\nExpected output of MatrixPrint():\n");
    printf(" _____________________________\n"); 
    printf("|  55.5500| 999.0000|  12.2100|\n");
    printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("|  -1.5000|-900.5000|  44.4210|\n");
    printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("|  -0.1000|   5.0000|   0.5000|\n");
    printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");



    // Add more tests here!
    while (1);
}

