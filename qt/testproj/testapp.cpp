#include <QtCore>
#include "testapp.h"
#include "petrel.h"
#include <QTextStream>
TestApp::TestApp(int &argc, char **argv) :
  QCoreApplication(argc, argv)
{
    //if(argc<3) return;
    QString id,pass;
    QFile data("idpw");
    if (data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        in >> id >> pass;
        m_petrel = new Petrel(id,pass);
        connect(m_petrel, SIGNAL(homeTimelineReceived(statuses_t&)),
                this, SLOT(homeTimelineReceived(statuses_t&)));
        //m_petrel->homeTimeline(0,0,0,0);
        m_petrel->update(tr("てすと"),0,"","");
    }
}

void TestApp::homeTimelineReceived(statuses_t& s){
    qDebug() << "duhfisuhiu";
    foreach(QSharedPointer<status_t> ptr, s.status){
        qDebug() << ptr->text;
        qDebug() << ptr->user->profile_background_color.getColor();
    }
}
