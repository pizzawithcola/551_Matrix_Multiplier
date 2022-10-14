#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h" 
#include "readMatrix.h"
#include <errno.h>
#include "freeAndPrint.h"

//this function will do the malloc for matrix_t -> values
void mallocValuesForMatrix(matrix_t* m){
    m->values = (double **)malloc(m -> rows * sizeof(*m->values));
    if(!m->values){
	errno = 1;
	return;
    }
    for(int i = 0; i < m -> rows; i++){
        m->values[i] = (double *)malloc(m -> columns * sizeof(*m->values[i]));
        if(!m->values[i]){
	    errno = 1;
	    return;
	}
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
        if(errno != 0){
            free(curr);
            return;
        }
    } else { 
        perror("invalid input");
        errno = 1;
    }
    //read row from input
    if(getline(&curr, &linecap, f) >= 0){
        m -> rows = checkValidSizeTAndReturn(curr);
        if(errno != 0){
            free(curr);
            return;
        }
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
                if(errno != 0){
                    free(curr);
                    return;
                }
 	    } else { 
                perror("invalid input");
                errno = 1;
		free(curr);
		return;
    	    }
        }
    }
    //after all cell are filled, there should be no more lines
    if(getline(&curr, &linecap, f) >= 0){
        perror("too many lines");
        errno = 1;
	free(curr);
	return;
    }
    free(curr);
}

void freeAndClose(matrix_t * m, FILE * f){
    freeMatrix(m);
    if(fclose(f) != 0){
        perror("faill to close file");
    }
}

//this function will read from a file, create a matrix and fill in infos for the matrix
matrix_t * readMatrix(const char * filename) {
    errno = 0;
    FILE * f = fopen(filename, "r");
    if(f == NULL){
        return NULL;
    }
    matrix_t * m = (matrix_t*)malloc(sizeof(*m));
    if(!m){
    	if(fclose(f) != 0){
       	    perror("faill to close file");
        }
	return NULL;
    }
    m -> values = NULL;
    if(errno != 0){
        freeAndClose(m, f);
        return NULL;
    }
    //fill in row/column info
    fillInMatrixRowColumn(m, f);
    if(errno != 0){
        freeAndClose(m, f);
	return NULL;
    }
    //get number of cells
    size_t count = m -> rows * m -> columns;
    if(count == 0){
        perror("size is 0");
        freeAndClose(m, f);
	return NULL;
    }
    //malloc cells
    mallocValuesForMatrix(m);
    if(errno != 0){
        freeAndClose(m, f);
	return NULL;
    }
    //fill in cells
    fillInDoubleInMatrix(m, count, f);
    if(errno != 0){
        freeAndClose(m, f);
	return NULL;
    }

    if(fclose(f) != 0){
        perror("faill to close file");
    }
    return m;
}
