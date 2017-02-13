#include "game.h"

#include <QDebug>

Game::Game()
{
    condition = GameCondition::BEFOTRE_GAME;
}

void Game::initBinaryMap(int rows, int columns)
{
    for(int i = 0; i < rows; ++i)
    {
        map.push_back(QVector<CellCondition>());
        for(int j = 0; j < columns; ++j)
        {
            map[i].push_back(CellCondition::DEAD);
        }
    }
}

void Game::switchCellCondition(int row, int column)
{
    if(condition == GameCondition::DURING_THE_GAME)
    {
        qDebug() << "Логика | Попытка изменения ячейки во время игры";
        return;
    }

    if(map[row][column] == CellCondition::DEAD)
        map[row][column] = CellCondition::LIVE;
    else
        map[row][column] = CellCondition::DEAD;
}

void Game::getSettings(int _rows, int _columns)
{
    if(rows != _rows || columns != _columns)
    {
        rows = _rows;
        columns = _columns;

        map.resize(rows);
        for(auto it = map.begin(); it != map.end(); ++it) it->resize(columns);
    }
}

void Game::switchGameCondition(Game::GameCondition newCondition)
{
    condition = newCondition;
}

void Game::nextSnapshot()
{
    step();
}

void Game::step()
{
    BinaryMap temp_map;

    for(int i = 0; i < map.size(); ++i)
    {
        temp_map.push_back(QVector<CellCondition>(map[i].size()));
        for(int j = 0; j < map[i].size(); j++)
        {
            temp_map[i][j] = come_to_live(i, j);
        }
    }

    map = temp_map;

    for(int i = 0; i < map.size(); ++i)
    {
        for(int j = 0; j < map[i].size(); ++j)
        {
            emit setCellColorByCondition(i, j, map[i][j]);
        }
    }
}

Game::CellCondition Game::come_to_live(int row, int column)
{
    int number = check_around(row, column); // Количество живых клеток вокруг

    if(map[row][column] == CellCondition::LIVE) // если клетка жива
    {
        if(number == 2 || number == 3) return CellCondition::LIVE; // остается живой
    }
    else
        if(number == 3) return CellCondition::LIVE; // оживает

    return CellCondition::DEAD; // умирает / остается мертвой
}

int Game::check_around(int row, int column)
{
    int count = 0;

    for(int i = row - 1; i <= row + 1; ++i)
    {
        for(int j = column - 1; j <= column + 1; ++j)
        {
            if(is_correct_cords(i, j))
            {
                if(map[i][j] == CellCondition::LIVE && (i != row ||  j != column))
                    count++;
            }
        }
    }

    return count;
}

bool Game::is_correct_cords(int i, int j)
{
    return i >= 0 && i < map.size() && j >= 0 && j < map[0].size();
}
