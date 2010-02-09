#! /bin/sh
rm apis/*
mkdir tmp/
lynx -dump "http://apiwiki.twitter.com/Twitter-API-Documentation" > tmp/apiindex.dump
grep -o "http://.*$" < tmp/apiindex.dump > tmp/apiindex.urls
grep Twitter-REST-API < tmp/apiindex.urls > tmp/restapi.list
grep Twitter-Search-API < tmp/apiindex.urls > tmp/searchapi.list
./proc_list.sh tmp/restapi.list
./proc_list.sh tmp/searchapi.list
