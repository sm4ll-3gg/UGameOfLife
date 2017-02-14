#include "mainwindow.h"

#include <QHeaderView>
#include <QChar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    resize(1000, 600);

    cWidget = new QWidget;

    mainLayout = new QGridLayout(cWidget);

    game = new Game;
    connect(game, SIGNAL(gameConditionSwitched(Game::GameCondition)), this, SLOT(switchStartButtonTextByGameCondition(Game::GameCondition)));

    map = new Map;
    connect(map, SIGNAL(cellClicked(int,int)), game, SLOT(switchCellCondition(int,int)));
    connect(game, SIGNAL(cellClicked(int,int)), map, SLOT(switchBackground(int,int)));
    connect(map, SIGNAL(initBinaryMap(int,int)), game, SLOT(initBinaryMap(int,int)));
    connect(game, SIGNAL(setCellColorByCondition(int,int,bool)), map, SLOT(setCellColorByCondition(int,int,bool)));
    mainLayout->addWidget(map, 0, 0, 1, 6);

    settingsWidget = new Settings;
    settingsWidget->hide();
    connect(this, SIGNAL(settingsRequest()), settingsWidget, SLOT(getSettingsRequest()));
    connect(settingsWidget, SIGNAL(sendSettings(int,int)), game, SLOT(getSettings(int,int)));
    mainLayout->addWidget(settingsWidget, 0, 0, 1, 6);

    first = new QPushButton("First");
    first->setMinimumWidth(50);
    first->setMinimumHeight(50);
    connect(first, SIGNAL(clicked(bool)), game, SLOT(firstSnapshot()));
    mainLayout->addWidget(first, 2, 0);

    prev = new QPushButton("Previous");
    prev->setMinimumWidth(50);
    prev->setMinimumHeight(50);
    connect(prev, SIGNAL(clicked(bool)), game, SLOT(prevSnapshot()));
    mainLayout->addWidget(prev, 2, 1);

    start = new QPushButton("Start");
    start->setMinimumWidth(50);
    start->setMinimumHeight(50);
    connect(start, SIGNAL(clicked(bool)), game, SLOT(switchGameConditon())); // start/pause game
    mainLayout->addWidget(start, 2, 2);

    next = new QPushButton("Next");
    next->setMinimumWidth(50);
    next->setMinimumHeight(50);
    connect(next, SIGNAL(clicked(bool)), game, SLOT(nextSnapshot()));
    mainLayout->addWidget(next, 2, 3);

    settings = new QPushButton("Settings");
    settings->setMinimumWidth(50);
    settings->setMaximumHeight(50);
    connect(settings, SIGNAL(clicked(bool)), SLOT(openSettings()));
    connect(settingsWidget, SIGNAL(sendSettings(int,int)), map, SLOT(getSettings(int,int)));
    connect(settingsWidget, SIGNAL(close()), this, SLOT(closeSettings()));

    mainLayout->addWidget(settings, 2, 5);

    setCentralWidget(cWidget);

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

void MainWindow::switchStartButtonTextByGameCondition(Game::GameCondition condition)
{
    if(condition == Game::GameCondition::BEFOTRE_GAME)
        start->setText("Start");
    else
        start->setText("Pause");
}
