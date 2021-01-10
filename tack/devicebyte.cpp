#include "devicebyte.h"
#include "ui_devicebyte.h"

#include <iostream>
#include <fstream>
#include <bitset>

#define FLOAT_ARRAY_SIZE 5
#define OUTPUT_INT_ARRAY_SIZE 10

//����� ������
#define  FLAG_option_1  0
#define  FLAG_option_2  1
#define  FLAG_option_3  2
#define  FLAG_option_4  3
#define  FLAG_option_5  4
#define  FLAG_option_6  5
#define  FLAG_option_7  6
#define  FLAG_option_8  7

struct Msg {
    std::bitset<64> mask = 0xAAAAAAAAAAAAAAAA;
    std::bitset<8> bitsFLAG = FLAG_option_8; //8 ���
    int32_t id = 2111111111;
    int32_t n = 1999999999;

    float arrayMSG[FLOAT_ARRAY_SIZE] = { 0.0, 1.1, 2.2,3.3,4.4 };
};

//������ ��������� � ������
int struct2Array(Msg *msg, int32_t *arrMsg, uint32_t size) {

    int8_t* ptr_arrMsg = (int8_t*)arrMsg;
    int8_t* ptr_msg = (int8_t*)msg;

    size_t sz_arrMsg = sizeof(*arrMsg) * size;
    size_t sz_msg = sizeof(*msg);

   //�������� �� �������������� ������� sz_arrMsg != sz_msg0
    if (sz_arrMsg != sz_msg) {
        std::cerr << "Ошибка размеры sz_arrMsg и sz_msg0 не совпадают" << std::endl;
        return 1;
    }

    for (size_t i = 0; i < sz_msg; i++) {
        *(ptr_arrMsg + i) = *(ptr_msg + i);
    }
    return 0;
};

//������ ������� � ���������
int array2Struct(int32_t *arrMsg, uint32_t size, Msg *msg) {

    int8_t* ptr_arrMsg = (int8_t*)arrMsg;
    int8_t* ptr_msg = (int8_t*)msg;

    size_t sz_arrMsg = sizeof(*arrMsg) * size;
    size_t sz_msg = sizeof(*msg);

    //�������� �� �������������� ������� sz_arrMsg != sz_msg1
    if (sz_arrMsg != sz_msg) {
        std::cerr << "Ошибка размеры sz_arrMsg и sz_msg1 не совпадают" << std::endl;
        return 2;
    }

    for (size_t i = 0; i < sz_msg; i++) {
        *(ptr_msg + i) = *(ptr_arrMsg + i);
    }
    return 0;
};

//���������� ������� � ����
int arr2File(int32_t *arrMsg, uint32_t size, std::string fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::binary);

    int8_t* ptr_arrMsg = (int8_t*)arrMsg;
    size_t sz_arrMsg = sizeof(*arrMsg) * size;

    for (size_t i = 0; i < sz_arrMsg; i++) {
        file << *(ptr_arrMsg + i);
    }

    file.close();

    return 0;
};


//����� ������� �� �����
int file2Arr(std::string fileName, int32_t *arrMsg, uint32_t size) {

    std::ifstream file;
    file.open(fileName, std::ios::in | std::ios::binary);
    int8_t* ptr_arrMsg = (int8_t*)arrMsg;
    size_t sz_arrMsg = sizeof(*arrMsg) * size;

    for (size_t i = 0; i < sz_arrMsg; i++) {
        file.read((char*)ptr_arrMsg, sz_arrMsg);


    }

    file.close();
    return 0;
};

DeviceByte::DeviceByte(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DeviceByte)
{
    ui->setupUi(this);
}

DeviceByte::~DeviceByte()
{
    delete ui;
}


void DeviceByte::on_action_triggered()
{

    int32_t arrMsg[OUTPUT_INT_ARRAY_SIZE] = {1999999999};
    int32_t arrMsgInput[OUTPUT_INT_ARRAY_SIZE] = {};

    Msg msg0;
    Msg msg1 = {
        0,
        0,
        0,
        0,
        {0,0,0,0,0}
    };
    //����� ��������
    ui->console->appendPlainText( "� азмер Msg = " + QString::number(sizeof(Msg))+"\n");
   // std::cout << "� азмер Msg = "<< sizeof(Msg) << std::endl;
    ui->console->appendPlainText( "� азмер arrMsg = " + QString::number(sizeof(arrMsg))+"\n");
    //std::cout << "� азмер arrMsg = " << sizeof(arrMsg) << std::endl;
    ui->console->appendPlainText( "� азмер msg0 = " + QString::number(sizeof(msg0))+"\n");
   // std::cout << "� азмер msg0 = " << sizeof(msg0) << std::endl;
    ui->console->appendPlainText( "� азмер msg1 = " + QString::number(sizeof(msg1))+"\n");
   // std::cout << "� азмер msg1 = " << sizeof(msg1) << std::endl;

    //����� ������������ �������
     ui->console->appendPlainText( "Преобразование структуры в массив");
    struct2Array(&msg0, arrMsg, OUTPUT_INT_ARRAY_SIZE);
      ui->console->appendPlainText( "Сохранение массива в файл");
    arr2File(arrMsg, OUTPUT_INT_ARRAY_SIZE, "File.bin");
      ui->console->appendPlainText( "Загрузка из файла в новый массив");
    file2Arr("File.bin", arrMsgInput, OUTPUT_INT_ARRAY_SIZE);
      ui->console->appendPlainText( "Преобразование нового массива в новую структуру");
    array2Struct(arrMsgInput, OUTPUT_INT_ARRAY_SIZE, &msg1);

      ui->console->appendPlainText( "Преобразования завершены ");
}
