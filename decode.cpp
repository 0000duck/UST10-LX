#include "Decode.h"

Decode::decode()
{
    qDebug() << "decode constructor";
}

int Decode::decodeByte(QByteArray code, int byte) {
    int value = 0;
    int i;
    for (i = 0; i < byte; ++i) {
        value <<= 6;
        value &= ~0x3f;
        value |= code[i] - 0x30;
    }
    return value;
}

QByteArray Decode::clear(QByteArray rangeData){


    int n = 0;
    for(int i = 0; i<rangeData.size(); i++){  // Убираем все \n
        rangeData.remove(rangeData.indexOf("\n"),1);
        n++;
    }

    int offset = gdresp.size()+7; // 19


    for(int i = 0; i<rangeData.size()-offset; i++){   // Оставляем только данные о расстоянии
        rangeData[i] = rangeData[i+offset];
    }

    rangeData.resize(rangeData.size()-offset+n/65); // 3 - кол-во \n в первых 3х строках

    for (int i = 1; i < rangeData.size()/65+1; i++){ // Убираем байт контрольной суммы
        rangeData.remove(64*i,1);
        rangeData.remove(rangeData.size()-1,1);
    }

    return rangeData;
}

void Decode::getCoordinates(QByteArray rangeData){

    threeBytes.append(rangeData[0+j]);
    threeBytes.append(rangeData[1+j]);
    threeBytes.append(rangeData[2+j]);

    double range = Decode::decodeByte(threeBytes, threeBytes.size());

    if(range != 65533 && range != 4){

        range = range/1000;

        tetha = (angleMin + i*angleResolution) * PI/180;
        x = range * sin(tetha);
        y = range * cos(tetha);

        i++;
        threeBytes.clear();
        j+=3;
    }
}

double Decode::getX(){
    return x;
}

double Decode::getY(){
    return y;
}
