# Copyright © 2014 Bart Massey
# [This program is licensed under the "MIT License"]
# Please see the file COPYING in the source
# distribution of this software for license terms.

CC = gcc
# CDEBUG = -g -DDEBUG_ROTATE -DDEBUG_PROGRESS=1000000
CDEBUG = -O4
CFLAGS =  $(CDEBUG) -Wall -std=c99

polyominoer: polyominoer.o
	gcc $(CDEBUG) -o polyominoer polyominoer.o

clean:
	-rm -f polyominoer polyominoer.o
