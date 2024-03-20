#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QIntValidator>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_SendData_clicked();

    void on_pushButton_Connect_clicked();



    void on_horizontalSlider_Red_valueChanged(int value);

    void on_horizontalSlider_Green_valueChanged(int value);

    void on_horizontalSlider_Blue_valueChanged(int value);




    void on_horizontalSlider_Red_actionTriggered(int action);

    void on_horizontalSlider_Green_actionTriggered(int action);

    void on_horizontalSlider_Blue_actionTriggered(int action);

private:
    Ui::MainWindow *ui;
    QTcpSocket *TCPSocket;
    QString *dataIP;
};
#endif // MAINWINDOW_H
