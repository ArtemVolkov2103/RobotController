#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "secondwindow.h"

#include <QComboBox>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    QPushButton *eigthServoModelButton;
    QPushButton *sixServoModelButton;
    QPushButton *anotherModelButton;
private:
    Ui::MainWindow *ui;
    secondwindow *s;
signals:
    void sendData(int count);
private slots:
    void on_eigthServoModelButton_clicked();
    void on_sixServoModelButton_clicked();
    void on_anotherModelButton_clicked();
};
#endif // MAINWINDOW_H
