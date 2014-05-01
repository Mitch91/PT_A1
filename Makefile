###############################################################################
# COSC1283/1284 - Programming Techniques
# Semester 2 2013 Assignment #2 - SCSIT Program Management System
# Full Name        : EDIT HERE
# Student Number   : EDIT HERE
# Yallara Username : EDIT HERE
# Course Code      : EDIT HERE
# Program Code     : EDIT HERE
# Start up code provided by Paul Miller and Lin Padgham
################################################################################

CC = gcc
CFLAGS = -ansi -pedantic -Wall -g
CPPFLAGS = 
LDFLAGS =
SRCS = tm.c tm_coins.c tm_options.c tm_utility.c tm_stock.c
OBJS = $(SRCS:.c=.o)

tm: $(OBJS)
	$(CC) $(CFLAGS) -o tm $(OBJS)
	
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -f *.o tm

.PHONY:archive
archive:
	zip $(USER) tm.c tm.h tm_coins.c tm_coins.h tm_options.c tm_options.h \
	tm_stock.c tm_stock.h tm_utility.c tm_utility.h tm_readme.txt Makefile
