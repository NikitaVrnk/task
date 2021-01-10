#ifndef DEVICEBYTE_H
#define DEVICEBYTE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class DeviceByte; }
QT_END_NAMESPACE

class DeviceByte : public QMainWindow //локальный класс окна
{
    Q_OBJECT

public:
    DeviceByte(QWidget *parent = nullptr);
    ~DeviceByte();

private slots:
    void on_action_triggered();

private:
    Ui::DeviceByte *ui; //графический интерфейс
};



#endif // DEVICEBYTE_H
