# Set variables
CC=gcc
LDIR=../../libs
CFLAGS=-Wall -I. -I$(LDIR)

# Archive
_ARCH = libtlpi.a
ARCH = $(patsubst %, $(LDIR)/%,$(_ARCH))

# Source
SRC = pipes.c

# Compile
pipes.exe: $(SRC) $(ARCH) 
	$(CC) $(CFLAGS) -g -O0 -o $@ $^

clean: 
	rm -f core pipes.exe
