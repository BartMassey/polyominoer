CC = gcc
CFLAGS = -g -Wall -std=c99 # -DDEBUG_ROTATE

polyominoer: polyominoer.o
	gcc -g -o polyominoer polyominoer.o

clean:
	-rm -f polyominoer polyominoer.o
