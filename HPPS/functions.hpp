#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

using namespace std;

enum class Direction{
    North,
    South,
    East, 
    West,
    Null
};

Direction whatDir(pair<int, int> s, pair<int, int> t);

int changedDir(Direction bef, Direction now);

#endif