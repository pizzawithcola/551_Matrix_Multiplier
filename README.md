# This is for the lecture of ECE 551 on Oct 13

### Team Member
#### Ruolin Meng
#### Juncheng Liu
#### Yueting Luo
#### Zhibo Jia

## Content:
### Code:
	- main: main.c
	- readMatrix: readMatrix.c readMatrix.h
	- multiply: multiply.c multiply.h
	- freeAndPrint: freeAndPrint.c freeAndPrint.h
	- matrix: matrix.h
### Testcases:
	- testcase*/
	- test_result.txt

## Structures:
#### readMatrix:
	- matrix_t * readMatrix(const char * filename);
#### multiply:
	- matrix_t * multiply(matrix_t * left, matrix_t * right);
#### freeAndPrint:
	- void freeMatrix(matrix_t * matrix);
	- void printMatrix(matrix_t * matrix);
