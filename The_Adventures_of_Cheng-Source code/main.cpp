#include "startscene.h"

#include <QApplication>

int main(int argc, char *argv[]) //启动程序
{
    QApplication a(argc, argv);
    StartScene w;
    w.show();
    return a.exec();
}
