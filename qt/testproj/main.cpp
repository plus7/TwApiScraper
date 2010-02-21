#include <QtCore/QCoreApplication>
#include "testapp.h"
#include "petrel.h"
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    TestApp a(argc, argv);
    return a.exec();
}
