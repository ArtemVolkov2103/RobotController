#include "secondwindow.h"
#include "ui_secondwindow.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

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
#include <QLineEdit>


int servoCount = 6;
QList<QLineEdit *> servoNum;
QList<QLabel *> sliderValueLabels;
QList<QPushButton *> buttonsMin;
QList<QPushButton *> buttonsMax;
QList<QPushButton *> buttonsDef;
QList<QPushButton *> buttonsRes;
QList<QSlider *> sliders;
QList<int> sliderValues(20);
bool isConnected=false;
QSerialPort serialPort;
int StartPos[12] = {2000,2000,1130, 1250, 1256, 1176,  1200,1850,1280, 1500,600,1800};
QList<QList<int>> ValuesFromText;

secondwindow::secondwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::secondwindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Дипломная работа 'RobotController' "));

    autoButton = new QPushButton("A", this);
    oneButton = new QPushButton("1", this);
    leftButton = new QPushButton("<", this);
    rightButton = new QPushButton(">", this);
    textValues = new QPlainTextEdit("",this);
    QList<QLabel *> rightLabels;
    comPortName = new QComboBox(this);
    baudValuesBox = new QComboBox(this);
    minServoVal = new QLineEdit(this);
    maxServoVal = new QLineEdit(this);
    connectButton = new QPushButton("", this);
    QPalette p(connectButton->palette());

    loadButton = new QPushButton("Load", this);
    saveButton = new QPushButton("Save", this);
    recordButton = new QPushButton("Record", this);
    deleteButton = new QPushButton("Delete", this);
    clearButton = new QPushButton("Clear", this);



    for(int i = 0; i<20; i++){
        sliders << new QSlider(this);
        sliders.at(i)->setOrientation(Qt::Horizontal);
        sliders.at(i)->setMaximum(2500);
        sliders.at(i)->setMinimum(600);
        sliders.at(i)->setVisible(false);
    }

    connect(sliders.at(0),SIGNAL(valueChanged(int)),this,SLOT(slider0value(int) ));
    connect(sliders.at(1),SIGNAL(valueChanged(int)),this,SLOT(slider1value(int)));
    connect(sliders.at(2),SIGNAL(valueChanged(int)),this,SLOT(slider2value(int)));
    connect(sliders.at(3),SIGNAL(valueChanged(int)),this,SLOT(slider3value(int)));
    connect(sliders.at(4),SIGNAL(valueChanged(int)),this,SLOT(slider4value(int)));
    connect(sliders.at(5),SIGNAL(valueChanged(int)),this,SLOT(slider5value(int)));
    connect(sliders.at(6),SIGNAL(valueChanged(int)),this,SLOT(slider6value(int)));
    connect(sliders.at(7),SIGNAL(valueChanged(int)),this,SLOT(slider7value(int)));
    connect(sliders.at(8),SIGNAL(valueChanged(int)),this,SLOT(slider8value(int)));
    connect(sliders.at(9),SIGNAL(valueChanged(int)),this,SLOT(slider9value(int)));
    connect(sliders.at(10),SIGNAL(valueChanged(int)),this,SLOT(slider10value(int)));
    connect(sliders.at(11),SIGNAL(valueChanged(int)),this,SLOT(slider11value(int)));
    connect(sliders.at(12),SIGNAL(valueChanged(int)),this,SLOT(slider12value(int)));
    connect(sliders.at(13),SIGNAL(valueChanged(int)),this,SLOT(slider13value(int)));
    connect(sliders.at(14),SIGNAL(valueChanged(int)),this,SLOT(slider14value(int)));
    connect(sliders.at(15),SIGNAL(valueChanged(int)),this,SLOT(slider15value(int)));
    connect(sliders.at(16),SIGNAL(valueChanged(int)),this,SLOT(slider16value(int)));
    connect(sliders.at(17),SIGNAL(valueChanged(int)),this,SLOT(slider17value(int)));
    connect(sliders.at(18),SIGNAL(valueChanged(int)),this,SLOT(slider18value(int)));
    connect(sliders.at(19),SIGNAL(valueChanged(int)),this,SLOT(slider19value(int)));

    findAvailableComPorts();
    /* Инициализируем Таймер и подключим его к слоту,
         * который будет обрабатывать timeout() таймера
         * */
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(50);
}

void secondwindow::recieveData(int count){
    servoCount = count;
    this->setFixedSize(700,(200+servoCount*30));

    for (int i = 0; i < servoCount; ++i){
        servoNum << new QLineEdit(this);
        sliderValueLabels << new QLabel(this);

        buttonsMin << new QPushButton(this);
        buttonsMax << new QPushButton(this);
        buttonsDef << new QPushButton(this);
        buttonsRes << new QPushButton(this);

    }
    for (int i = 0; i < servoCount; ++i){
        //servoNum.at(i)->moveCursor (QTextCursor::End);
        servoNum.at(i)->setText("Servo " + QString::number(i));
        //servoNum.at(i)->insertPlainText("Servo " + QString::number(i));
        servoNum.at(i)->setGeometry(10, i*30+20, 80, 20); //длинна от 10 до 90px

        buttonsMin.at(i)->setText("MIN");
        buttonsMin.at(i)->setGeometry(90, i*30+20, 35, 20);
        buttonsMax.at(i)->setText("MAX");
        buttonsMax.at(i)->setGeometry(125, i*30+20, 35, 20);
        buttonsDef.at(i)->setText("DEF");
        buttonsDef.at(i)->setGeometry(160, i*30+20, 35, 20);
        buttonsRes.at(i)->setText("RES");
        buttonsRes.at(i)->setGeometry(195, i*30+20, 35, 20);

        sliders.at(i)->setVisible(true);
        sliders.at(i)->setGeometry(240, i*30+25, 350, 10);
        sliderValueLabels.at(i)->setText(QString::number(sliderValues.at(i)) + " microseconds");
        sliderValueLabels.at(i)->setGeometry(600, i*30+25, 110, 10);
    }
    autoButton->setGeometry(10, servoCount*30+25, 20, 20);
    connect(autoButton,SIGNAL(clicked()),this,SLOT(autoButtonClick() ));

    oneButton->setGeometry(10, (servoCount+1)*30+25, 20, 20);
    connect(oneButton,SIGNAL(clicked()),this,SLOT(oneButtonClick() ));

    leftButton->setGeometry(10, (servoCount+2)*30+25, 20, 20);
    connect(leftButton,SIGNAL(clicked()),this,SLOT(leftButtonClick() ));

    rightButton->setGeometry(10, (servoCount+3)*30+25, 20, 20);
    connect(rightButton,SIGNAL(clicked()),this,SLOT(rightButtonClick() ));

    textValues->setGeometry(40, servoCount*30+25, 400, 120);

    comPortName->setGeometry(450, servoCount*30+25, 70, 20);
    //comPortName->addItems({"com3", "com5"});
    baudValuesBox->setGeometry(450, (servoCount+1)*30+25, 70, 20);
    baudValuesBox->addItems({"9600", "115200"});
    minServoVal->setGeometry(450, (servoCount+2)*30+25, 70, 20);
    minServoVal->setText("600");
    maxServoVal->setGeometry(450, (servoCount+3)*30+25, 70, 20);
    maxServoVal->setText("2500");
    connectButton->setGeometry(530, servoCount*30+25, 100, 120);
    connectButton->setStyleSheet("border-radius: 10px;""background-color:rgba(255, 0, 0, 255)");
    connect(connectButton,SIGNAL(clicked()),this,SLOT(connectButtonClick() ));

    int btnWidth = 50;
    loadButton->setGeometry(10, (servoCount+4)*30+25, btnWidth, 20);
    connect(loadButton,SIGNAL(clicked()),this,SLOT(loadButtonClick() ));

    saveButton->setGeometry(btnWidth+10, (servoCount+4)*30+25, btnWidth, 20);
    connect(saveButton,SIGNAL(clicked()),this,SLOT(saveButtonClick() ));

    recordButton->setGeometry(btnWidth*2+10, (servoCount+4)*30+25, btnWidth, 20);
    connect(recordButton,SIGNAL(clicked()),this,SLOT(recordButtonClick() ));

    deleteButton->setGeometry(btnWidth*3+10, (servoCount+4)*30+25, btnWidth, 20);
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(deleteButtonClick() ));

    clearButton->setGeometry(btnWidth*4+10, (servoCount+4)*30+25, btnWidth, 20);
    connect(clearButton,SIGNAL(clicked()),this,SLOT(clearButtonClick() ));
}

void secondwindow::findAvailableComPorts(){
    comPortName->clear();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        comPortName->addItem(serialPortInfo.portName());
    }

}

void secondwindow::autoButtonClick()
{
    serialPort.open(QIODevice::ReadWrite);
    //if(serialPort.opwen(QIODevice::ReadWrite)){
    if(sliderValues.at(0) == 0){
        for(int i=0; i<servoCount; i++){//если значение со слайдера еще не пришло
            sliderValues[i] = StartPos[i];
        }
    }
    for(int i=0; i<servoCount; i++){
        serialPort.write(QString::number(sliderValues[i]).toUtf8());
        serialPort.write(",");
    }
    serialPort.write("@");

    serialPort.waitForBytesWritten(); // ждем пока дойдет

    // и не знаю с чем тут связано, но, чтобы сообщение дошло
    // надо обязательно прочитать не пришло ли нам чего в ответ
    //
    // функция waitForReadyRead(10) проверят не появилось
    // в ближайшие 10 миллисекунд чего-нибудь в ответ
    while (serialPort.waitForReadyRead(10)) {
        // и если появилось мы просто это читаем в пустоту
        serialPort.readAll();
        // сам while необходим для того что ответ приходит порциями
        // и мы хотим считать все что отправилось
    }
    serialPort.close();
}
void secondwindow::oneButtonClick()
{

}
void secondwindow::leftButtonClick()
{

}
void secondwindow::rightButtonClick()
{

}
void secondwindow::connectButtonClick()
{
    if (!serialPort.isOpen()) {
        findAvailableComPorts();
        // указали имя к какому порту будем подключаться
        serialPort.setPortName(this->comPortName->currentText());
        qDebug() << comPortName->currentText();
        // указали скорость
        serialPort.setBaudRate(QSerialPort::Baud9600);
        // пробуем подключится
        if (!serialPort.open(QIODevice::ReadWrite)) {
            // если подключится не получится, то покажем сообщение с ошибкой
            QMessageBox::warning(this, "Ошибка подключения", "Не удалось подключится к порту.");
            isConnected = false;
            connectButton->setStyleSheet("border-radius: 10px;""background-color:rgba(255, 0, 0, 255)");
            serialPort.close();
            return;
        }
        else {
            connectButton->setStyleSheet("border-radius: 10px;""background-color:rgba(0, 255, 0, 255)");
            isConnected = true;
        }
    }
    else QMessageBox::warning(this, "Ошибка подключения", "Уже есть существующее подключение");


}
void secondwindow::loadButtonClick()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    QString::fromUtf8("Открыть файл"),
                                                    QDir::fromNativeSeparators("C:/1 УЧЕБА/РОБОТ 11.2020/РОБОТ/beepod координаты"),
                                                    "Text (*.txt *.TXT)");
    QFile file(fileName);//путь до файла
    QStringList LIST;

    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        textValues->clear();
        ValuesFromText.clear();
        int j=0;//количество строк в файле
        while(!file.atEnd())
        {
            //читаем строку
            QString str = file.readLine().trimmed();//trimmed удаляет \n в конце строки

            //Делим строку на слова разделенные пробелом
            QStringList lst = str.split(",");
            LIST.append(lst);
                // выводим значения
            QList<int> list;
            for (int i=0;i < lst.length()-1;i++) {
                list << lst.at(i).toInt();
                textValues->insertPlainText(lst.at(i));

            }
            textValues->insertPlainText("\n");
            ValuesFromText.append(list);
            j++;
        }
        for(int i=0; i < servoCount; i++){
            sliders.at(i)->setSliderPosition(ValuesFromText[0][i]);
        }
        LIST.clear();
    }

    else
    {
        QMessageBox::warning(this, "Ошибка при открытии файла", "Не удалось открыть файл");
    }
}
void secondwindow::saveButtonClick()
{

}
void secondwindow::recordButtonClick()
{

}
void secondwindow::deleteButtonClick()
{

}
void secondwindow::clearButtonClick()
{

}

void secondwindow::slotTimerAlarm()// Ежесекундно обновляем данные
{
    /*serialPort.open(QIODevice::ReadWrite);
    //if(serialPort.open(QIODevice::ReadWrite)){
    if(sliderValues.at(0) == 0){
        for(int i=0; i<servoCount; i++){//если значение со слайдера еще не пришло
            sliderValues[i] = StartPos[i];
        }
    }
    for(int i=0; i<servoCount; i++){
        serialPort.write(QString::number(sliderValues[i]).toUtf8());
        serialPort.write(",");
    }
    serialPort.write("@");

    serialPort.waitForBytesWritten(); // ждем пока дойдет

    // и не знаю с чем тут связано, но, чтобы сообщение дошло
    // надо обязательно прочитать не пришло ли нам чего в ответ
    //
    // функция waitForReadyRead(10) проверят не появилось
    // в ближайшие 10 миллисекунд чего-нибудь в ответ
    while (serialPort.waitForReadyRead(10)) {
        // и если появилось мы просто это читаем в пустоту
        serialPort.readAll();
        // сам while необходим для того что ответ приходит порциями
        // и мы хотим считать все что отправилось
    }
    serialPort.close();*/

}

void secondwindow::slider0value(int val){
    sliderValueLabels.at(0)->setText(QString::number(val) + " microseconds");
    sliderValues[0] = val;
}
void secondwindow::slider1value(int val){
    sliderValueLabels.at(1)->setText(QString::number(val));
    sliderValues[1] = val;
}
void secondwindow::slider2value(int val){
    sliderValueLabels.at(2)->setText(QString::number(val));
    sliderValues[2] = val;
}
void secondwindow::slider3value(int val){
    sliderValueLabels.at(3)->setText(QString::number(val));
    sliderValues[3] = val;
}
void secondwindow::slider4value(int val){
    sliderValueLabels.at(4)->setText(QString::number(val));
    sliderValues[4] = val;
}
void secondwindow::slider5value(int val){
    sliderValueLabels.at(5)->setText(QString::number(val));
    sliderValues[5] = val;
}
void secondwindow::slider6value(int val){
    sliderValueLabels.at(6)->setText(QString::number(val));
    sliderValues[6] = val;
}
void secondwindow::slider7value(int val){
    sliderValueLabels.at(7)->setText(QString::number(val));
    sliderValues[7] = val;
}
void secondwindow::slider8value(int val){
    sliderValueLabels.at(8)->setText(QString::number(val));
    sliderValues[8] = val;
}
void secondwindow::slider9value(int val){
    sliderValueLabels.at(9)->setText(QString::number(val));
    sliderValues[9] = val;
}
void secondwindow::slider10value(int val){
    sliderValueLabels.at(9)->setText(QString::number(val));
    sliderValues[9] = val;
}
void secondwindow::slider11value(int val){
    sliderValueLabels.at(9)->setText(QString::number(val));
    sliderValues[9] = val;
}
void secondwindow::slider12value(int val){
    sliderValueLabels.at(9)->setText(QString::number(val));
    sliderValues[9] = val;
}
void secondwindow::slider13value(int val){
    sliderValueLabels.at(9)->setText(QString::number(val));
    sliderValues[9] = val;
}
void secondwindow::slider14value(int val){
    sliderValueLabels.at(9)->setText(QString::number(val));
    sliderValues[9] = val;
}
void secondwindow::slider15value(int val){
    sliderValueLabels.at(9)->setText(QString::number(val));
    sliderValues[9] = val;
}
void secondwindow::slider16value(int val){
    sliderValueLabels.at(9)->setText(QString::number(val));
    sliderValues[9] = val;
}
void secondwindow::slider17value(int val){
    sliderValueLabels.at(9)->setText(QString::number(val));
    sliderValues[9] = val;
}
void secondwindow::slider18value(int val){
    sliderValueLabels.at(9)->setText(QString::number(val));
    sliderValues[9] = val;
}
void secondwindow::slider19value(int val){
    sliderValueLabels.at(9)->setText(QString::number(val));
    sliderValues[9] = val;
}

secondwindow::~secondwindow()
{
    delete ui;
}
