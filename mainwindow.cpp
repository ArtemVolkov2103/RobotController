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
    this->setFixedSize(430, 400);
    /*QPixmap background;
    background.load("C:/Users/ThinkBook/Downloads/background.jpg");
        //scaling the image, optional. See the documentation for more options
    background = background.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);*/
    s = new secondwindow();

    sixServoModelButton = new QPushButton("", this);
    sixServoModelButton->setGeometry(10, 10, 200, 300);
    QPixmap pixmap("C:/Users/ThinkBook/Pictures/6 servo.png");
    QIcon ButtonIcon(pixmap);
    sixServoModelButton->setIcon(ButtonIcon);
    sixServoModelButton->setIconSize(sixServoModelButton->size());
    connect(sixServoModelButton,SIGNAL(clicked()),this,SLOT(on_sixServoModelButtonClicked()));

    eigthServoModelButton = new QPushButton("", this);
    eigthServoModelButton->setGeometry(220, 10, 200, 300);
    QPixmap pixmap2("C:/Users/ThinkBook/Downloads/Biped-humanoid-robot-KHR-2.png");
    QIcon ButtonIcon2(pixmap2);
    eigthServoModelButton->setIcon(ButtonIcon2);
    eigthServoModelButton->setIconSize(eigthServoModelButton->size());
    connect(eigthServoModelButton,SIGNAL(clicked()),this,SLOT(on_eigthServoModelButtonClicked()));

    anotherModelButton = new QPushButton("Другая модель робота", this);
    anotherModelButton->setGeometry(10, 320, 200, 50);
    anotherModelButton->setDisabled(true);
    anotherModelButton->setObjectName("anotherModelButton");

    connect(anotherModelButton,SIGNAL(clicked()),this,SLOT(on_anotherModelButtonClicked()));
    labelForServoCount = new QLabel("Число сервоприводов:", this);
    labelForServoCount->setObjectName("whiteTextLabels");
    labelForServoCount->setGeometry(220, 320, 200, 25);
    anotherModelServoCount = new QLineEdit("0",this);
    anotherModelServoCount->setGeometry(220, 345, 200, 25);
    anotherModelServoCount->setObjectName("servoNum");
    connect(anotherModelServoCount,SIGNAL(textChanged(QString)),this,SLOT(on_anotherModelServoCountChanged()));

    connect(this, SIGNAL(sendData(int)), s, SLOT(recieveData(int)));
}


MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::setServoCount(int count) { servoCount = count;}
void MainWindow::on_sixServoModelButtonClicked(){

    emit sendData(6);
    s->show();
    this->hide();
}
void MainWindow::on_eigthServoModelButtonClicked(){
    emit sendData(8);
    s->show();
    this->close();
}

void MainWindow::on_anotherModelServoCountChanged(){
    if(anotherModelServoCount->text().toInt()<=20 && anotherModelServoCount->text().toInt() > 0)
        anotherModelButton->setDisabled(false);
    else{
        QMessageBox::warning(this, "Ошибка ввода", "Проверьте, что количество сервоприводов указано верно. Допустимые значения от 1 до 20");
        anotherModelButton->setDisabled(true);
    }
}
void MainWindow::on_anotherModelButtonClicked(){
    emit sendData(anotherModelServoCount->text().toUInt());
    s->show();
    this->close();
}

