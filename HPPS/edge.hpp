#ifndef EDGE_HPP
#define EDGE_HPP

#include <vector>

using namespace std;

class Edge
{
public:
    pair<int, int> from;
    pair<int, int> to;
    double weight;

    Edge() : from({0, 0}), to({0, 0}), weight(0.0) {}
    
    Edge(pair<int, int> v, pair<int, int> w, double wt)
        : from(v), to(w), weight(wt) {}
};


#endif