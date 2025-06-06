#include <iostream>
#include "../HPPS/functions.hpp"

Direcao qualDir(pair<int, int> ori, pair<int, int> dest){
    int x = dest.first - ori.first;
    int y = dest.second - ori.second;
    if(x == -1 && !y)   return Direcao::Norte;
    if(x && !y)         return Direcao::Sul;
    if(!x && y)         return Direcao::Leste;
    if(!x && y == -1)   return Direcao::Oeste;
    return Direcao::Null;
}

int trocou(Direcao bef, Direcao now){
    if(bef == Direcao::Null || bef == now){
        return 0;
    }
    return 3;
}
