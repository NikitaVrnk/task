#include "devicebyte.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"Russian");

    QApplication a(argc, argv);
    DeviceByte w; //сохдается жкземпляр окна




    w.show(); //показать
    return a.exec(); //exec(); цикл обработки события
}
