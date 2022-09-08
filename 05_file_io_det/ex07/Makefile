# Set variables
CC=gcc
LDIR=../../libs
CFLAGS=-Wall -I. -I$(LDIR)

# Archive
_ARCH = libtlpi.a
ARCH = $(patsubst %, $(LDIR)/%,$(_ARCH))

# Source
RD_SRC = my_readv.c
WR_SRC = my_writev.c

# Compile read
# my_readv.exe: $(RD_SRC) $(ARCH) 
# 	$(CC) $(CFLAGS) -o $@ $^

# Compile write
my_writev.exe: $(WR_SRC) $(ARCH) 
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -f core my_writev.exe my_readv.exe