#! /bin/bash

gcc -Wall -o atomic_append atomic_append.c ../../../tlpi-dist/libtlpi.a -I../../../tlpi-dist/lib
