#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "map.h"
#include "settings.h"
#include "game.h"

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

    Game*           game; // Логика игры

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void settingsRequest();
    void changeGameCondition(Game::GameCondition newCondition);

private slots:
    void openSettings();
    void closeSettings();
};

#endif // MAINWINDOW_H
