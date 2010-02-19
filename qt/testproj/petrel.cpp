#include "petrel.h"

Petrel::Petrel(const QString& id, const QString& pass)
        :m_manager(new QNetworkAccessManager( this )),
        m_id(id),m_pass(pass)
{
    connect(m_manager,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(replyFinished(QNetworkReply*)));
}

Petrel::~Petrel()
{
    //delete m_manager;
}

//HTTP
void Petrel::issueGetRequest(QNetworkRequest& req){
    QByteArray auth = m_id.toUtf8() + ":" + m_pass.toUtf8();
    req.setRawHeader( "Authorization", auth.toBase64().prepend( "Basic " ) );
    m_manager->get(req);
}

void Petrel::issuePostRequest(QNetworkRequest& req, QByteArray& data, bool multipart){

}

void Petrel::issuePutRequest(QNetworkRequest& req, QByteArray& data){

}

void Petrel::issueDeleteRequest(QNetworkRequest& req){

}

void Petrel::homeTimeline()
{
    QString requestStr("http://api.twitter.com/1/statuses/home_timeline.xml");
    //replace /id/ /list_id/
    QUrl requestUrl(requestStr);
    //addQueryItem
    QNetworkRequest req(requestStr);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), ROLE_HOME_TIMELINE);
    issueGetRequest(req);
}

void Petrel::replyFinished(QNetworkReply *reply)
{
    qDebug() << "hoge";
    QNetworkRequest request = reply->request();
    QString replyStr( reply->readAll() );
    int role = request.attribute( (QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE) ).toInt();
    switch(role){
        case ROLE_HOME_TIMELINE:
        {
            qDebug() << replyStr.length();
            QString hoge = replyStr.left(replyStr.length());
            QDomDocument doc;
            doc.setContent(replyStr);
            qDebug() << doc.documentElement().tagName();
            statuses_t s(doc.documentElement());
            foreach(QSharedPointer<status_t> ptr, s.status){
                qDebug() << ptr->text;
                qDebug() << ptr->user->profile_background_color.getColor();
            }

            emit homeTimelineReceived(s);
        }
    }
    reply->deleteLater();
}
