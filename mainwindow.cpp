#include "mainwindow.h"
#include "qlabel.h"
#include "qslider.h"
#include <QPushButton>
#include <QWidget>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QColor>
#include <Qt>

#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QFile>
#include <QtGui>
#include <QFileDialog>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QGridLayout>

#include <QStyle>
#include <QScreen>

#include "secondwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Выберите модель робота"));
    this->setFixedSize(450, 400);
    s = new secondwindow();

        sixServoModelButton = new QPushButton("", this);
        sixServoModelButton->setGeometry(10, 10, 200, 300);
        QPixmap pixmap("C:/Users/ThinkBook/Pictures/6 servo.png");
        QIcon ButtonIcon(pixmap);
        sixServoModelButton->setIcon(ButtonIcon);
        sixServoModelButton->setIconSize(sixServoModelButton->size());
        connect(sixServoModelButton,SIGNAL(clicked()),this,SLOT(on_sixServoModelButton_clicked() ));

        eigthServoModelButton = new QPushButton("", this);
        eigthServoModelButton->setGeometry(220, 10, 200, 300);
        QPixmap pixmap2("C:/Users/ThinkBook/Downloads/Biped-humanoid-robot-KHR-2.png");
        QIcon ButtonIcon2(pixmap2);
        eigthServoModelButton->setIcon(ButtonIcon2);
        eigthServoModelButton->setIconSize(eigthServoModelButton->size());
        connect(eigthServoModelButton,SIGNAL(clicked()),this,SLOT(on_eigthServoModelButton_clicked() ));

        anotherModelButton = new QPushButton("Другая модель робота", this);
        anotherModelButton->setGeometry(25, 320, 400, 50);
        connect(anotherModelButton,SIGNAL(clicked()),this,SLOT(on_anotherModelButton_clicked() ));

        connect(sixServoModelButton, SIGNAL(sendData(int)), this, SLOT(on_sixServoModelButton_clicked()));
        connect(this, SIGNAL(sendData(int)), s, SLOT(recieveData(int)));
}


MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::setServoCount(int count) { servoCount = count;}
void MainWindow::on_sixServoModelButton_clicked(){

    emit sendData(6);
    s->show();
    this->hide();
}
void MainWindow::on_eigthServoModelButton_clicked(){
    emit sendData(8);
    s->show();
    this->close();
}
void MainWindow::on_anotherModelButton_clicked(){
    emit sendData(4);
    s->show();
    this->close();
}

