#ifndef Game_H
#define Game_H

#include "map.h"

#include <QObject>
#include <QVector>
#include <QStack>
#include <QSettings>

class Game : public QObject
{
    Q_OBJECT

public:
    enum class CellCondition { DEAD = 0, LIVE = 1 };
    enum class GameCondition { BEFOTRE_GAME = 0, DURING_THE_GAME = 1 };

    Game();

private: // methods
    typedef QVector<QVector<CellCondition> > BinaryMap;

    void                initMap(BinaryMap& map, int rows, int columns);
    void                updateSnapshot();

    // Игровая логика
    void                step();
    CellCondition       come_to_live(int i, int j); // condition - текущее состояние клетки
    int                 check_around(int row, int column);
    bool                is_correct_cords(int i, int j);

signals:
    void                setCellColorByCondition(int row, int column, bool condition);
    void                gameConditionSwitched(Game::GameCondition condition);
    void                cellClicked(int row, int column);

private slots:
    void                initBinaryMap(int rows, int columns);
    void                switchCellCondition(int row, int column);
    void                getSettings(QSettings& settings);
    void                firstSnapshot();
    void                prevSnapshot();
    void                nextSnapshot();
    void                switchGameConditon();
    void                clear();

private:
    int                 rows;
    int                 columns;
    int                 timerStep;
    short               numberToAlive;
    short               minimumNumberToSurvive;
    short               maximumNumberToSurvive;

    int                 count; // Номер поколения

    GameCondition       condition;
    BinaryMap           firstMap; // Карта первого поколения
    QStack<BinaryMap>   prevMaps; // Карты всех предыдущих поколений
    BinaryMap           currentMap; // Карта текущего поколения

    QTimer*             timer;
};

#endif // Game_H
