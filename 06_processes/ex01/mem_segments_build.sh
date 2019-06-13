#! /bin/bash

gcc -Wall -S -o mem_segments.s mem_segments.c ../../tlpi-dist/libtlpi.a -I../../tlpi-dist/lib 
