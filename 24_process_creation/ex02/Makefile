# Set variables
CC=gcc
LDIR=../../libs
CFLAGS=-Wall -I. -I$(LDIR)

# Archive
_ARCH = libtlpi.a
ARCH = $(patsubst %, $(LDIR)/%,$(_ARCH))

# Source
SRC = vfork_fd.c

# Compile
vfork_fd.exe: $(SRC) $(ARCH) 
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -f core vfork_fd.exe