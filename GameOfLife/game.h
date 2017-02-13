#ifndef Game_H
#define Game_H

#include "map.h"

#include <QObject>
#include <QVector>

class Game : public QObject
{
    Q_OBJECT

public:
    enum CellCondition { DEAD = 0, LIVE = 1 };
    enum GameCondition { BEFOTRE_GAME = 0, DURING_THE_GAME = 1 };

    Game();

private: // methods
    void            step();
    CellCondition   come_to_live(int i, int j); // condition - текущее состояние клетки
    int             check_around(int row, int column);
    bool            is_correct_cords(int i, int j);

signals:
    void            setCellColorByCondition(int row, int column, bool condition);

private slots:
    void            initBinaryMap(int rows, int columns);
    void            switchCellCondition(int row, int column);
    void            getSettings(int rows, int columns);
    void            switchGameCondition(GameCondition newCondition);
    void            nextSnapshot();

private:
    typedef QVector<QVector<CellCondition> > BinaryMap;

    int             rows;
    int             columns;

    GameCondition   condition;
    BinaryMap       map;
};

#endif // Game_H
