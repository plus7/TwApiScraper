#include <QtCore/QCoreApplication>
#include "petrel.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Petrel petrel("plus7","ylxzfuhdT");
    petrel.homeTimeline();
    return a.exec();
}
