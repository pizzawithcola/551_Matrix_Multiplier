#include "multiply.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "freeAndPrint.h"

void checkMemory(matrix_t * result);
void checkMultiplyInvaild(matrix_t * left, matrix_t * right);
matrix_t * mallocResultMatrix(matrix_t * left, matrix_t * right);
void multiplyMatrix(matrix_t * result, matrix_t * left, matrix_t * right);

//this functin check if multiplication can be performed 
void checkMultiplyInvaild(matrix_t * left, matrix_t * right){
    //if the number of columns of left matrix is not equal to the number of rows of right matrix, they cannot be multiplied
    if (left->columns != right->rows) {
        perror("Cannot multiply the input matrices");
        exit(EXIT_FAILURE);
    }
}

//this function malloc space for the result
matrix_t * mallocResultMatrix(matrix_t * left, matrix_t * right) {
    matrix_t * result = malloc(sizeof(*result));
    result->rows = left->rows;
    result->columns = right->columns;
    result->values = malloc(result->rows*sizeof(*result->values));
    
    //use loop to allocate for every row
    for (size_t i = 0; i < result->rows; i++) {
        result->values[i] = malloc(result->columns*sizeof(*result->values[i]));
    }

    //check if the allocation is success
    checkMemory(result);
    return result;
}

//this function checks memory
void checkMemory(matrix_t * result) {
    if(result == NULL) {
        perror("No enough memory");
        exit(EXIT_FAILURE);
    }

    if(result->values==NULL) {
        perror("No enough memory");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < result->rows; i++) {
        if(result->values[i]==NULL){
            perror("No enough memory");
            exit(EXIT_FAILURE);
        }
    }
}

void multiplyMatrix(matrix_t * result, matrix_t * left, matrix_t * right) {
    //the outer two loop use to track the location in the result matrix
    for (size_t i = 0; i < result->rows; i++) {
        for (size_t j = 0; j < result->columns; j++) {
            double sum = 0.0;
            //use loop to do write value to the correct location
            for (size_t k = 0; k < left->columns; k++) {
                sum += left->values[i][k] * right->values[k][j];
            }
            result->values[i][j] = sum;
        }
    }
}

matrix_t * multiply(matrix_t * left, matrix_t * right){
    printf("trying to multiply matrix:\n");
    printf("first matrix: %zu X %zu:\n", left->rows,left->columns);
    printMatrix(left);
    printf("second matrix: %zu X %zu:\n",right->rows, right->columns);
    printMatrix(right);
    //check whether we can do the multiplication
    checkMultiplyInvaild(left, right);

    //allocate the result
    matrix_t * result = mallocResultMatrix(left, right);
    
    //do multiplication
    multiplyMatrix(result, left, right);

    return result;
}
