#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include<QSettings>
#include<QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("1");
    QCoreApplication::setApplicationName("DBLB");
    QSettings settings;

    //创建窗体
    MainWindow w;
    w.show();
    return a.exec();
}
