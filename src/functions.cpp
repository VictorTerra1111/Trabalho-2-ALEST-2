#include <iostream>
#include "../HPPS/functions.hpp"

Direction whatDir(pair<int, int> s, pair<int, int> t){
    int x = t.first - s.first;
    int y = t.second - s.second;
    if(x == -1 && !y)   return Direction::North;
    if(x && !y)         return Direction::South;
    if(!x && y)         return Direction::East;
    if(!x && y == -1)   return Direction::West;
    return Direction::Null;
}

int changedDir(Direction bef, Direction now){
    if(bef == Direction::Null || bef == now){
        return 0;
    }
    return 3;
}
