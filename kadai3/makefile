# -*- Makefile -*-
# Makefile for scheduling problem 2012.
# Just type `make', and you'll get executable file `sche2012'.

CC = gcc
#CFLAGS = -O2 -g -Wall
CFLAGS = -g -Wall

TARGET = sche2012
OBJS = main.o support.o

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(TARGET)

#$(TARGET) : $(OBJS)
#	$(CC) -o $@ $?
$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS) *~

main.o: main.c
support.o : support.c
