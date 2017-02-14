#ifndef MAP_H
#define MAP_H

#include <QTableWidget>
#include <QVector>

class Map : public QTableWidget
{
    Q_OBJECT

public:
    Map(QWidget* parent = nullptr);
    Map(int rows, int columns, QWidget* parent = nullptr);

private: // methods
    void init();

signals:
    void initBinaryMap(int rows, int columns);
    void settingsRequest(int rows, int columns);

private slots:
    void switchBackground(int row, int column);
    void getSettings(int rows, int columns);
    void setCellColorByCondition(int row, int column, bool condition);
};

#endif // MAP_H
