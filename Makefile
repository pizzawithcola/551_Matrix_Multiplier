CFLAGS=-std=gnu99 -pedantic -Werror -Wall
matrixMultiplier: main.c matrix.h readMatrix.c multiply.c freeAndPrint.c
	gcc $(CFLAGS) -o matrixMultiplier main.c matrix.h readMatrix.c multiply.c freeAndPrint.c -ggdb3
