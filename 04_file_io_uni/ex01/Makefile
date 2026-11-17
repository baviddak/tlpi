# Set variables
CC=gcc
LDIR=../../libs
CFLAGS=-Wall -I. -I$(LDIR)

# Source
SRC = main.c

# Compile
my_tee: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -f core my_tee
