#ifndef MIN_HEAP_NODE_HPP
#define MIN_HEAP_NODE_HPP

#include <vector>

using namespace std;

class minHeapNode
{
public:
    pair<int, int> vertex;
    double priority;

    bool operator>(const minHeapNode &other) const
    {
        return priority > other.priority;
    }
};

#endif