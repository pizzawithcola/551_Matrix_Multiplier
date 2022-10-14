#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

//this function free a matrix_t
void freeMatrix(matrix_t * matrix) {
  if(!matrix){
    return;
  }
  if(matrix -> rows && matrix -> values){
    for(int i = 0; i < matrix->rows; i++){
      if(matrix->values[i]){
        free(matrix->values[i]);
      }
    }
  }
  if(matrix -> values){
      free(matrix->values);
  }
  free(matrix);
}

//this function prints matrix_t
void printMatrix(matrix_t * matrix){
    for(size_t i = 0; i < matrix->rows; i++){
        for(size_t j = 0; j < matrix->columns; j++){
            printf("%f ",matrix->values[i][j]);
        }
        printf("\n");
    }
}
