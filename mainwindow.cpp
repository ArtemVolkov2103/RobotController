#include "mainwindow.h"
#include "qlabel.h"
#include "qslider.h"
#include <QPushButton>
#include <QWidget>
#include "ui_mainwindow.h"

QList<QLabel *> servoNum;
QList<QLabel *> sliderValueLabels;
QList<QPushButton *> buttonsMin;
QList<QPushButton *> buttonsMax;
QList<QPushButton *> buttonsDef;
QList<QPushButton *> buttonsRes;
QList<QSlider *> sliders;
QList<int> sliderValues(6);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("RobotController"));

    for (int i = 0; i < 6; ++i){
        servoNum << new QLabel(this);
        sliderValueLabels << new QLabel(this);

        buttonsMin << new QPushButton(this);
        buttonsMax << new QPushButton(this);
        buttonsDef << new QPushButton(this);
        buttonsRes << new QPushButton(this);
        sliders << new QSlider(this);
        sliders.at(i)->setOrientation(Qt::Horizontal);
    }
    for (int i = 0; i < 6; ++i){
        servoNum.at(i)->setText("Servo " + QString::number(i));
        servoNum.at(i)->setGeometry(10, i*30+25, 50, 10); //длинна от 10 до 60px

        buttonsMin.at(i)->setText("MIN");
        buttonsMin.at(i)->setGeometry(60, i*30+20, 35, 20);
        buttonsMax.at(i)->setText("MAX");
        buttonsMax.at(i)->setGeometry(95, i*30+20, 35, 20);
        buttonsDef.at(i)->setText("DEF");
        buttonsDef.at(i)->setGeometry(130, i*30+20, 35, 20);
        buttonsRes.at(i)->setText("RES");
        buttonsRes.at(i)->setGeometry(165, i*30+20, 35, 20);

        sliders.at(i)->setGeometry(210, i*30+25, 350, 10);
        sliderValueLabels.at(i)->setText(QString::number(sliderValues.at(i)));
        sliderValueLabels.at(i)->setGeometry(570, i*30+25, 50, 10);
    }
    connect(sliders.at(0),SIGNAL(valueChanged(int)),this,SLOT(slider0value(int))); //TODO - связать сигнал слайдера с


}
void MainWindow::slider0value(int val){
    sliderValueLabels.at(0)->setText(QString::number(val));
    sliderValues[0] = val;
}



MainWindow::~MainWindow()
{
    delete ui;
}

