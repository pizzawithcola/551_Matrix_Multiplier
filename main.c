//  DKU Semester I
//
//  Created by Jamie on 2022/10/13.

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "readMatrix.h"
#include "multiply.h"
#include "freeAndPrint.h"

int main(int argc, char ** argv){
    // regular check
    if(argc != 3){
        perror("Argument Number Error!");
        return EXIT_FAILURE;
    }
    const char * fileName1 = argv[1];
    const char * fileName2 = argv[2];
    // import and read the first and second file
    matrix_t * firstMatrix = readMatrix(fileName1);
    if(!firstMatrix){
	exit(EXIT_FAILURE);
    }
    matrix_t * secondMatrix = readMatrix(fileName2);
    if(!secondMatrix){
        freeMatrix(firstMatrix);
        exit(EXIT_FAILURE);
    }
    //do multiplication
    matrix_t * result = multiply(firstMatrix, secondMatrix);
    //print
    printf("the result matrix is:\n");
    printMatrix(result);
    //free
    freeMatrix(firstMatrix);
    freeMatrix(secondMatrix);
    freeMatrix(result);
}
