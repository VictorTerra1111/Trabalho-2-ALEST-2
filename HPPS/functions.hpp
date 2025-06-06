#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

using namespace std;

enum class Direcao{
    Norte,
    Sul,
    Leste, 
    Oeste,
    Null
};

Direcao qualDir(pair<int, int> ori, pair<int, int> dest);

int trocou(Direcao bef, Direcao now);

#endif