#!/bin/bash
rm -f server client
gcc -Wall -o server us_xfr_sv.c
gcc -Wall -o client us_xfr_cl.c
