#! /bin/sh
rm apis/*
lynx -dump "http://apiwiki.twitter.com/Twitter-API-Documentation" > index.txt
grep -o "http://.*$" < index.txt > index.urls
grep Twitter-REST-API < index.urls > restapi.list
grep Twitter-Search-API < index.urls > searchapi.list
./api.sh restapi.list
./api.sh searchapi.list
