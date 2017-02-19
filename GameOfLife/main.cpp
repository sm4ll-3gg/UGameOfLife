#include "mainwindow.h"
#include <QApplication>

/*=============================
 *          TODO:
 * Добавить возможность очищать игровое поле;
 * Убрать выделение ячеек при нажатии на них;
 * Возможно написать конфиг;
===============================*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
