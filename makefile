# Variables
#
# variables for compiling rules
SHELL=/bin/bash
CC=gcc
CFLAGS=-std=c17 -g3
VPATH=Database

all: database

database: Database.o
	${CC} ${CFLAGS} -o $@ $^ -lm

Database.o: Database.c

run:
	./database data.db

wipe:
	rm -f data.db

clean: 
	rm -f database *.o