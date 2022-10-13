#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct matrix_tag {
    double ** values;
    size_t rows;
    size_t columns;
}
typedef struct matrix_tag matrix_t;

matrix_t * readMatrix(const char * filename) {
    matrix_t * m = (matrix_t*)malloc(sizeof(*m));
    FILE * f = fopen(filename, "r");
    char * curr = NULL;
    size_t linecap;
    if(getline(&curr, &linecap, f) >= 0){
        m -> columns = strtoul(curr);
    } else { 
        perror("invalid input");
        exit(EXIT_FAILURE);
    }
    if(getline(&curr, &linecap, f) >= 0){
        m -> rows = strtoul(curr);
    } else { 
        perror("invalid input");
        exit(EXIT_FAILURE);
    }
    size_t count = m -> rows * m -> columns;
    if(count == 0){
        perror("invalid input");
        exit(EXIT_FAILURE);
    }
    m->values = (double **)malloc(m -> rows * sizeof(*m->values));
    for(int i = 0; i < m -> rows; i++){
        m->values[i] = (double *)malloc(m -> columns * sizeof(*m->values[i]));
    }
    for(int i = 0; i < m -> rows; i++){
        for(int j = 0; j < m -> columns; j++){
            if(getline(&curr, &linecap, f) >= 0){
                m -> values[i][j] = strtod(curr);
            } else { 
                perror("invalid input");
                exit(EXIT_FAILURE);
            }
        }
    }
    return matrix_t;
}