#include "game.h"

#include <cstdlib>
#include <ctime>

Life::Life()
{
    condition = GameCondition::BEFOTRE_GAME;
}

//void Life::step()
//{
//    Map temp_map;

//    for(size_t i = 0; i < map.size(); i++)
//    {
//        temp_map.push_back(std::vector<bool>(map[i].size()));

//        for(size_t j = 0; j < map[i].size(); j++)
//        {
//            temp_map[i][j] = come_to_live(i, j);
//        }
//    }


//    if(map != temp_map)
//        map = temp_map;
//    else
//    {
//        clear();
//        mvaddstr(0,0,"Game OVER! ;(");
//    }
//    print();
//}

//bool Life::come_to_live(int i, int j)
//{
//    int number = check_around(i, j);

//    if(map[i][j]) // если клетка жива
//    {
//        if(number == 2 || number == 3) return true; // остается живой
//    }
//    else
//        if(number == 3) return true; // оживает

//    return false; // умирает / остается мертвой
//}

//int Life::check_around(int _i, int _j)
//{
//    int count = 0;

//    for(int i = _i - 1; i <= _i + 1; ++i)
//    {
//        for(int j = _j - 1; j <= _j + 1; ++j)
//        {
//            if(is_correct_cords(i, j))
//            {
//                if(map[i][j]) count++;
//            }
//        }
//    }

//    return count;
//}

//bool Life::is_correct_cords(int i, int j)
//{
//    return i >= 0 && i < map.size() && j >= 0 && j < map[0].size();
//}

//void Life::print()
//{
//    for(size_t i = 0; i < map.size(); ++i)
//    {
//        for(size_t j = 0; j < map[i].size(); ++j)
//        {
//            if(map[i][j])
//                mvaddch(i, j, '#' | COLOR_PAIR(1));
//            else
//                mvaddch(i, j, ' ' | COLOR_PAIR(0));

//        }
//    }
//}
