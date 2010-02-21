#ifndef TESTAPP_H
#define TESTAPP_H

#include <QCoreApplication>
#include "../petrel_types.h"
class Petrel;

class TestApp : public QCoreApplication
{
Q_OBJECT
public:
    TestApp(int &argc, char **argv);


signals:

public slots:
    void homeTimelineReceived(statuses_t& home_timeline);
private:
    Petrel *m_petrel;
};

#endif // TESTAPP_H
