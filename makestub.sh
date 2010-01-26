#!/bin/sh
lynx -dump $1 > tmp
python2.6 ./makestub.py tmp $1

