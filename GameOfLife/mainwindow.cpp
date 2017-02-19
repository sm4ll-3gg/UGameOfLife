#include "mainwindow.h"

#include <QHeaderView>
#include <QChar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    resize(1000, 600);

    cWidget = new QWidget;
    cLayout = new QHBoxLayout(cWidget);

    mainWidget = new QWidget;
    cLayout->addWidget(mainWidget);
    mainLayout = new QGridLayout(mainWidget);

    game = new Game;
    connect(game, SIGNAL(gameConditionSwitched(Game::GameCondition)), this, SLOT(switchStartButtonTextByGameCondition(Game::GameCondition)));

    map = new Map;
    connect(map, SIGNAL(cellClicked(int,int)), game, SLOT(switchCellCondition(int,int)));
    connect(game, SIGNAL(cellClicked(int,int)), map, SLOT(switchBackground(int,int)));
    connect(map, SIGNAL(initBinaryMap(int,int)), game, SLOT(initBinaryMap(int,int)));
    connect(game, SIGNAL(setCellColorByCondition(int,int,bool)), map, SLOT(setCellColorByCondition(int,int,bool)));
    mainLayout->addWidget(map, 0, 0, 1, mainLayout->columnCount());

    buttonsLayout = new QHBoxLayout;

    first = new QPushButton("First");
    first->setMinimumSize(50, 50);
    connect(first, SIGNAL(clicked(bool)), game, SLOT(firstSnapshot()));
    buttonsLayout->addWidget(first);

    prev = new QPushButton("Previous");
    prev->setMinimumSize(50, 50);
    connect(prev, SIGNAL(clicked(bool)), game, SLOT(prevSnapshot()));
    buttonsLayout->addWidget(prev);

    start = new QPushButton("Start");
    start->setMinimumSize(50, 50);
    connect(start, SIGNAL(clicked(bool)), game, SLOT(switchGameConditon())); // start/pause game
    buttonsLayout->addWidget(start);

    next = new QPushButton("Next");
    next->setMinimumSize(50, 50);
    connect(next, SIGNAL(clicked(bool)), game, SLOT(nextSnapshot()));
    buttonsLayout->addWidget(next);

    clear = new QPushButton("Clear");
    clear->setMinimumSize(50, 50);
    connect(clear, SIGNAL(clicked(bool)), map, SLOT(clear()));
    connect(clear, SIGNAL(clicked(bool)), game, SLOT(clear()));
    buttonsLayout->addWidget(clear);

    settings = new QPushButton("Settings");
    settings->setMinimumSize(50, 50);
    connect(settings, SIGNAL(clicked(bool)), SLOT(openSettings()));
    buttonsLayout->addWidget(settings);

    mainLayout->addLayout(buttonsLayout, mainLayout->rowCount() , 0);

    settingsWidget = new Settings;
    settingsWidget->hide();
    connect(this, SIGNAL(settingsRequest()), settingsWidget, SLOT(getSettingsRequest()));
    connect(settingsWidget, SIGNAL(sendSettings(int,int,int)), game, SLOT(getSettings(int,int,int)));
    connect(settingsWidget, SIGNAL(sendSettings(int,int,int)), map, SLOT(getSettings(int,int,int)));
    connect(settingsWidget, SIGNAL(close()), this, SLOT(closeSettings()));
    cLayout->addWidget(settingsWidget);

    setCentralWidget(cWidget);

    emit settingsRequest();
}

MainWindow::~MainWindow()
{

}

void MainWindow::openSettings()
{
    mainWidget->hide();
    settingsWidget->setHidden(false);

    qDebug() << "Интерфейс | Открыты настройки";
}

void MainWindow::closeSettings()
{
    settingsWidget->hide();
    mainWidget->setHidden(false);

    qDebug() << "Интерфейс | Закрыты настройки";
}

void MainWindow::switchStartButtonTextByGameCondition(Game::GameCondition condition)
{
    if(condition == Game::GameCondition::BEFOTRE_GAME)
        start->setText("Start");
    else
        start->setText("Pause");
}
