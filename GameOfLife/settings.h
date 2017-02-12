#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QGridLayout>

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private:
    QGridLayout* mainLayout;
};

#endif // SETTINGS_H
