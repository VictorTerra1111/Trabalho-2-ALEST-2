#ifndef MIN_HEAP_NODE_HPP
#define MIN_HEAP_NODE_HPP

#include <utility>

class minHeapNode {
public:
    std::pair<int, int> vertex;
    double priority;

    minHeapNode(std::pair<int, int> v = {0, 0}, double p = 0.0)
        : vertex(v), priority(p) {}

    bool operator>(const minHeapNode &other) const {
        return priority > other.priority;
    }
};

#endif
