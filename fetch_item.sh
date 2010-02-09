#!/bin/sh
lynx -dump $1 > tmp/api
python2.6 ./makestub.py tmp/api $1

