# Set variables
CC=gcc
LDIR=../../libs
CFLAGS=-Wall -I. -I$(LDIR)

# Archive
_ARCH = libtlpi.a
ARCH = $(patsubst %, $(LDIR)/%,$(_ARCH))

# Source
SRC = bidirectional_comms.c

# Compile
bidirectional_comms: $(SRC) $(ARCH) 
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean: 
	rm -f core bidirectional_comms
