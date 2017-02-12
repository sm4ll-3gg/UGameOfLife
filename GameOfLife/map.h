#ifndef MAP_H
#define MAP_H

#include <QTableWidget>
#include <QVector>

class Map : public QTableWidget
{
    Q_OBJECT

public:
    enum CellCondition { DEAD = 0, LIVE = 1 };

    Map(QWidget* parent = nullptr);
    Map(int rows, int columns, QWidget* parent = nullptr);

private: // methods
    void init();

public slots:
    void switchCellCondition(int row, int column);
    void switchBackground(QTableWidgetItem* item);

private:
    typedef QVector<QVector<CellCondition> > BinaryMap;

    BinaryMap map;
};

#endif // MAP_H
