#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QComboBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSignalMapper>
#include <QWidget>

namespace Ui {
class secondwindow;
}

class secondwindow : public QWidget
{
    Q_OBJECT

public:
    explicit secondwindow(QWidget *parent = nullptr);
    ~secondwindow();
public:
    QPushButton *autoButton;
    QPushButton *oneButton;
    QPushButton *rtcButton;
    QPushButton *connectButton;

    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *recordButton;
    QPushButton *reWriteButton;
    QPushButton *deleteButton;
    QPushButton *clearButton;
    QPushButton *upButton;
    QPushButton *downButton;
    QPlainTextEdit *textValues;
    QComboBox *baudValuesBox;
    QComboBox *comPortName;
    QLineEdit *minServoVal;
    QLineEdit *maxServoVal;
    QPushButton *applyServoVal;

    void closeEvent(QCloseEvent *event);
public slots:
    void recieveData(int);
private slots:
    void findAvailableComPorts();
    void autoButtonClick();
    void oneButtonClick();
    void rtcButtonClick();
    void minButtonClick(int);
    void maxButtonClick(int);
    void resButtonClick(int);
    void OnClose();
    void connectButtonClick();

    void loadButtonClick();
    void saveButtonClick();
    void recordButtonClick();
    void reWriteButtonClick();
    void deleteButtonClick();
    void clearButtonClick();

    void upButtonClick();
    void downButtonClick();

    void minServoValChanged();
    void maxServoValChanged();
    void applyServoValClicked();

    void OnDoubleClicked(const QModelIndex &index);

    void slider0value(int val);
    void slider1value(int val);
    void slider2value(int val);
    void slider3value(int val);
    void slider4value(int val);
    void slider5value(int val);
    void slider6value(int val);
    void slider7value(int val);
    void slider8value(int val);
    void slider9value(int val);
    void slider10value(int val);
    void slider11value(int val);
    void slider12value(int val);
    void slider13value(int val);
    void slider14value(int val);
    void slider15value(int val);
    void slider16value(int val);
    void slider17value(int val);
    void slider18value(int val);
    void slider19value(int val);
private:
    Ui::secondwindow *ui;
    QSignalMapper *signalMapper;

};

#endif // SECONDWINDOW_H
