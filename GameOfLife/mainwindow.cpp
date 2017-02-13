#include "mainwindow.h"

#include <QHeaderView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    resize(1000, 600);

    cWidget = new QWidget;

    mainLayout = new QGridLayout(cWidget);

    map = new Map;
    mainLayout->addWidget(map, 0, 0, 1, 6);

    settingsWidget = new Settings;
    settingsWidget->hide();
    connect(this, SIGNAL(settingsRequest()), settingsWidget, SLOT(getSettingsRequest()));
    mainLayout->addWidget(settingsWidget, 0, 0, 1, 6);

    first = new QPushButton("|<<");
    first->setMinimumWidth(50);
    first->setMinimumHeight(50);
    mainLayout->addWidget(first, 2, 0);

    prev = new QPushButton("<");
    prev->setMinimumWidth(50);
    prev->setMinimumHeight(50);
    mainLayout->addWidget(prev, 2, 1);

    start = new QPushButton("> ||");
    start->setMinimumWidth(50);
    start->setMinimumHeight(50);
    mainLayout->addWidget(start, 2, 2);

    stop = new QPushButton("⏹");
    stop->setMinimumWidth(50);
    stop->setMinimumHeight(50);
    mainLayout->addWidget(stop, 2, 3);

    next = new QPushButton(">");
    next->setMinimumWidth(50);
    next->setMinimumHeight(50);
    mainLayout->addWidget(next, 2, 4);

    settings = new QPushButton("Settings");
    settings->setMinimumWidth(50);
    settings->setMaximumHeight(50);
    connect(settings, SIGNAL(clicked(bool)), SLOT(openSettings()));
    connect(settingsWidget, SIGNAL(sendSettings(int,int)), map, SLOT(getSettings(int,int)));
    connect(settingsWidget, SIGNAL(close()), this, SLOT(closeSettings()));

    mainLayout->addWidget(settings, 2, 5);

    setCentralWidget(cWidget);

    game = new Game;
    connect(map, SIGNAL(cellClicked(int,int)), game, SLOT(switchCellCondition(int,int)));
    connect(map, SIGNAL(initBinaryMap(int,int)), game, SLOT(initBinaryMap(int,int)));
    connect(map, SIGNAL(switchCellCondition(int,int)), game, SLOT(switchCellCondition(int,int)));
    connect(settingsWidget, SIGNAL(sendSettings(int,int)), game, SLOT(getSettings(int,int)));
    connect(game, SIGNAL(setCellColorByCondition(int,int,bool)), map, SLOT(setCellColorByCondition(int,int,bool)));
    connect(next, SIGNAL(clicked(bool)), game, SLOT(nextSnapshot()));

    emit settingsRequest();
}

MainWindow::~MainWindow()
{

}

void MainWindow::openSettings()
{
    map->hide();
    settingsWidget->setHidden(false);
    qDebug() << "Интерфейс | Открыты настройки";
}

void MainWindow::closeSettings()
{
    settingsWidget->hide();
    map->setHidden(false);
    qDebug() << "Интерфейс | Закрыты настройки";
}
