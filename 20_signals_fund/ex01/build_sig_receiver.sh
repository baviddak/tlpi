#! /bin/bash

gcc -Wall -o sig_receiver_sigaction sig_receiver_sigaction.c ../../../tlpi-dist/libtlpi.a -I../../../tlpi-dist/lib

gcc -Wall -o sig_sender sig_sender.c ../../../tlpi-dist/libtlpi.a -I../../../tlpi-dist/lib
