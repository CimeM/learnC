CC=gcc 
#[macro] - which compiler will be used
CFLAGS=-I.
DEPS = test_main.h 
#dependacies

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


# -c 	(to create object fiile)
# -o $@ (compilation must be named after a name that stands on the left of : )
# $< 	(the first file in dependancy list)


test_main: test_main.o testfunc.o 
	gcc -o test_main test_main.o testfunc.o -I.


# The -I. is included so that gcc will look in
# the current directory (.) for the include file test_main.h
#