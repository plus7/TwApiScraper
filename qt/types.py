#!/usr/bin/env python
# coding: UTF-8
import os
import re
from xml.dom import minidom, Node

filename = "../output/schema.xml"
leaf_types = "../resource/leaf_types"
leaf_dic = {}
code_dic = {}
ctor_dic = {}
child_dic = {}
root_dic = {}
util_def = """
QUrl getUrlValue(QDomElement& elm);
bool getBoolValue(QDomElement& elm);
quint64 getUInt64Value(QDomElement& elm);
QString getStrValue(QDomElement& elm);
QDateTime getDateTimeValue(QDomElement& elm);
Color getColorValue(QDomElement& elm);
"""

util_impl = """
QUrl getUrlValue(QDomElement& elm){
  return QUrl(getStrValue(elm));
}

bool getBoolValue(QDomElement& elm){
  if(getStrValue(elm)=="true"){
    return true;
  }else{
    return false;
  }
}

quint64 getUInt64Value(QDomElement& elm){
  QString str = getStrValue(elm);
  bool ok;
  quint64 dec = str.toULongLong(&ok, 10);
  if(ok)
    return dec;
  else
    return 0;
}

QString getStrValue(QDomElement& elm){
  QDomNode child = elm.firstChild();
  if(child.isNull())
    return "";
  else
    return child.nodeValue();
}

QDateTime getDateTimeValue(QDomElement& elm){
  return QDateTime::fromString(getStrValue(elm));
}

Color getColorValue(QDomElement& elm){
  return Color(getStrValue(elm));
}
"""

def fixIdentifier(name):
    name = re.sub("-", "_", name)
    name = re.sub(":", "_", name)
    return name

def getCtorCodePlural(tagName,first):
    fixedName = fixIdentifier(tagName)
    if first == True:
        aaa = "    if(tagName == \"" + tagName + "\"){\n"
    else:
        aaa = "else if(tagName == \"" + tagName + "\"){\n"
    if leaf_dic.has_key(tagName):
        if leaf_dic[tagName] == "QString":
            return aaa + "        " + fixedName + ".append(getStrValue(child));\n    }"
        elif leaf_dic[tagName] == "bool":
            return aaa + "        " + fixedName + ".append(getBoolValue(child));\n    }"
        elif leaf_dic[tagName] == "quint64":
            return aaa + "        " + fixedName + ".append(getUInt64Value(child));\n    }"
        elif leaf_dic[tagName] == "qint64":
            return aaa + "        " + fixedName + ".append(getInt64Value(child));\n    }"
        elif leaf_dic[tagName] == "int":
            return aaa + "        " + fixedName + ".append(getIntValue(child));\n    }"
        elif leaf_dic[tagName] == "Color":
            return aaa + "        " + fixedName + ".append(getColorValue(child));\n    }"
        elif leaf_dic[tagName] == "QUrl":
            return aaa + "        " + fixedName + ".append(getUrlValue(child));\n    }"
        elif leaf_dic[tagName] == "QDateTime":
            return aaa + "      " + fixedName + ".append(getDateTimeValue(child));\n    }"
    else:
        return aaa + "      " + fixedName + ".append(QSharedPointer<" + fixedName + "_t>(new "+fixedName+"_t(child)));\n    }"

def getCtorCode(tagName,first):
    fixedName = fixIdentifier(tagName)
    if first == True:
        aaa = "    if(tagName == \"" + tagName + "\"){\n"
    else:
        aaa = "else if(tagName == \"" + tagName + "\"){\n"
    if leaf_dic.has_key(tagName):
        if leaf_dic[tagName] == "QString":
            return aaa + "        " + fixedName + " = getStrValue(child);\n    }"
        elif leaf_dic[tagName] == "bool":
            return aaa + "        " + fixedName + " = getBoolValue(child);\n    }"
        elif leaf_dic[tagName] == "quint64":
            return aaa + "        " + fixedName + " = getUInt64Value(child);\n    }"
        elif leaf_dic[tagName] == "qint64":
            return aaa + "        " + fixedName + " = getInt64Value(child);\n    }"
        elif leaf_dic[tagName] == "int":
            return aaa + "        " + fixedName + " = getIntValue(child);\n    }"
        elif leaf_dic[tagName] == "Color":
            return aaa + "        " + fixedName + " = getColorValue(child);\n    }"
        elif leaf_dic[tagName] == "QUrl":
            return aaa + "        " + fixedName + " = getUrlValue(child);\n    }"
        elif leaf_dic[tagName] == "QDateTime":
            return aaa + "      " + fixedName + " = getDateTimeValue(child);\n    }"
    else:
        return aaa + "      " + fixedName + " = QSharedPointer<" + fixedName + "_t>(new "+fixedName+"_t(child));\n    }"

def processElm(elm):
    tmp = ""
    fixedClass = fixIdentifier(elm.tagName)
    tmp = tmp + "class "+fixedClass+"_t {\n"
    ctor_code = fixedClass + "_t::" + fixedClass+"_t(QDomElement& element){\n"
    ctor_code = ctor_code + "  QDomElement child = element.firstChildElement();\n"
    ctor_code = ctor_code + "  QString tagName;\n"
    ctor_code = ctor_code + "  for (; !child.isNull(); child = child.nextSiblingElement()) {\n"
    ctor_code = ctor_code + "    tagName = child.tagName()\n"
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
            fixedName = fixIdentifier(c.tagName)
            if not leaf_dic.has_key(c.tagName):
                child_dic[elm.tagName].append(c.tagName)
            if c.getAttribute("plural"):
                ctor_code = ctor_code + getCtorCodePlural(c.tagName,first)
                if leaf_dic.has_key(c.tagName):
                    members = members + "  QList<"+leaf_dic[c.tagName]+"> " + fixedName+";\n"
                else:
                    members = members + "  QList<QSharedPointer<"+fixedName+"_t> > " + fixedName+";\n"
            else:
                ctor_code = ctor_code + getCtorCode(c.tagName,first)
                if leaf_dic.has_key(c.tagName):
                    members = members + "  "+leaf_dic[c.tagName]+" "+fixedName+";\n"
                else:
                    members = members + "  QSharedPointer<"+fixedName+"_t> "+fixedName+";\n"
            first = False
    ctor_code = ctor_code + "\n  }\n}\n"
    tmp = tmp + "  " + elm.tagName+"_t(QDomElement& element);\n"
    tmp = tmp + members + "};\n"
    code_dic[elm.tagName]=tmp
    ctor_dic[elm.tagName]=ctor_code

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

f = open("petrel_types.h", 'w')
impl = open("petrel_impl.cpp", 'w')
f.write("#include <QtCore>\n#include <QtXml>\n")
f.write(util_def)
impl.write("#include <QtCore>\n#include <QtXml>\n#include \"petrel_types.h\"\n\n")
impl.write(util_impl)
for codekey in child_dic:#
    if len(child_dic[codekey]) == 0:
        f.write(code_dic[codekey])
        impl.write(ctor_dic[codekey])
        del code_dic[codekey]
print "//----------"
for codekey in code_dic:
    if not root_dic[codekey]:
        f.write(code_dic[codekey])
        impl.write(ctor_dic[codekey])

print "//----------"
for codekey in root_dic:
    if code_dic.has_key(codekey):
        f.write(code_dic[codekey])
        impl.write(ctor_dic[codekey])
        
f.close()

