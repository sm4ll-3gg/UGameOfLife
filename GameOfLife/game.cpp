#include "game.h"

#include <QTimer>
#include <QDebug>

Game::Game()
{
    condition = GameCondition::BEFOTRE_GAME;
    count = 1;

    timer = new QTimer(this);
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextSnapshot()));
}

void Game::initMap(Game::BinaryMap &map, int rows, int columns)
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

void Game::updateSnapshot()
{
    for(int i = 0; i < currentMap.size(); ++i)
    {
        for(int j = 0; j < currentMap[i].size(); ++j)
        {
            CellCondition currCondition = currentMap[i][j];

            if(currCondition == CellCondition::LIVE)
                emit setCellColorByCondition(i, j, true);
            else
                emit setCellColorByCondition(i, j, false);
        }
    }
}

void Game::initBinaryMap(int rows, int columns)
{
    initMap(firstMap, rows, columns);
    initMap(currentMap, rows, columns);
}

void Game::switchCellCondition(int row, int column)
{
    if(condition == GameCondition::DURING_THE_GAME)
    {
        qDebug() << "Логика | Попытка изменения ячейки во время игры";
        return;
    }

    if(currentMap[row][column] == CellCondition::DEAD)
        currentMap[row][column] = CellCondition::LIVE;
    else
        currentMap[row][column] = CellCondition::DEAD;

    emit cellClicked(row, column);
}

void Game::getSettings(QSettings &settings)
{
    settings.beginGroup("/Settings");
    int _rows = settings.value("/rows", rows).toInt();
    int _columns = settings.value("/columns", columns).toInt();
    int _timer = settings.value("/timer_delay", timerStep).toInt();
    numberToAlive = settings.value("/number_to_alive", numberToAlive).toInt();
    minimumNumberToSurvive = settings.value("/minimum_number_to_survive", minimumNumberToSurvive).toInt();
    maximumNumberToSurvive = settings.value("/maximum_number_to_survive", maximumNumberToSurvive).toInt();
    settings.endGroup();

    if(rows != _rows || columns != _columns)
    {
        qDebug() << "Логика | Настройки успешно получены";

        rows = _rows;
        columns = _columns;

        currentMap.resize(rows);
        for(auto it = currentMap.begin(); it != currentMap.end(); ++it) it->resize(columns);
    }

    timerStep = _timer;
    timer->setInterval(timerStep);
}

void Game::firstSnapshot()
{
    if(count > 1)
    {
        currentMap = firstMap;
        prevMaps.clear();
        count = 1;
        updateSnapshot();
    }
    else return;
}

void Game::prevSnapshot()
{
    if(!prevMaps.isEmpty())
    {
        currentMap = prevMaps.pop();
        count--;
        updateSnapshot();
    }
    else
    {
        qDebug() << "Логика | Попытка вернуться из первого поколения";
        return;
    }
}

void Game::nextSnapshot()
{
    if(!prevMaps.isEmpty())
    {
        if(currentMap == prevMaps.top())
        {
            qDebug() << "Логика | Развитие зашло в тупик";
            if(condition == GameCondition::DURING_THE_GAME) switchGameConditon();
        }
    }

    if(count == 1) firstMap = currentMap;
    prevMaps.push(currentMap);
    count++;

    step();
}

void Game::switchGameConditon()
{
    if(condition == GameCondition::BEFOTRE_GAME)
    {
        qDebug() << "Логика | Игра начата/возобновлена";

        condition = GameCondition::DURING_THE_GAME;
        emit gameConditionSwitched(condition);
        timer->start();
    }
    else
    {
        qDebug() << "Логика | Игра остановлена";

        condition = GameCondition::BEFOTRE_GAME;
        emit gameConditionSwitched(condition);
        timer->stop();
    }
}

void Game::clear()
{
    prevMaps.clear();
    firstMap.clear();
    currentMap.clear();
}

void Game::step()
{
    BinaryMap temp_map;

    for(int i = 0; i < currentMap.size(); ++i)
    {
        temp_map.push_back(QVector<CellCondition>(currentMap[i].size()));
        for(int j = 0; j < currentMap[i].size(); j++)
        {
            temp_map[i][j] = come_to_live(i, j);
        }
    }

    currentMap = temp_map;

    updateSnapshot();
}

Game::CellCondition Game::come_to_live(int row, int column)
{
    int number = check_around(row, column); // Количество живых клеток вокруг

    if(currentMap[row][column] == CellCondition::LIVE) // если клетка жива
    {
        if(number >= minimumNumberToSurvive && number <= maximumNumberToSurvive) return CellCondition::LIVE; // остается живой
    }
    else
        if(number == numberToAlive) return CellCondition::LIVE; // оживает

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
                if(currentMap[i][j] == CellCondition::LIVE && (i != row ||  j != column))
                    count++;
            }
        }
    }

    return count;
}

bool Game::is_correct_cords(int i, int j)
{
    return i >= 0 && i < currentMap.size() && j >= 0 && j < currentMap[0].size();
}
