#! /bin/bash

gcc -Wall -o write_beginning write_beginning.c ../../../tlpi-dist/libtlpi.a -I../../../tlpi-dist/lib -DBUFFER_MAX=200