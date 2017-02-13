#include "settings.h"

#include <QDebug>
#include <QPalette>

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    rows(10), columns(10)
{
    mainLayout = new QGridLayout;

    QFont headerFont;
    headerFont.setBold(true);
    headerFont.setPixelSize(18);

    mapSize = new QLabel("Размер карты игрового поля:");
    mapSize->setFont(headerFont);
    mainLayout->addWidget(mapSize, 0, 0, Qt::AlignLeft);

    rowsLayout = new QHBoxLayout;
    rowsText = new QLabel("Количество строк: ");
    rowsLayout->addWidget(rowsText, 0, Qt::AlignLeft);
    rowsBrowser = new QLineEdit;
    rowsBrowser->setText("10");
    rowsBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rowsBrowser->setMaximumSize(1000,30);
    rowsLayout->addWidget(rowsBrowser, 5, Qt::AlignLeft);
    rowsUncorrectValue = new QLabel("Некорректное значение!");
    rowsUncorrectValue->setStyleSheet("color: red; font: italic;");
    rowsUncorrectValue->hide();
    rowsLayout->addWidget(rowsUncorrectValue, Qt::AlignLeft);
    mainLayout->addLayout(rowsLayout, 1, 0, Qt::AlignLeft);

    columnsLayout = new QHBoxLayout;
    columnsText = new QLabel("Количество столбцов: ");
    columnsLayout->addWidget(columnsText, 0, Qt::AlignLeft);
    columnsBrowser = new QLineEdit;
    columnsBrowser->setText("10");
    columnsBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    columnsBrowser->setMaximumSize(1000, 30);
    columnsLayout->addWidget(columnsBrowser, 5, Qt::AlignLeft);
    columnsUncorrectValue = new QLabel("Некорректное значение!");
    columnsUncorrectValue->setStyleSheet("color: red; font: italic;");
    columnsUncorrectValue->hide();
    columnsLayout->addWidget(columnsUncorrectValue, Qt::AlignLeft);
    mainLayout->addLayout(columnsLayout, 1, 1, Qt::AlignLeft);

    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addItem(spacer, 2, 0);

    CancelAndApplyLayout = new QHBoxLayout;
    apply = new QPushButton("Apply");
    apply->setMaximumSize(149, 40);
    apply->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(apply,
            SIGNAL(clicked(bool)),
            this,
            SLOT(saveSettings())
            );
    CancelAndApplyLayout->addWidget(apply, 10);
    cancel = new QPushButton("Cancel");
    cancel->setMaximumSize(149, 40);
    cancel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(cancel,
            SIGNAL(clicked(bool)),
            this,
            SLOT(cancelSettingsChanges())
            );
    CancelAndApplyLayout->addWidget(cancel, 10);
    mainLayout->addLayout(CancelAndApplyLayout, 5, 3, Qt::AlignRight);

    setLayout(mainLayout);
}

Settings::~Settings()
{
}

bool Settings::isNumber(const QString &string)
{
    for(auto it = string.begin(); it != string.end(); ++it)
    {
        if(!it->isNumber())
        {
            return false;
        }
    }

    return true;
}

void Settings::getSettingsRequest()
{
    emit sendSettings(rows, columns);
}

void Settings::saveSettings()
{
    bool allRight = true;

    if(isNumber(rowsBrowser->text()))
    {
        rows = rowsBrowser->text().toInt();
        if(!rowsUncorrectValue->isHidden()) rowsUncorrectValue->setHidden(true);
        allRight = true;
        qDebug() << "Настройки | Изменено число строк";
    }
    else
    {
        if(rowsUncorrectValue->isHidden()) rowsUncorrectValue->setHidden(false);
        allRight = false;
        qDebug() << "Настройки | Введенное количество строк не является числом.";
    }

    if(isNumber(columnsBrowser->text()))
    {
        columns = columnsBrowser->text().toInt();
        if(!columnsUncorrectValue->isHidden()) columnsUncorrectValue->setHidden(true);
        allRight = true;
        qDebug() << "Настройки | Изменено число столбцов";
    }
    else
    {
        if(columnsUncorrectValue->isHidden()) columnsUncorrectValue->setHidden(false);
        allRight = false;
        qDebug() << "Настройки | Введенное количество столбцов не является числом.";
    }

    if(allRight)
    {
        emit sendSettings(rows, columns);
        qDebug() << "Настройки | Настройки успешно изменены";
        emit close();
    } else qDebug() << "Настройки | Ошибка при изменении настроек";
}

void Settings::cancelSettingsChanges()
{
    rowsBrowser->setText(QString::number(rows));
    columnsBrowser->setText(QString::number(columns));
    emit close();
}
