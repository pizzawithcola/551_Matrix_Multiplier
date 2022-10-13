//
//  main.c
//  DKU Semester I
//
//  Created by Jamie on 2022/10/13.
//

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(int argc, char ** argv){
    // regular check
    if(argc != 3){
        perror("Argument Number Error!");
        return EXIT_FAILURE;
    }
    
    // import and read the first and second file
    FILE * firstFile = fopen("matrix1.txt", "r");
    matrix_t * firstMatrix = malloc(sizeof(*firstMatrix));
    firstMatrix = readMatrix(firstFile);
    
    FILE * secondFile = fopen("matrix2.txt", "r");
    matrix_t * secondMatrix = malloc (sizeof(*firstMatrix));
    secondMatrix = readMatrix(secondFile);
    
    matrix_t * result = malloc(sizeof(*result));
    result = multiply(firstMatrix, secondMatrix);
    
    printMatrix(result);
    
    freeMatrix(firstMatrix);
    freeMatrix(secondMatrix);
    freeMatrix(result);
}
