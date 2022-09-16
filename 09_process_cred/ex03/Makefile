# Set variables
CC=gcc
LDIR=../../libs
CFLAGS=-Wall -I. -I$(LDIR)

# Archive
_ARCH = libtlpi.a
ARCH = $(patsubst %, $(LDIR)/%,$(_ARCH))

# Source
SRC = my_initgroups.c

# Compile
my_initgroups.exe: $(SRC) $(ARCH) 
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -f core my_initgroups.exe