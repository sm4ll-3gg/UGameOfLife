#include "settings.h"

#include <QLabel>
#include <QFont>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QTextBrowser>

Settings::Settings(QWidget *parent) :
    QWidget(parent)
{
    mainLayout = new QGridLayout;

    QFont headerFont;
    headerFont.setBold(true);
    headerFont.setPixelSize(18);

    QLabel* mapSize = new QLabel("Размер карты игрового поля:");
    mapSize->setFont(headerFont);
    mainLayout->addWidget(mapSize, 0, 0, Qt::AlignLeft);

    QHBoxLayout* rawsLayout = new QHBoxLayout;
    QLabel* raws = new QLabel("Количество строк: ");
    rawsLayout->addWidget(raws, 0, Qt::AlignLeft);
    QTextBrowser* rawsBrowser = new QTextBrowser;
    rawsBrowser->setMaximumHeight(30);
    rawsLayout->addWidget(rawsBrowser, 5, Qt::AlignCenter);
    mainLayout->addLayout(rawsLayout, 1, 0, Qt::AlignLeft);

    QHBoxLayout* columnsLayout = new QHBoxLayout;
    QLabel* columns = new QLabel("Количество столбцов: ");
    columnsLayout->addWidget(columns, 0, Qt::AlignLeft);
    QTextBrowser* columnsBrowser = new QTextBrowser;
    columnsBrowser->setMaximumHeight(30);
    columnsLayout->addWidget(columnsBrowser, 5, Qt::AlignCenter);
    mainLayout->addLayout(columnsLayout, 1, 1, Qt::AlignLeft);

    QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(spacer, 2, 0, 2);

    setLayout(mainLayout);
}

Settings::~Settings()
{
}
