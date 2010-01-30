#!/usr/bin/env python
# coding: UTF-8
import os
import re
from xml.dom import minidom, Node
dirList=os.listdir("./apis/")
dic = {}
roots = {}

def scanNode(node, level = 0):
    if node.nodeType == Node.ELEMENT_NODE:
        parent = node.parentNode
        if parent and parent.nodeType == Node.ELEMENT_NODE:
            if dic.has_key(parent.tagName):
                if not dic[parent.tagName].has_key(node.tagName):
                    dic[parent.tagName][node.tagName] = {}
            else:
                dic[parent.tagName] = {node.tagName:{}}
            if level == 2:
                roots[parent.tagName] = True
    elif node.nodeType == Node.TEXT_NODE:
        parent = node.parentNode
        prevElm = node.previousSibling
        #print parent.tagName
        #if prevElm:
            #print "  " + prevElm.tagName
        if node.data.find("truncated") > -1 or node.data.find("...") > -1:
            #print "***truncated***"
            dic[parent.tagName][prevElm.tagName]["plural"] = True
    if node.hasChildNodes:
        for child in node.childNodes:
            scanNode(child, level+1)

for fname in dirList:
    if fname.endswith(".xml"):
        print fname
        doc = minidom.parse("./apis/"+fname)
        scanNode(doc)
                
#print dic
#print roots
#exit()
print "<schema xmlns:georss=\"http://hoge/\">"
for elm in dic:
    if roots.has_key(elm):
        print "<" + elm + " root=\"true\">"
    else:
        print "<" + elm + ">"
    for child in dic[elm]:
        if dic[elm][child].has_key("plural") and dic[elm][child]["plural"]:
            print "  <"+child+" plural=\"true\"/>"
        else:
            print "  <"+child+"/>"
    print "</" + elm + ">"
print "</schema>"
