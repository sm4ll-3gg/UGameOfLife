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
    emit initBinaryMap(rows, columns);

    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < columns; ++j)
        {
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

    connect(this,
            SIGNAL(itemClicked(QTableWidgetItem*)),
            SLOT(switchBackground(QTableWidgetItem*))
            );
}

void Map::switchBackground(QTableWidgetItem* item)
{
    if(item->backgroundColor() == Qt::white)
        item->setBackgroundColor(Qt::red);
    else
        item->setBackgroundColor(Qt::white);
}

void Map::getSettings(int rows, int columns)
{
    if(rowCount() != rows || columnCount() != columns)
    {
        setRowCount(rows);
        setColumnCount(columns);

        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < columns; ++j)
            {
                if(item(i, j) == nullptr)
                {
                    QTableWidgetItem* item = new QTableWidgetItem;
                    item->setBackgroundColor(Qt::white);
                    setItem(i, j, item);
                }
            }
        }
    }
}

void Map::setCellColorByCondition(int row, int column, bool condition)
{
    QTableWidgetItem* tempItem = item(row, column);
    if(condition == false)
        tempItem->setBackgroundColor(Qt::white);
    else tempItem->setBackgroundColor(Qt::red);
}

