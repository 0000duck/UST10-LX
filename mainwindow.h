#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QNetworkRequest>
#include <unistd.h>
#include <string.h>
#include <QVector>
#include "drawer3d.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<double> getVecX();
    QVector<double> getVecY();

public slots:
    void onConnected();
    void onReadyRead();
    void test();
    void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
    drawer3D* Drawer3D;

    QTcpSocket  _socket;
    QVector<double> x;
    QVector<double> y;
    QByteArray responseRaw;

    QByteArray getResponseRaw();
    int mainFunc();

};

#endif // MAINWINDOW_H
