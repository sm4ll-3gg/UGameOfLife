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

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private:
    bool            isNumber(const QString& string);

signals:
    void            sendSettings(int rows, int columns, int timer);
    void            close();

private slots:
    void            getSettingsRequest();
    void            saveSettings();
    void            cancelSettingsChanges();

private:
    int             rows;
    int             columns;
    int             timer;

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

    QSpacerItem*    spacer;

    QHBoxLayout*    CancelAndApplyLayout;
    QPushButton*    apply;
    QPushButton*    cancel;
};

#endif // SETTINGS_H
