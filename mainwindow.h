#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "secondwindow.h"

#include <QComboBox>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QKeyEvent>
#include "qlabel.h"
#include <QLineEdit>



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
    QLabel *labelForServoCount;
    QLineEdit *anotherModelServoCount;

private:
    Ui::MainWindow *ui;
    secondwindow *s;
signals:
    void sendData(int count);
private slots:
    void on_sixServoModelButtonClicked();
    void on_eigthServoModelButtonClicked();
    void on_anotherModelServoCountChanged();
    void on_anotherModelButtonClicked();
};
#endif // MAINWINDOW_H
