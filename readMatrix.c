#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h" 
#include "readMatrix.h"
#include <errno.h>
#include "freeAndPrint.h"

//this function check if malloc succeed
void checkMalloc(void* item){
    if(!item){
        perror("no memory to malloc"); 
        errno = 1;
    }
}
//this function will do the malloc for matrix_t -> values
void mallocValuesForMatrix(matrix_t* m){
    m->values = (double **)malloc(m -> rows * sizeof(*m->values));
    checkMalloc(m->values);
    for(int i = 0; i < m -> rows; i++){
        m->values[i] = (double *)malloc(m -> columns * sizeof(*m->values[i]));
        checkMalloc(m->values[i]);
    }
}

//this function check the input for row/column is valid
size_t checkValidSizeTAndReturn(char * input){
    char *endptr = NULL;
    //try to do convertion
    size_t result = strtoull(input, &endptr, 10);
    //errno should remain 0, endptr has to be \0 or \r
    if (errno != 0 || (*endptr != '\0' && *endptr != '\r' && *endptr != '\n') || input == endptr) {
        perror("invalid row/column input");
        errno = 1;
    }
    return result;
}

//this function fill in matrix_t -> row/column
void fillInMatrixRowColumn(matrix_t* m, FILE* f){
    char * curr = NULL;
    size_t linecap;
    //read column from input
    if(getline(&curr, &linecap, f) >= 0){
        m -> columns = checkValidSizeTAndReturn(curr);
    } else { 
        perror("invalid input");
        errno = 1;
    }
    //read row from input
    if(getline(&curr, &linecap, f) >= 0){
        m -> rows = checkValidSizeTAndReturn(curr);
    } else { 
        perror("invalid input");
        errno = 1;
    }
    free(curr);
}

//this function check if a valid double was in the line
double checkValidDoubleAndReturn(char * input){
    char *endptr;
    //try convert
    double result = strtod(input, &endptr);
    //same check as above, errno should be 0, endptr be \0 or \r
    if (errno != 0 ||  (*endptr != '\0' && *endptr != '\r' && *endptr != '\n') || input == endptr) {
        perror("invalid double input");
        errno = 1;
    }
    return result;
}

//this function fills in double to the matrix
void fillInDoubleInMatrix(matrix_t* m, size_t count, FILE* f){
    char * curr = NULL;
    size_t linecap;
    for(int i = 0; i < m -> rows; i++){
        for(int j = 0; j < m -> columns; j++){
            if(getline(&curr, &linecap, f) >= 0){
                m -> values[i][j] = checkValidDoubleAndReturn(curr);
            } else { 
                perror("invalid input");
                errno = 1;
    	    }
        }
    }
    //after all cell are filled, there should be no more lines
    if(getline(&curr, &linecap, f) >= 0){
        perror("too many lines");
        errno = 1;
    }
    free(curr);
}

//this function will read from a file, create a matrix and fill in infos for the matrix
matrix_t * readMatrix(const char * filename) {
    errno = 0;
    matrix_t * m = (matrix_t*)malloc(sizeof(*m));
    checkMalloc(m);
    FILE * f = fopen(filename, "r");
    //fill in row/column info
    fillInMatrixRowColumn(m, f);
    //get number of cells
    size_t count = m -> rows * m -> columns;
    if(count == 0){
        perror("invalid input");
	errno = 1;
    }
    //malloc cells
    mallocValuesForMatrix(m);
    //fill in cells
    fillInDoubleInMatrix(m, count, f);
    if(fclose(f) != 0){
        perror("fail to close file");
        errno = 1;
    }
    if(errno != 0){
        freeMatrix(m);
        return NULL;
    }
    return m;
}
