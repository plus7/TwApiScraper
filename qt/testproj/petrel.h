#ifndef PETREL_H
#define PETREL_H

#include <QObject>
#include <QtNetwork>

enum ATTR_TYPE {
    ATTR_ROLE
};

enum ROLE_TYPE {
    ROLE_HOME_TIMELINE,
    ROLE_HOGE
};

class Petrel : public QObject
{
    Q_OBJECT
public:
    Petrel(const QString& id, const QString& pass);
    virtual ~Petrel();
    void homeTimeline();
    void issueGetRequest(QNetworkRequest& req);

//signals:
    //void homeTimelineReceived(home_timeline_t& home_timeline);

public slots:
    void replyFinished( QNetworkReply* );
private:
    QNetworkAccessManager *m_manager;
    QString m_id;
    QString m_pass;
};

#endif // PETREL_H
