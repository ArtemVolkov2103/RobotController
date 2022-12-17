#include "mainwindow.h"

#include <QApplication>
#include <secondwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //ModelSelectionForm modelSelectionForm;
    //modelSelectionForm.show();
    //secondwindow s;
    //s.show();
    MainWindow w;
    w.show();
    return a.exec();
}
