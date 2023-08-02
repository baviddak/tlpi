# Set variables
CC=gcc
LDIR=../../libs
CFLAGS=-Wall -I. -I$(LDIR)

# Archive
_ARCH = libtlpi.a
ARCH = $(patsubst %, $(LDIR)/%,$(_ARCH))

# Source
SRC = null_evp.c

# Compile
null_evp.exe: $(SRC) $(ARCH) 
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -f core null_evp.exe