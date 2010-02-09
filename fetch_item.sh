#!/bin/sh
lynx -width=1000 -dump $1 > tmp/api
python2.6 ./makestub.py tmp/api $1

