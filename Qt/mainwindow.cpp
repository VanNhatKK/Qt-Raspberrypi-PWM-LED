#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TCPSocket = new QTcpSocket();
    connect(TCPSocket,SIGNAL(readyRead()),SLOT(Read_Data()));
    TCPSocket->open(QIODevice::ReadWrite);
    if(TCPSocket->isOpen())
    {
        QMessageBox::information(this,"Qt with Nhat","Connect to the Server.");
    }
    else
    {
        QMessageBox::information(this,"Qt with Nhat","Not connect to the Server.");
    }
    QIntValidator *validator = new QIntValidator();
    ui->lineEdit_inputPort->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_SendData_clicked()
{
    if(TCPSocket)
    {
        if(TCPSocket->isOpen())
        {
            QString WriteData = ui->lineEdit->text();
            TCPSocket->write(WriteData.toUtf8());
        }
        else
        {
            QMessageBox::information(this,"Qt with Nhat","Error: "+ TCPSocket->errorString());
        }
    }
    else
    {
        QMessageBox::information(this,"Qt with Nhat","Error: "+ TCPSocket->errorString());
    }
}


int check=0;

void MainWindow::on_pushButton_Connect_clicked()
{

    QString inputIP = ui->lineEdit_inputIP->text();
    QHostAddress IP(inputIP);
    QString inputPort = ui->lineEdit_inputPort->text();
    int Port = inputPort.toInt();
    if(IP.isNull()||Port==0)
    {
        QMessageBox::information(this,"Qt with Nhat","Error: Please input IP & Port");
    }
    check=check+1;
    if((check)%2==1)
    {
        TCPSocket->connectToHost(IP, Port);
        if(TCPSocket->waitForConnected())
        {
            ui->pushButton_Connect->setText("Disconnect");
            ui->label_Noti->setText("Connected");
            ui->label_Lamp->setStyleSheet("background-color: green; border-radius: 15px; width: 15px; height: 15px;");
        }
    }
    else if((check)%2==0)
    {
        if (TCPSocket->state() == QAbstractSocket::ConnectedState)
        {
            TCPSocket->disconnectFromHost();
            ui->label_Lamp->setStyleSheet("background-color: red; border-radius: 15px; width: 15px; height: 15px;");
            ui->pushButton_Connect->setText("Connect");
            ui->label_Noti->setText("Disconnect");
        }
    }
}






int value_Red,value_Green,value_Blue;

void MainWindow::on_horizontalSlider_Red_valueChanged(int value)
{
    value_Red=value;
    ui->label_value_Red->setText(QString::number(value_Red)+"%");
}


void MainWindow::on_horizontalSlider_Green_valueChanged(int value)
{
    value_Green=value;
    ui->label_value_Green->setText(QString::number(value_Green)+"%");
}


void MainWindow::on_horizontalSlider_Blue_valueChanged(int value)
{
    value_Blue=value;
    ui->label_value_Blue->setText(QString::number(value_Blue)+"%");
}


void MainWindow::on_horizontalSlider_Red_actionTriggered(int action)
{
    if(action)
        TCPSocket->write((QString::number(value_Red)).toUtf8()+"r"+(QString::number(value_Green)).toUtf8()+"g"+(QString::number(value_Blue)).toUtf8()+"b");
}

void MainWindow::on_horizontalSlider_Green_actionTriggered(int action)
{
    if(action)
        TCPSocket->write((QString::number(value_Green)).toUtf8()+"r"+(QString::number(value_Green)).toUtf8()+"g"+(QString::number(value_Blue)).toUtf8()+"b");
}

void MainWindow::on_horizontalSlider_Blue_actionTriggered(int action)
{
    if(action)
        TCPSocket->write((QString::number(value_Red)).toUtf8()+"r"+(QString::number(value_Green)).toUtf8()+"g"+(QString::number(value_Blue)).toUtf8()+"b");
}

