#ifndef LIFE_H
#define LIFE_H

#include "map.h"

#include <QVector>

class Life
{
public:
    enum GameCondition { BEFOTRE_GAME, DURING_THE_GAME };

    Life();

    void    step();

private: // methods
    bool    come_to_live(int i, int j); // condition - текущее состояние клетки
    int     check_around(int i, int j);

    bool    is_correct_cords(int i, int j);

private:
    GameCondition condition;
};

#endif // LIFE_H
