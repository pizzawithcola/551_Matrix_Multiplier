CFLAGS=-std=gnu99 -pedantic -Werror -Wall
matrixMultiplier: main.c matrix.h readMatrix.c readMatrix.h multiply.c multiply.h freeAndPrint.c freeAndPrint.h
	gcc $(CFLAGS) -o matrixMultiplier main.c readMatrix.c multiply.c freeAndPrint.c -ggdb3
