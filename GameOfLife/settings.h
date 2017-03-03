#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QSettings>
#include <QSpinBox>

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

signals:
    void            sendSettings(QSettings& settings);
    void            close();

private slots:
    void            getSettingsRequest();
    void            saveSettings();
    void            cancelSettingsChanges();
    void            minimumNumberToSurviveChanged(int minimum);

private:
    bool            isNumber(const QString& string);

    void            readSettings();
    void            writeSettings();

private:
    QSettings       settings;
    int             rows;
    int             columns;
    int             timer;
    short           numberToAlive;
    short           minimumNumberToSurvive;
    short           maximumNumberToSurvive;

    QGridLayout*    mainLayout;

    QLabel*         mapSize;

    QHBoxLayout*    rowsLayout;
    QLabel*         rowsText;
    QLineEdit*      rowsBrowser;
    QLabel*         rowsUncorrectValue;

    QHBoxLayout*    columnsLayout;
    QLabel*         columnsText;
    QLineEdit*      columnsBrowser;
    QLabel*         columnsUncorrectValue;

    QLabel*         timerBrowser;
    QSlider*        timerSlider;
    QLabel*         timerValue;

    QGridLayout*    gameSettingsLayout;
    QLabel*         gameSettingsHeader;
    QHBoxLayout*    numberToAliveLayout;
    QLabel*         numberToAliveLabel;
    QSpinBox*       numberToAliveField;
    QHBoxLayout*    numberToSurviveLayout;
    QLabel*         numberToSurviveFromLabel;
    QSpinBox*       minimumNumberToSurviveField;
    QLabel*         numberToSurviveToLabel;
    QSpinBox*       maximumNumberToSurviveField;

    QSpacerItem*    spacer;

    QHBoxLayout*    CancelAndApplyLayout;
    QPushButton*    apply;
    QPushButton*    cancel;
};

#endif // SETTINGS_H
