#include "settings.h"

#include <QDebug>

Settings::Settings(QWidget *parent) :
    QWidget(parent)
{
    readSettings();

    mainLayout = new QGridLayout;
    mainLayout->setSpacing(20);

    QFont headerFont;
    headerFont.setBold(true);
    headerFont.setPixelSize(18);

    int rowCount = 0;
    int columnCount = 0;

    mapSize = new QLabel("Размер карты игрового поля:");
    mapSize->setFont(headerFont);
    mainLayout->addWidget(mapSize, rowCount, columnCount, Qt::AlignLeft);

    rowCount++;

    rowsLayout = new QHBoxLayout;
    rowsText = new QLabel("Количество строк: ");
    rowsLayout->addWidget(rowsText, 0, Qt::AlignLeft);
    rowsBrowser = new QLineEdit;
    rowsBrowser->setText( settings.value("/Settings/rows", "10").toString() );
    rowsBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rowsBrowser->setMaximumSize(1000,30);
    rowsLayout->addWidget(rowsBrowser, 5, Qt::AlignLeft);
    rowsUncorrectValue = new QLabel("Некорректное значение!");
    rowsUncorrectValue->setStyleSheet("color: red; font: italic;");
    rowsUncorrectValue->hide();
    rowsLayout->addWidget(rowsUncorrectValue, Qt::AlignLeft);
    mainLayout->addLayout(rowsLayout, rowCount, 0, Qt::AlignLeft);

    columnsLayout = new QHBoxLayout;
    columnsText = new QLabel("Количество столбцов: ");
    columnsLayout->addWidget(columnsText, 0, Qt::AlignLeft);
    columnsBrowser = new QLineEdit;
    columnsBrowser->setText( settings.value("/Settings/columns", "10").toString() );
    columnsBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    columnsBrowser->setMaximumSize(1000, 30);
    columnsLayout->addWidget(columnsBrowser, 5, Qt::AlignLeft);
    columnsUncorrectValue = new QLabel("Некорректное значение!");
    columnsUncorrectValue->setStyleSheet("color: red; font: italic;");
    columnsUncorrectValue->hide();
    columnsLayout->addWidget(columnsUncorrectValue, Qt::AlignLeft);
    mainLayout->addLayout(columnsLayout, rowCount, 1, Qt::AlignLeft);

    rowCount++;

    timerBrowser = new QLabel("Частота ходов (в миллисекундах): ");
    timerBrowser->setFont(headerFont);
    mainLayout->addWidget(timerBrowser, rowCount, 0, Qt::AlignLeft);
    timerSlider = new QSlider(Qt::Horizontal);
    timerSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    timerSlider->setTickPosition(QSlider::TicksAbove);
    timerSlider->setMinimumSize(200,20);
    timerSlider->setMaximumSize(500, 20);
    timerSlider->setRange(100, 2000);
    timerSlider->setValue( settings.value("/Settings/timer_delay", 500).toInt() );
    timerSlider->setSingleStep(100);
    timerSlider->setPageStep(100);
    timerValue = new QLabel;
    timerValue->setNum( settings.value("/Settings/timer_delay", 500).toInt() );
    connect(timerSlider, SIGNAL(valueChanged(int)), timerValue, SLOT(setNum(int)));
    mainLayout->addWidget(timerValue, rowCount, 3, Qt::AlignLeft);
    mainLayout->addWidget(timerSlider, rowCount, 1, Qt::AlignLeft);

    rowCount++;

    gameSettingsLayout = new QGridLayout;
    gameSettingsHeader = new QLabel("Игровые настройки:");
    gameSettingsHeader->setFont(headerFont);
    gameSettingsLayout->addWidget(gameSettingsHeader, 0, 0, 1, gameSettingsLayout->columnCount(), Qt::AlignLeft);

    numberToAliveLayout = new QHBoxLayout;
    numberToAliveLabel = new QLabel("Количество живых клеток вокруг для зарождения жизни: ");
    numberToAliveLayout->addWidget(numberToAliveLabel);
    numberToAliveField = new QSpinBox;
    numberToAliveField->setMinimumSize(30, 30);
    numberToAliveField->setButtonSymbols(QSpinBox::PlusMinus);
    numberToAliveField->setRange(1, 8);
    numberToAliveField->setValue(numberToAlive);
    numberToAliveField->setWrapping(true);
    numberToAliveLayout->addWidget(numberToAliveField, 0, Qt::AlignLeft);
    gameSettingsLayout->addLayout(numberToAliveLayout, 1, 0, 1, gameSettingsLayout->columnCount(), Qt::AlignLeft);

    numberToSurviveLayout = new QHBoxLayout;
    numberToSurviveFromLabel = new QLabel("Количество живых клеток вокруд для выживания: от ");
    numberToSurviveLayout->addWidget(numberToSurviveFromLabel);
    minimumNumberToSurviveField = new QSpinBox;
    minimumNumberToSurviveField->setRange(0, 8);
    minimumNumberToSurviveField->setValue(minimumNumberToSurvive);
    minimumNumberToSurviveField->setWrapping(true);
    connect(minimumNumberToSurviveField, SIGNAL(valueChanged(int)), this, SLOT(minimumNumberToSurviveChanged(int)));
    numberToSurviveLayout->addWidget(minimumNumberToSurviveField);
    numberToSurviveToLabel = new QLabel(" до ");
    numberToSurviveLayout->addWidget(numberToSurviveToLabel);
    maximumNumberToSurviveField = new QSpinBox;
    maximumNumberToSurviveField->setRange(minimumNumberToSurvive, 8);
    maximumNumberToSurviveField->setValue(maximumNumberToSurvive);
    maximumNumberToSurviveField->setWrapping(true);
    numberToSurviveLayout->addWidget(maximumNumberToSurviveField);
    gameSettingsLayout->addLayout(numberToSurviveLayout, 2, 0, 1, gameSettingsLayout->columnCount(), Qt::AlignLeft);

    mainLayout->addLayout(gameSettingsLayout, rowCount, 0, 1, mainLayout->columnCount());

    rowCount++;

    spacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addItem(spacer, rowCount, 0);

    CancelAndApplyLayout = new QHBoxLayout;
    apply = new QPushButton("Apply");
    apply->setMaximumSize(150, 40);
    apply->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(apply, SIGNAL(clicked(bool)), this, SLOT(saveSettings()));
    CancelAndApplyLayout->addWidget(apply, 10);
    cancel = new QPushButton("Cancel");
    cancel->setMaximumSize(150, 40);
    cancel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(cancelSettingsChanges()));
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

void Settings::readSettings()
{
    settings.beginGroup("/Settings");

    rows = settings.value("/rows", 10).toInt();
    columns = settings.value("/columns", 10).toInt();
    timer = settings.value("/timer_delay", 500).toInt();
    numberToAlive = settings.value("/number_to_alive", 3).toInt();
    minimumNumberToSurvive = settings.value("/minimum_number_to_survive", 2).toInt();
    maximumNumberToSurvive = settings.value("/maximum_number_to_survive", 3).toInt();

    settings.endGroup();
}

void Settings::writeSettings()
{
    settings.beginGroup("/Settings");

    settings.setValue("/rows", rows);
    settings.setValue("/columns", columns);
    settings.setValue("/timer_delay", timer);
    settings.setValue("/number_to_alive", numberToAlive);
    settings.setValue("/minimum_number_to_survive", minimumNumberToSurvive);
    settings.setValue("/maximum_number_to_survive", maximumNumberToSurvive);

    settings.endGroup();
}

void Settings::getSettingsRequest()
{
    emit sendSettings(settings);
}

void Settings::saveSettings()
{
    timer = timerSlider->value();
    numberToAlive = numberToAliveField->value();
    minimumNumberToSurvive = minimumNumberToSurviveField->value();
    maximumNumberToSurvive = maximumNumberToSurviveField->value();

    bool isOk = true;

    int temp = rowsBrowser->text().toInt(&isOk);
    if(isOk)
    {
        rows = temp;
        rowsUncorrectValue->hide();
    }
    else
    {
        rowsUncorrectValue->setHidden(false);
        qDebug() << "Настройки | Некорректно задано количество строк";
        return;
    }

    temp = columnsBrowser->text().toInt(&isOk);
    if(isOk)
    {
        columns = temp;
        columnsUncorrectValue->hide();
    }
    else
    {
        columnsUncorrectValue->setHidden(false);
        qDebug() << "Настройки | Некорректно задано количество строк";
        return;
    }

    writeSettings();

    emit sendSettings(settings);
    qDebug() << "Настройки | Настройки успешно изменены";
    emit close();
}

void Settings::cancelSettingsChanges()
{
    rowsBrowser->setText(QString::number(rows));
    columnsBrowser->setText(QString::number(columns));
    timerSlider->setValue(timer);

    emit close();
}

void Settings::minimumNumberToSurviveChanged(int minimum)
{
    maximumNumberToSurviveField->setRange(minimum, 8);
}
