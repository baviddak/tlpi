# Set variables
CC=gcc
LDIR=../../libs
CFLAGS=-Wall -I. -I$(LDIR)

# Archive
_ARCH = libtlpi.a
ARCH = $(patsubst %, $(LDIR)/%,$(_ARCH))

# Headers
HDR = my_envlib.h

# Source
SRC = main.c my_envlib.c

# Compile
envlib.exe: $(SRC) $(ARCH) $(HDR)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(ARCH)

clean: 
	rm -f core envlib.exe
