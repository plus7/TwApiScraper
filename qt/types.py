#!/usr/bin/env python
# coding: UTF-8
import os
import re
from xml.dom import minidom, Node

filename = "../output/schema.xml"
leaf_types = "../resource/leaf_types"
leaf_dic = {}

def processElm(elm):
    print "class "+elm.tagName+"_t {"
    for c in elm.childNodes:
        if c.nodeType == Node.ELEMENT_NODE:
            if c.getAttribute("plural"):
                if leaf_dic.has_key(c.tagName):
                    print "  QList<"+leaf_dic[c.tagName]+"> " + c.tagName+";"
                else:
                    print "  QList<"+c.tagName+"_t> " + c.tagName+";"
            else:
                if leaf_dic.has_key(c.tagName):
                    print "  "+leaf_dic[c.tagName]+" "+c.tagName+";"
                else:
                    print "  "+c.tagName+"_t "+c.tagName+";"
    print "};"

f = open(leaf_types, 'r')
for line in f:
    line=line.strip()
    x = line.split("\t")
    leaf_dic[x[0]]=x[1]
f.close()
print leaf_dic

doc = minidom.parse(filename)
for root in doc.childNodes:
    for elm in root.childNodes:
        if elm.nodeType == Node.ELEMENT_NODE:
            if elm.getAttribute("leaf") == "true":
                leaf_dic[elm.tagName]="QString"
    for elm in root.childNodes:
        if elm.nodeType == Node.ELEMENT_NODE:
            if not leaf_dic.has_key(elm.tagName):
                processElm(elm)
