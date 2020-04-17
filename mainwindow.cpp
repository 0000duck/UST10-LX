#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "decode.h"

#include <QDebug>
#include <QtNetwork/QHostAddress>
#include <QtOpenGL>
#include "drawer3d.h"
#include "qcustomplot.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _socket(this)
{
    qDebug() << "mainwindow constructor";

    ui->setupUi(this);

    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(&_socket, SIGNAL(connected()), this, SLOT(onConnected()));

    /////////
    connect(&_socket, SIGNAL(hostFound()), this, SLOT(test()));
    ////////

    _socket.connectToHost(QHostAddress("192.168.0.10"), 10940);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnected()
{
    qDebug() << "connected!";
    char msg[100];

    sprintf(msg,"BM\n");
    qDebug() << "BM request!\n";
    _socket.write(msg);

    _socket.waitForBytesWritten(100);

    QByteArray gdresp = "GD0000010000\n";
    qDebug() << "msg: " <<  gdresp;
    _socket.write(gdresp);

}


void MainWindow::onReadyRead()
{
    QByteArray responseRaw = _socket.readAll();
    qDebug() << "response: " << responseRaw;
    qDebug() << "end response";
}

void MainWindow::test(){

    responseRaw = "GD0000010000\n00P\nTGQjF\n"
                  "08A08;08908808408108907S07R08>08U09409J09G09F08G07o07W07W07U07;0g\n"
                  "6f06R06Y06U06W06c07J08608J08408G08808J08R09P09P09A09=09D09U09X093\n"
                  "X09P09R09C0:G15M15Q15V?om?om?om?om1:81:=19n?om?om?om?om?om?om?omK\n"
                  "?om?om?om1S`1Se1Sk1TU1XO1YA1YM1YM0bl0bi0bi0c60bj0c00c?0cE0cC0cB0i\n"
                  "cP0cV0cV0ce0ce0cY0a`0_f0_J0^i0^R0^@0]I0\\[0[o0[A8\n\n";

    //        responseRaw = "GD0000010000\n00P\nTGQjF\n"
    //                      "00i00i00i00i00k00k00n01101101101101101101100o00m00o00o0130130140]\n"
    //                      "14012012014015017017017016017017016016015015015014014014014015010\n"
    //                      "501801<01<01?01D01D01D01F01F01L01O01R01T01V01W01X01X01X01Z01Z01Ze\n"
    //                      "01001b01j02;02`09H09H09Z09Z09_0:90:90:@0:@0:@0:;0:@0:;0:;0:90:90]\n" //01\01
    //                "9Z08X08408408408608608608408408408408908908908908808608308008008V\n"
    //                "007m07m07j07h07h07h07d06E04D04>04=04=04>04C04H04H04I04J04K04U04Ue\n"
    //                "04X04X04X04W04W04W04W04[04]04_04`04`04h04l04l04n05005005305;05>0N\n"
    //                "5D05F05J05M05Q05T05W05[05]05^05`05f05f05m05n065065065068065065060\n"
    //                "906:06:06;06<06>06A06L06L06N06S06T06d07S07[09D0hH0hH0hH0gO0fk0fDV\n"
    //                "0eg0eU0e@0db0db0db0000000000000000000000000a40`N0_o0_`0_G0_=0^a0^\n"
    //                "^I0^<0]h0]W0]@0]00\\X0\\L0[l0[f0[S0[?0[00Zi0ZJ0ZC0Z70Z70Z70Z90Z90Z2\n"
    //                "90Z40Z00XR0XR0XR0XR0XR0XO0XD0W]0VT0VT0VM0V;0Um0Uc0U]0UQ0UJ0UC0U9Y\n"
    //                "0Te0Tc0T^0TK0T=0T70T60Sm0Sf0Sf0SR0SO0SD0S?0S70Rn0Rh0Rh0Rd0R]0RK0Y\n"
    //                "RD0RD0R70R60R20Qo0Qb0Q^0Q\\0QV0QL0QI0QH0QC0Q50Q40Q30Po0Pk0Pi0Pg0PD\n"
    //                "a0P[0PR0PR0PQ0PI0PI0PG0PB0PB0P@0P?0P:0P90P00P00Oh0Od0Oc0Oc0O`0O_[\n"
    //                "0O]0O]0OZ0OZ0OZ0OZ0OZ0O[0O[0Og0PO0PO0PO0PL0PL0PI0P90P90O_0OP0OP0k\n"
    //                "OP0Od0P50P50P>0PG0PG0PC0PC0PC0Oa0OH0OH0OH0OJ0OK0OL0OK0OK0OL0OP0O1\n"
    //                "Q0OQ0OQ0OR0OR0OT0OT0OU0OZ0OZ0O[0O[0O\\0O]0Oc0Oc0Oc0Od0On0On0Oo0OoY\n"
    //                "0P40P40P80P=0PC0PE0PE0PE0PN0PN0PP0PX0P`0Pb0Pg0Ph0Pm0Q90Q90Q90Q?0?\n"
    //                "QC0QF0QI0QM0Q[0Qa0Qc0Qi0R20R20R=0RA0RG0RO0RR0RX0R]0Rj0S10S20S90ST\n"
    //                "@0SJ0SP0SS0Sa0Sk0T80T:0T>0TI0TN0T]0Ta0Tl0U40U;0UN0UR0UV0Ul0V20V?5\n\n";
    mainFunc();
}



int MainWindow::mainFunc(){

    Decode d;

    qDebug() << responseRaw;
    QByteArray rangeData = d.clear(responseRaw);

    for(int i = 0; i < rangeData.size()/3;i++ ){
        d.getCoordinates(rangeData);
        x.append(d.getX());
        y.append(d.getY());
       // qDebug() << x.at(i) << y.at(i);
    }

    /// 3D
            Drawer3D = new drawer3D(ui->OGLQuad);
            Drawer3D->resize(1920,1080);

    /// 2D

//    QCustomPlot cPlot;
//    // создаем график и добавляем данные:
//    cPlot.addGraph();
//    cPlot.graph(0)->setData(x, y);

//    // задаем обозначения осей координат:
//    cPlot.xAxis->setLabel("x");
//    cPlot.yAxis->setLabel("y");
//    // устанавливаем диапазоны отображения данных:
//    cPlot.xAxis->setRange(-10, 10);
//    cPlot.yAxis->setRange(-10, 10);
//    //Ставим отображение точек
//    cPlot.graph(0)->setLineStyle(QCPGraph::lsNone);
//    cPlot.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));


//    // рисуем график
//    cPlot.replot();

//    cPlot.setWindowTitle("Lidar points");
//    cPlot.resize(548, 420);

//    cPlot.show();

}

QVector<double> MainWindow::getVecX(){
    return x;
}

QVector<double> MainWindow::getVecY(){
    return y;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Drawer3D->resize(event->size().width(),event->size().height());
}

