#!/bin/sh
lynx -width=1000 -dump $1 > tmp/api
python2.6 ./writeinfo.py tmp/api $1

