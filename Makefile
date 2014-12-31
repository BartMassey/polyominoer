# Copyright © 2014 Bart Massey
# [This program is licensed under the "MIT License"]
# Please see the file COPYING in the source
# distribution of this software for license terms.

CC = gcc
CFLAGS = -g -Wall -std=c99 # -DDEBUG_ROTATE

polyominoer: polyominoer.o
	gcc -g -o polyominoer polyominoer.o

clean:
	-rm -f polyominoer polyominoer.o
