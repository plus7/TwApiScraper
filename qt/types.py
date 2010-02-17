#!/usr/bin/env python
# coding: UTF-8
import os
import re
from xml.dom import minidom, Node

filename = "../output/schema.xml"
leaf_types = "../resource/leaf_types"
leaf_dic = {}
code_dic = {}
child_dic = {}
root_dic = {}

def getCtorCodePlural(tagName,first):
    if first == True:
        aaa = "      if(tagName == \"" + tagName + "\"){\n"
    else:
        aaa = "else if(tagName == \"" + tagName + "\"){\n"
    if leaf_dic.has_key(tagName):
        if leaf_dic[tagName] == "QString":
            return aaa + "        " + tagName + ".append(getStrValue(child));\n      }"
        elif leaf_dic[tagName] == "bool":
            return aaa + "        " + tagName + ".append(getBoolValue(child));\n      }"
        elif leaf_dic[tagName] == "quint64":
            return aaa + "        " + tagName + ".append(getUInt64Value(child));\n      }"
        elif leaf_dic[tagName] == "qint64":
            return aaa + "        " + tagName + ".append(getInt64Value(child));\n      }"
        elif leaf_dic[tagName] == "int":
            return aaa + "        " + tagName + ".append(getIntValue(child));\n      }"
        elif leaf_dic[tagName] == "ColorString":
            return aaa + "        " + tagName + ".append(getColorValue(child));\n      }"
        elif leaf_dic[tagName] == "QUrl":
            return aaa + "        " + tagName + ".append(getUrlValue(child));\n      }"
        elif leaf_dic[tagName] == "QDateTime":
            return aaa + "        " + tagName + ".append(getDateTimeValue(child));\n      }"
    else:
        return aaa + "        " + tagName + ".append(" + tagName + "_t(child));\n      }"

def getCtorCode(tagName,first):
    if first == True:
        aaa = "      if(tagName == \"" + tagName + "\"){\n"
    else:
        aaa = "else if(tagName == \"" + tagName + "\"){\n"
    if leaf_dic.has_key(tagName):
        if leaf_dic[tagName] == "QString":
            return aaa + "        " + tagName + " = getStrValue(child);\n      }"
        elif leaf_dic[tagName] == "bool":
            return aaa + "        " + tagName + " = getBoolValue(child);\n      }"
        elif leaf_dic[tagName] == "quint64":
            return aaa + "        " + tagName + " = getUInt64Value(child);\n      }"
        elif leaf_dic[tagName] == "qint64":
            return aaa + "        " + tagName + " = getInt64Value(child);\n      }"
        elif leaf_dic[tagName] == "int":
            return aaa + "        " + tagName + " = getIntValue(child);\n      }"
        elif leaf_dic[tagName] == "ColorString":
            return aaa + "        " + tagName + " = getColorValue(child);\n      }"
        elif leaf_dic[tagName] == "QUrl":
            return aaa + "        " + tagName + " = getUrlValue(child);\n      }"
        elif leaf_dic[tagName] == "QDateTime":
            return aaa + "        " + tagName + " = getDateTimeValue(child);\n      }"
    else:
        return aaa + "        " + tagName + " = " + tagName + "_t(child);\n      }"

def processElm(elm):
    tmp = ""
    tmp = tmp + "class "+elm.tagName+"_t {\n"
    ctor_code = "  " + elm.tagName+"_t(QDomElement& element){\n"
    ctor_code = ctor_code + "    QDomElement child = element.firstChildElement();\n"
    ctor_code = ctor_code + "    QString tagName;\n"
    ctor_code = ctor_code + "    for (; !child.isNull(); child = child.nextSiblingElement()) {\n"
    ctor_code = ctor_code + "      tagName = child.tagName()\n"
    members = ""
    if not child_dic.has_key(elm.tagName):
        child_dic[elm.tagName] = []
    if elm.getAttribute("root") == "true" and not root_dic.has_key(elm.tagName):
        root_dic[elm.tagName] = True
    else:
        root_dic[elm.tagName] = False
    first = True
    for c in elm.childNodes:
        if c.nodeType == Node.ELEMENT_NODE:
            if not leaf_dic.has_key(c.tagName):
                child_dic[elm.tagName].append(c.tagName)
            if c.getAttribute("plural"):
                ctor_code = ctor_code + getCtorCodePlural(c.tagName,first)
                if leaf_dic.has_key(c.tagName):
                    members = members + "  QList<"+leaf_dic[c.tagName]+"> " + c.tagName+";\n"
                else:
                    members = members + "  QList<"+c.tagName+"_t> " + c.tagName+";\n"
            else:
                ctor_code = ctor_code + getCtorCode(c.tagName,first)
                if leaf_dic.has_key(c.tagName):
                    members = members + "  "+leaf_dic[c.tagName]+" "+c.tagName+";\n"
                else:
                    members = members + "  "+c.tagName+"_t "+c.tagName+";\n"
            first = False
    ctor_code = ctor_code + "\n    }\n  }\n"
    tmp = tmp + ctor_code + members + "};\n"
    code_dic[elm.tagName]=tmp

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


print "#include <QtCore>\n#include <QtXml>\n"
for codekey in child_dic:#
    if len(child_dic[codekey]) == 0:
        print code_dic[codekey]
        del code_dic[codekey]
print "//----------"
for codekey in code_dic:
    if not root_dic[codekey]:
        print code_dic[codekey]
print "//----------"
for codekey in root_dic:
    if code_dic.has_key(codekey):
        print code_dic[codekey]
        
