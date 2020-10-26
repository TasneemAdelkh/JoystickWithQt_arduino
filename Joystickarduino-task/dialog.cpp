#include "dialog.h"
#include "ui_dialog.h"
#include <QtSerialPort/QSerialPort>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
   /* qDebug()<<"av arduino :"<<QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialportinfo , QSerialPortInfo::availablePorts()){
        qDebug()<<"vendor: "<<serialportinfo.hasVendorIdentifier();
        if(serialportinfo.hasVendorIdentifier())
        {
            qDebug()<<"vendor "<<serialportinfo.vendorIdentifier();
        }
    } */
    arduino=new QSerialPort;
   buffer="";

    foreach(const QSerialPortInfo &serialportinfo , QSerialPortInfo::availablePorts()){
        if(serialportinfo.hasVendorIdentifier()&&serialportinfo.hasProductIdentifier())
        {
            port = serialportinfo.portName();
            avarduino=true;
        }
    }
    if(avarduino)
    {
        arduino->setPortName(port);
        arduino->open(QSerialPort:: ReadWrite);
        arduino->setBaudRate(QSerialPort ::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        QObject::connect(arduino,SIGNAL(readyRead()),this,SLOT(readingarduino()));
    }
   SDL_Init(SDL_INIT_JOYSTICK);
            SDL_Joystick *joystick=SDL_JoystickOpen(0);

            qDebug()<<"controller name"<<SDL_JoystickName(joystick);
            qDebug()<<"NUm Axes: "<<SDL_JoystickNumAxes(joystick);
            qDebug()<<"Num buttons: "<<SDL_JoystickNumButtons(joystick);
            joyeventloop=new threadevent(this);
            joyeventloop->start();
            connect(joyeventloop, &threadevent::SDL_Joybuttondown,this, &Dialog::writingarduino);


}
void Dialog:: writingarduino()
{
    if(arduino->isWritable())
    {
        arduino->write(QString("H" + ui->lineEdit->text()+"V"+ui->lineEdit_2->text()).toStdString().c_str());
    }
}

Dialog::~Dialog()
{

    if(arduino->isOpen())
        arduino->close();
    delete ui;
}
void Dialog:: readingarduino(){

  readlist=buffer.split(',');
  if(readlist.length()<5)
  {
      sensorsread=arduino->readAll();
      buffer +=QString::fromStdString(sensorsread.toStdString());
  }
  else{
      qDebug()<<readlist;
      Dialog::updatelcdpressure(readlist.at(0),readlist.at(1),readlist.at(2),readlist.at(3));
      buffer="";
  }
}
void Dialog:: splitting(){
     readlist= buffer.split(',');
    qDebug()<<readlist.at(1);
}
void Dialog::updatelcdpressure(QString pressure_reading,QString IMUX, QString IMUY,QString IMUYAW){
   ui->lcdNumberpressure->display(pressure_reading);
   ui->lcdNumber->display(IMUX);
   ui->lcdNumber_2->display(IMUY);
   ui->lcdNumber_3->display(IMUYAW);
}


void Dialog::on_pushButton_clicked()   //stop is called to stop running thread
{
    joyeventloop->running=false;

    qDebug()<<"test";
}
