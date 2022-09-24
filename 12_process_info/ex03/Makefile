# Set variables
CC=gcc
LDIR=../../libs
CFLAGS=-Wall -I. -I$(LDIR)

# Archive
_ARCH = libtlpi.a
ARCH = $(patsubst %, $(LDIR)/%,$(_ARCH))

# Source
SRC = file_path.c

# Compile
file_path.exe: $(SRC) $(ARCH) 
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -f core file_path.exe