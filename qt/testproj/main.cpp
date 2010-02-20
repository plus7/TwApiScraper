#include <QtCore/QCoreApplication>
#include "petrel.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Petrel petrel("xxxxxxxx","xxxxxxxx");
    petrel.homeTimeline();
    return a.exec();
}
