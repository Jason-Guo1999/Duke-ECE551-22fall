CFLAGS = -std=gnu99  -Wall -ggdb
rotateMatrix: rotateMatrix.o
	gcc -o $@ rotateMatrix.o
rotatematrix.o: rotatematrix.c
	gcc $(CFLAGS) -c  rotateMatrix.c

.PHONY:clean
clean:
	rm -f rotateMatrix *.o *.o~
