#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <string>
#include "edge.hpp"
#include "minHeapNode.hpp"
#include "graph.hpp"

using namespace std;

class Dijkstra
{
public:
    Dijkstra(const Graph &vgraph, pair<int, int> source);
    // recebe o grafo e o vertice de origem

    bool hasPathTo(const pair<int, int> &v) const;
    // existe caminho da origem ateh 'v'?

    double distTo(const pair<int, int> &v) const;
    // menor distancia origem-v

    vector<Edge> pathTo(const pair<int, int> &v) const;
    // vector de arestas do caminho de origem-v

private:
    void relax(const Edge &e);
    // atualiza distTo

    map<pair<int, int>, Edge> edgeToMap;

    map<pair<int, int>, double> distToMap;

    priority_queue<minHeapNode, vector<minHeapNode>, greater<minHeapNode>> pq;
    // filha com prioridade: menor custo

    map<pair<int, int>, vector<Edge>> graph; // grafo (um mapa de coordenada e um vector de arestas)

};

#endif
