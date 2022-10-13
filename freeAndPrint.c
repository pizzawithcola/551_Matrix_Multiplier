#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


void freeMatrix(matrix_t * matrix) {
  //WRITE ME!
  for(int i = 0; i < matrix->rows; i++){
    free(matrix->values[i]);
  }
  free(matrix->values);
  free(matrix);
}
//
void printMatrix(matrix_t * matrix){
    for(size_t i = 0; i < matrix->rows; i++){
        for(size_t j = 0; j < matrix->columns; j++){
            printf("%f ",matrix->values[i][j]);
        }
        printf("\n");
    }
}
