#include "map.h"

#include <QHeaderView>

Map::Map(QWidget* parent)
    :QTableWidget(parent)
{
    init();
}

Map::Map(int rows, int columns, QWidget *parent)
    :QTableWidget(rows, columns, parent)
{
    connect(this,
            SIGNAL(cellClicked(int, int)),
            SLOT(switchCellCondition(int, int))
            );

    connect(this,
            SIGNAL(itemClicked(QTableWidgetItem*)),
            SLOT(switchBackground(QTableWidgetItem*))
            );

    for(int i = 0; i < rows; ++i)
    {
        map.push_back(QVector<CellCondition>());
        for(int j = 0; j < columns; ++j)
        {
            map[i].push_back(CellCondition::DEAD);

            QTableWidgetItem* item = new QTableWidgetItem;
            item->setBackgroundColor(Qt::white);
            setItem(i, j, item);
        }
    }
    init();
}

void Map::init()
{
    setSelectionMode(QAbstractItemView::NoSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->hide();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->hide();
}

void Map::switchCellCondition(int row, int column)
{
    // Если игра еще не началась
    if(map[row][column] == CellCondition::DEAD)
        map[row][column] = CellCondition::LIVE;
    else
        map[row][column] = CellCondition::DEAD;
}

void Map::switchBackground(QTableWidgetItem* item)
{
    if(item->backgroundColor() == Qt::white)
        item->setBackgroundColor(Qt::red);
    else
        item->setBackgroundColor(Qt::white);
}
