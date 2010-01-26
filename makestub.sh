#!/bin/sh
lynx -dump $1 > tmp
python ./makestub.py tmp $1

