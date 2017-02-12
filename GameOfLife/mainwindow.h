#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "map.h"
#include "settings.h"

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWidget*        cWidget;

    QGridLayout*    mainLayout;

    Map*            map;
    Settings*       settingsWidget;

    QPushButton*    start; // Манипуляции с итерациями мира
    QPushButton*    stop;
    QPushButton*    next;
    QPushButton*    prev;
    QPushButton*    first;
    QPushButton*    settings;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void settingsRequest(int rows, int columns);

private slots:
    void openSettings();
};

#endif // MAINWINDOW_H
