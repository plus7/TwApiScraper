#!/usr/bin/env python2.6
# coding: UTF-8
import sys
import re
import os.path
import string
import commands

invoke_defs=[]
invoke_impls=[]
recv_case=[]
signal_defs=[]
role_type_defs=[]

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

def fixIdentifier(name):
    name = re.sub("-", "_", name)
    name = re.sub(":", "_", name)
    name = re.sub("^protected$", "protected_", name)
    hoge = re.sub("^long$", "long_", name)
#    print hoge
    return hoge

HEADER_STR = """
#ifndef PETREL_H
#define PETREL_H

#include <QObject>
#include <QtNetwork>
#include "../petrel_types.h"

enum ATTR_TYPE {{
    ATTR_ROLE
}};

//autogenerated enum
enum ROLE_TYPE {{
    {0}
}};

class Petrel : public QObject
{{
    Q_OBJECT
public:
    Petrel(const QString& userid, const QString& pass);
    virtual ~Petrel();
    //BEGIN auto generated methods
{1}
    //END auto generated methods
    void issueGetRequest(QNetworkRequest& req);
    void issuePostRequest(QNetworkRequest& req, QByteArray& data);
    void issuePutRequest(QNetworkRequest& req, QByteArray& data);
    void issueDeleteRequest(QNetworkRequest& req);
signals:
    //BEGIN auto generated signals
{2}
    //END auto generated signals

public slots:
    void replyFinished( QNetworkReply* );
private:
    QNetworkAccessManager *m_manager;
    QString m_userid;
    QString m_pass;
}};

#endif // PETREL_H
"""

IMPL_STR = """#include "petrel.h"

Petrel::Petrel(const QString& userid, const QString& pass)
        :m_manager(new QNetworkAccessManager( this )),
        m_userid(userid),m_pass(pass)
{{
    connect(m_manager,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(replyFinished(QNetworkReply*)));
}}

Petrel::~Petrel()
{{
}}

//HTTP
void Petrel::issueGetRequest(QNetworkRequest& req){{
    QByteArray auth = m_userid.toUtf8() + ":" + m_pass.toUtf8();
    req.setRawHeader( "Authorization", auth.toBase64().prepend( "Basic " ) );
    m_manager->get(req);
}}

void Petrel::issuePostRequest(QNetworkRequest& req, QByteArray& data){{
    QByteArray auth = m_userid.toUtf8() + ":" + m_pass.toUtf8();
    req.setRawHeader( "Authorization", auth.toBase64().prepend( "Basic " ) );
    m_manager->post(req,data);
}}

void Petrel::issuePutRequest(QNetworkRequest& req, QByteArray& data){{
    QByteArray auth = m_userid.toUtf8() + ":" + m_pass.toUtf8();
    req.setRawHeader( "Authorization", auth.toBase64().prepend( "Basic " ) );
    m_manager->put(req,data);
}}

void Petrel::issueDeleteRequest(QNetworkRequest& req){{
    QByteArray auth = m_userid.toUtf8() + ":" + m_pass.toUtf8();
    req.setRawHeader( "Authorization", auth.toBase64().prepend( "Basic " ) );
    m_manager->deleteResource(req);
}}

//BEGIN autogenerated methods
{0}
//END autogenerated methods

void Petrel::replyFinished(QNetworkReply *reply)
{{
    QNetworkRequest request = reply->request();
    QString replyStr( reply->readAll() );
    int role = request.attribute( (QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE) ).toInt();
    QDomDocument doc;
    doc.setContent(replyStr);
    switch(role){{
        //autogenerated choice
{1}
    }}
    reply->deleteLater();
}}
"""

def lowerFirst(s):
    return s[0].lower()+s[1:]

def upperFirst(s):
    return s[0].upper()+s[1:]

def Snake2Camel(SnakeCase,upper):
    rv = "".join(map(lambda item: item[0].upper() + item[1:], SnakeCase.split("_")))
    if not upper:
        return rv[0].lower() + rv[1:]
    else:
        return rv

#http://refactormycode.com/codes/675-camelcase-to-camel-case-python-newbie
def Camel2Snake(Camel):
    if Camel is None:
        return None
    pattern = re.compile('([A-Z][A-Z][a-z])|([a-z][A-Z])')
    return pattern.sub(lambda m: m.group()[:1] + "_" + m.group()[1:].lower(), Camel)

#role_type_defs.append("HOME_TIMELINE")
#role_type_defs.append("FRIENDS_TIMELINE")

urlrx = re.compile("^URL:(.*)$")
formatrx = re.compile("^Format:(.*)$")
methodrx = re.compile("^Method:(.*)$")
limitrx  = re.compile("^Limit:(.*)$")
authrx   = re.compile("^AuthRequired:(.*)$")
paramsrx = re.compile("^Params:(.*)$")
xmlrtrx  = re.compile("^XMLRoot:(.*)$")
pagerx  = re.compile("^Pagination:(.*)$")

def getMethod(s):
    if not s.find("DELETE") < 0:
        return "DELETE"
    elif not s.find("CREATE") < 0:
        return "CREATE"
    elif not s.find("PUT") < 0:
        return "PUT"
    elif not s.find("POST") < 0:
        return "POST"
    else:
        return "GET"

def getLimit(s):
    if not s.find("true") < 0:
        return True
    else:
        return False

def getObject(f):
    url=""
    method="GET"
    format=[]
    limit=False
    auth=False
    params=[]
    xmlroot=""
    pagination=False
    for l in f:
        m = urlrx.match(l)
        if m:
            url=m.group(1)
            continue
        m = formatrx.match(l)
        if m:
            format=m.group(1).split(",")
            continue
        m = methodrx.match(l)
        if m:
            method = getMethod(m.group(1))
            continue
        m = limitrx.match(l)
        if m:
            limit=getLimit(m.group(1))
            continue
        m = authrx.match(l)
        if m:
            auth=getLimit(m.group(1))
            continue
        m = paramsrx.match(l)
        if m:
            params=m.group(1).split(",")
            continue
        m = xmlrtrx.match(l)
        if m:
            xmlroot=m.group(1)
            continue
        m = pagerx.match(l)
        if m:
            pagination=(m.group(1)=="True")
            continue
    return {'url':url,'method':method, 'format':format, 'limit':limit, 'auth':auth, 'params':params, 'xmlroot':xmlroot, 'pagination':pagination}

def getParamsStr(obj):
    cppparams = []
    for key in obj['params']:
        if key == "":
            continue
        varname = fixIdentifier(key)
        if type_dic.has_key(key):
            if type_dic[key] == 'QString':
                cppparams.append("const QString& "+varname)
            else:
                cppparams.append(type_dic[key] + " " + varname)
        else:
            cppparams.append("const QString& "+varname)
    return ", ".join(cppparams)

def strlize(key):
    varname=fixIdentifier(key)
    if type_dic.has_key(key):
        if type_dic[key] == 'QString':
            return varname
        elif type_dic[key] == 'quint64' or type_dic[key] == 'qint64' or type_dic[key] == 'int':
            return "QString::number({0},10)".format(varname)
        elif type_dic[key] == 'Color' or type_dic[key] == 'QDateTime' or type_dic[key] == 'QUrl':
            return "{0}.toString()".format(varname)
    else:
        return varname

def decide(key):
    if type_dic.has_key(key):
        key = fixIdentifier(key)
        print key
        if type_dic[key] == 'QString':
            return "if({0}!=\"\")".format(key)
        elif type_dic[key] == 'quint64' or type_dic[key] == 'qint64' or type_dic[key] == 'int':
            return "if({0}!=0)".format(key)
        elif type_dic[key] == 'Color':
            return "if({0}.toString()!=\"\")".format(key)
        elif type_dic[key] == 'QDateTime':
            return "if({0}!=QDateTime())".format(key)
        elif type_dic[key] == 'QUrl':
            return "if({0}!=QUrl())".format(key)
    else:
        key = fixIdentifier(key)
        return "if({0}!=\"\")".format(key)

def getFuncObj(obj,methodname):
    get_tmpl="""
    QString requestStr("{0}");
    QUrl requestUrl(requestStr);
    //addQueryItem
{1}
    QNetworkRequest req(requestUrl.toString());
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), {2});
    """
    post_tmpl="""
    QString requestStr("{0}");
    QUrl requestUrl(requestStr);
    //addQueryItem
{1}
    QByteArray _query_(requestUrl.encodedQuery());
    QNetworkRequest req(requestUrl.toString(QUrl::RemoveQuery));
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), {2});
    """
    lines=""
    url=obj['url']
    suffixrx=re.compile("\.format$")
    url=suffixrx.sub("/",url)
    if obj['method'] == "GET" or obj['method'] == "DELETE":
        q=[]
        prx = re.compile("/user/")
        url=prx.sub("/\"+m_userid+\"/",url)
        for p in obj['params']:
            if p == "":
                continue
            strlized = strlize(p)
            prx = re.compile("/"+p+"/")
            m=prx.search(url)
            if m:
#                print "hogehoge"
                url=prx.sub("/\"+"+strlized+"+\"/",url)
            else:
                q.append("    {2} requestUrl.addQueryItem(\"{0}\",{1});".format(p,strlized,decide(p)))
        rx=re.compile("/$")
        url=rx.sub(".xml",url)        
        lines = get_tmpl.format(url, "\n".join(q), Camel2Snake(methodname).upper())
        if obj['method'] == "GET":
            lines = lines + "issueGetRequest(req);\n"
        else:
            lines = lines + "issueDeleteRequest(req);\n"
    elif obj['method'] == "POST" or obj['method'] == "PUT":
        if 'image' in obj['params']:
            pass
        else:
            q=[]
            prx = re.compile("/user/")
            url=prx.sub("/\"+m_userid+\"/",url)
            for p in obj['params']:
                if p == "":
                    continue
                strlized = strlize(p)
                prx = re.compile("/"+p+"/")
                m=prx.search(url)
                if m:
#                    print "hogehoge"
                    url=prx.sub("/\"+"+strlized+"+\"/",url)
                else:
                    q.append("    {2} requestUrl.addQueryItem(\"{0}\",{1});".format(p,strlized,decide(p)))
            rx=re.compile("/$")
            url=rx.sub(".xml",url)
            lines = post_tmpl.format(url, "\n".join(q), Camel2Snake(methodname).upper())
            if obj['method'] == "POST":
                lines = lines + "issuePostRequest(req,_query_);\n"
            else:
                lines = lines + "issuePutRequest(req,_query_);\n"
    else:
        pass
    return {'args':getParamsStr(obj), 'lines':lines}

def processFile(path):
    f = open(path, 'r')
    filename = os.path.basename(path) 
    methodname = fixIdentifier(os.path.splitext(filename)[0])
    obj=getObject(f)
    xmlroot = fixIdentifier(obj['xmlroot'])
    if xmlroot == "":
        return
    if "xml" not in obj['format']:
        return
    role_type = Camel2Snake(methodname).upper()
    role_type_defs.append(role_type)
    func_obj = getFuncObj(obj,methodname)
    invoke_defs.append("    void "+lowerFirst(methodname)+"("+func_obj['args']+");")
    invoke_impls.append("void Petrel::"+lowerFirst(methodname)+"("+func_obj['args']+"){\n"+ func_obj['lines'] + "\n}\n")
    #print func_obj['lines']
    if obj['pagination']:
        params = xmlroot+"_t& "+xmlroot+", quint64 next, quint64 prev"
        signal_defs.append("    void "+lowerFirst(methodname)+"Received("+params+");")
    else:
        params = xmlroot+"_t& "+xmlroot
        signal_defs.append("    void "+lowerFirst(methodname)+"Received("+params+");")
#invoke_impl
    if obj['method'] == "GET":
        pass
#recv_case
    choice = "        case "+ role_type +":\n        {\n"
    choice = choice + "          " + xmlroot + "_t " + xmlroot[0] +"(doc.documentElement());\n"
    choice = choice + "          emit " + lowerFirst(methodname)+"Received(" + xmlroot[0] + ");\n"
    choice = choice + "          break;\n"
    choice = choice + "        }\n"
    recv_case.append(choice)

lines = commands.getoutput("ls apis/*.api").split("\n")
for path in lines:
    processFile(path)


f=open("petrel.h",'w')
f.write(HEADER_STR.format(",".join(role_type_defs),"\n".join(invoke_defs),"\n".join(signal_defs)))
f.close()

f=open("petrel.cpp",'w')
f.write(IMPL_STR.format("".join(invoke_impls), "".join(recv_case)))
f.close()
