#include <QtCore/QCoreApplication>
#include "petrel.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc<3) return -1;
    Petrel petrel(argv[1],argv[2]);
    petrel.homeTimeline();
    return a.exec();
}
