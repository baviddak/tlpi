# Set variables
CC=gcc
LDIR=../../libs
CFLAGS=-Wall -I. -I$(LDIR)

# Archive
_ARCH = libtlpi.a
ARCH = $(patsubst %, $(LDIR)/%,$(_ARCH))

# Source
SRC = child_init.c

# Compile
child_init.exe: $(SRC) $(ARCH) 
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -f core child_init.exe