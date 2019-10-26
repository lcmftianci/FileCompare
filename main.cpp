#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include <QDir>
#include <QTextCodec>
#include <QDebug>
#include <QFile>

//load stylesheet
void loadStyleSheet(QString strPath)
{
    QFile file(strPath);
    file.open(QIODevice::ReadOnly);
    QString cstyle = file.readAll();
    qApp->setStyleSheet(cstyle);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << QDir::currentPath();
    QString strCssPath = QDir::currentPath() + "/stylesheet/newBlack.css";
    loadStyleSheet(strCssPath);
    MainWindow w;
    w.show();

    return a.exec();
}
