#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPortInfo>
#include<QDebug>
#include<QtCore>
#include <QString>
#include <SDL.h>
#include<QWidget>
#include<threadevent.h>
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE
class threadevent;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void updatelcdpressure (QString pressure_reading,QString IMUX, QString IMUY,QString IMUYAW);
    void splitting();
 signals:


private slots:
    void writingarduino();
    void  readingarduino();


    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    QSerialPort *arduino;
    const  quint16 vendor =9025;
    const quint16 product =67;
    bool avarduino;
    QString port;
threadevent *joyeventloop;
QByteArray sensorsread;
QString buffer;
QStringList readlist;
};
#endif // DIALOG_H
