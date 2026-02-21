# Variables
#
# variables for compiling rules
SHELL=/bin/bash
CC=gcc
CFLAGS=-std=c17 -g3
VPATH=Database

OBJS = main.o constants.o input.o row.o pager.o btree.o table.o cursor.o statement.o

all: database

database: $(OBJS)
	${CC} ${CFLAGS} -o $@ $^ -lm

run:
	./database data.db

wipe:
	rm -f data.db

clean:
	rm -f database *.o
