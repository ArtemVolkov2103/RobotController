#include "mainwindow.h"

#include <QApplication>
#include <secondwindow.h>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*QFile file(":/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromUtf8(file.readAll());
    a.setStyleSheet(styleSheet);*/

    QFile file(":/stylesheet.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();
    a.setStyleSheet(styleSheet);
    //ModelSelectionForm modelSelectionForm;
    //modelSelectionForm.show();
    //secondwindow s;
    //s.show();
    MainWindow w;
    w.show();
    return a.exec();
}
