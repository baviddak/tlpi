#! /bin/bash

gcc -Wall -o longjmp_into_returned_fn longjmp_into_returned_fn.c ../../../tlpi-dist/libtlpi.a -I../../../tlpi-dist/lib
