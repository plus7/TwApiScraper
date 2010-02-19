#!/usr/bin/env python
# coding: UTF-8
import sys
import re
import os.path
import string

type_dic = {'id': 'quint64', 
            'since_id': 'quint64', 
            'max_id': 'quint64', 
            'user_id': 'quint64', 
            'in_reply_to_status_id': 'quint64',
            'list_id': 'quint64',
            'count': 'int',
            'page': 'int',
            'cursor': 'qint64',
            'user': 'QString',
            'screen_name': 'QString', 
            'name': 'QString',
            'source_id': 'quint64', 
            'source_screen_name': 'QString', 
            'target_id': 'quint64', 
            'target_screen_name': 'QString'
            }

s_intv, s_url, s_format, s_httpmethod, s_reqauth, s_apilimit, s_params, s_params2, s_response, s_xml, s_example = range(11)
state = s_intv

urlrx = re.compile("^URL.*:$")
fmtrx = re.compile("^Format.*:$")
methodrx = re.compile("^HTTP Method.*:$")
rarx = re.compile("^Requires Authentication.*:$")
limitrx = re.compile("^API rate limited.*:$")
paramrx = re.compile("^Parameter.*:$")
resprx = re.compile("^Response.*:$")
xmlrx = re.compile("^XML example.*:$")
tagrx = re.compile("<([a-zA-Z][a-zA-Z0-9_\-]*)\s*.*>")
exrx = re.compile("^Usage examples.*:$")
httprx = re.compile("http://.*")
httpmethodrx = re.compile("(GET|POST|DELETE|CREATE)")
param_ext_rx = re.compile("\* (.*?)(:|\.)")
param_opt = re.compile("\* (.*?)(:|\.) (Optional|Required)")

url = ""
fmt = ""
http = ""
limit = ""
auth = ""
xml = ""
rootelm = ""
flag = False
params = []

for line in open(sys.argv[1], 'r'):
    current = line.strip()
    if state == s_intv:
        if urlrx.match(current):
            state = s_url
        elif fmtrx.match(current):
            state = s_format
        elif methodrx.match(current):
            state = s_httpmethod
        elif rarx.match(current):
            state = s_reqauth
        elif limitrx.match(current):
            state = s_apilimit
        elif paramrx.match(current):
            state = s_params
        elif resprx.match(current):
            state = s_response
        elif exrx.match(current):
            state = s_example
    elif state == s_url:
        if httprx.match(current):
            url = current
            state = s_intv
    elif state == s_format:
        if current != "":
            fmt = current
            state = s_intv
    elif state == s_httpmethod:
        if httpmethodrx.match(current):
            http = current
            state = s_intv
    elif state == s_reqauth:
        if current != "":
            auth = current
            state = s_intv
    elif state == s_apilimit:
        if current != "":
            limit = current
            state = s_intv
    elif state == s_params:
        if current.startswith("* "):# or current.startswith("+ "):
            m = param_ext_rx.match(current)
            if m and not (' ' in m.group(1)) and not ('[' in m.group(1)):
                params.append(m.group(1))
        elif current == "":
            state = s_params2
        elif resprx.match(line):
            state = s_response
    elif state == s_params2:
        if current == "":
            state = s_intv
        else:
            state = s_params
            if current.startswith("* "):# or current.startswith("+ "):
                m = param_ext_rx.match(current)
                if m and not (' ' in m.group(1)) and not ('[' in m.group(1)):
                    params.append(m.group(1))
            elif resprx.match(line):
                state = s_response
    elif state == s_response:
        if xmlrx.match(current):
            state = s_xml
    elif state == s_example:
        state = s_intv
    elif state == s_xml:
        #hogerx = re.compile("Twitter REST API Method:")
        #if exrx.match(current) or hogerx.match(current):
        #     state = s_intv
        #else:
        #     if current != "":
        if current != "":
            current = string.replace(current, '& ', '&amp; ')
            xml = xml + current + "\n"
            if not flag:
                m = tagrx.match(current)
                if m:
                    rootelm = m.group(1)
                    #print "hogehoge:</"+rootelm+">"
                    if current.endswith("</"+rootelm+">"):
                        state = s_intv
                    else:
                        flag = True
            else:
                #print current
                if current == "</"+rootelm+">":
                    #print "finished"
                    state = s_intv
                    flag = False
                elif state == s_example:
                    state = s_intv

file_rx = re.compile(".*%3A-(.*)$")
print sys.argv[2]
mmm = file_rx.match(sys.argv[2])
filename = "error"
if mmm:
    filename = mmm.group(1)
    filename = filename.replace('%C2%A0', "-")

hoge = filename.strip().split("-",1)
name = ''
if filename.startswith("GET") or filename.startswith("POST") or filename.startswith("DELETE"):
    name = filename.replace('-',' ')
    name = name.title()
else:
    if hoge[0] == "account" or hoge[0] == "statuses":
        name = hoge[1]
    else:
        hoge.reverse()
        name = '_'.join(hoge)
    name = name.replace('_',' ')

name = name.title()
name = name.replace(" ","")
oldname = name
plural = re.compile("(.*)s$")
if (url.endswith("/id.format") or ("POST" in http or "DELETE" in http)) and name.endswith("s"):
    name = name[0:len(name)-1]
    if name.endswith("se") or name.endswith("oe") or name.endswith("xe") or name.endswith("she") or name.endswith("che"):
        name = name = name[0:len(name)-1]
print name

if os.path.exists("apis/"+name+".api"):
    name = oldname

f = open("apis/"+name+".api", 'w')
#first = "int QwTwitter::"+name+"("
#cppparams = []
#for key in params:
#    if type_dic.has_key(key):
#        if type_dic[key] == 'QString':
#            cppparams.append("const QString& "+key)
#        else:
#            cppparams.append(type_dic[key] + " " + key)
#    else:
#        cppparams.append("const QString& "+key)
#first = first + ', '.join(cppparams) + '){\nreturn 0;\n}\n\n'
    #rx = re.compile"(/|\.)("+key+")(/|\.)"
    #m = rx.match(url)
    #if m:
        
#first = first + ', '.join(cppparams) + "){\n"
#f.write(first)
f.write("URL:{0}\n".format(url))
f.write("Format:{0}\n".format(fmt))
f.write("Method:{0}\n".format(http))
f.write("Limit:{0}\n".format(limit))
f.write("AuthRequired:{0}\n".format(auth))
f.write("Params:{0}\n".format(','.join(params)))
f.write("XMLRoot:{0}\n".format(rootelm))
f.close()

if xml != "":
    xmlf = open("apis/"+name+".xml", 'w')
    xmlf.write(xml)
    xmlf.close()
