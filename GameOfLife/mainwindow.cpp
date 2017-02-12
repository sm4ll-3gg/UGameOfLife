#include "mainwindow.h"

#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    cWidget = new QWidget;

    mainLayout = new QGridLayout(cWidget);

    map = new Map(10, 10);
    mainLayout->addWidget(map, 0, 0, 1, 6);

    settingsWidget = new Settings;

    first = new QPushButton("|<<");
    first->setMinimumWidth(50);
    first->setMinimumHeight(50);
    mainLayout->addWidget(first, 2, 0);

    prev = new QPushButton("<");
    prev->setMinimumWidth(50);
    prev->setMinimumHeight(50);
    mainLayout->addWidget(prev, 2, 1);

    start = new QPushButton(">");
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
    mainLayout->addWidget(settings, 2, 5);
    connect(settings,
            SIGNAL(clicked(bool)),
            SLOT(openSettings())
           );

    setCentralWidget(cWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::openSettings()
{
    mainLayout->addWidget(settingsWidget, 0, 0, 1, 6);
}
