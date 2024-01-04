#include "yonghu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    yonghu *yonghu1 = new yonghu;
    yonghu1->show();
    return a.exec();
}
