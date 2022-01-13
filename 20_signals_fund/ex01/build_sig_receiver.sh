#! /bin/bash
gcc -Wall -o sig_receiver_sigaction.exe sig_receiver_sigaction.c ../../../tlpi-dist/libtlpi.a -I../../../tlpi-dist/lib
gcc -Wall -o sig_sender.exe sig_sender.c ../../../tlpi-dist/libtlpi.a -I../../../tlpi-dist/lib
