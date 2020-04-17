#ifndef DECODE_H
#define DECODE_H
#include <QCoreApplication>
#include <QDebug>
#define PI 3.14
class Decode
{

private:

    int bytesForData = 3;
    double angleMin = -135;
    double angleResolution = 0.25;
    double tetha = 0;
    double x,y;
    int i = 0, j = 0;

    QByteArray gdresp = "GD0000010000\n";        // Запрос лидару, потом уберу
    QByteArray threeBytes;                       // Массив, содержащий одну информацию о расстоянии
    QByteArray rangeData;

    int decodeByte(QByteArray code, int byte);   // Декодирование

public:
    double getX();
    double getY();
    int getSize();

    decode();
    QByteArray clear(QByteArray rangeData);      // Функция, оставляющая в полученном ответе только данные о расстоянии
    void getCoordinates(QByteArray rangeData);   // Функция, получающая координаты точек

};

#endif // DECODE_H
