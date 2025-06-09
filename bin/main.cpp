#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "../HPPS/map.hpp"
#include "../HPPS/graph.hpp"
#include "../HPPS/graphAssem.hpp"
#include "../HPPS/dijkstra.hpp"
#include "../HPPS/functions.hpp"

using namespace std;

int main() {
    string filePath = "TXTS/mapa100.txt";

    Map mapa(filePath);
    map<char, pair<int, int>> harbors = mapa.getHarbor();

    vector<char> portoIds;
    for (const auto &entry : harbors)
        portoIds.push_back(entry.first);

    sort(portoIds.begin(), portoIds.end());

    map<pair<int, int>, vector<Edge>> rawGraph = assembleDirGraph(mapa);
    Graph graph;
    for (const auto &entry : rawGraph) {
        for (const Edge &e : entry.second)
            graph.addEdge(e.from, e.to, e.weight);
    }

    double totalFuel = 0;
    vector<string> trechos;
    vector<string> portosIgnorados;

    size_t i = 0;
    size_t lastValidIndex = 0;  // Índice do último porto acessível

    while (i < portoIds.size() - 1) {
        size_t nextIndex = i + 1;

        Dijkstra dijkstra(graph, harbors[portoIds[i]]);

        // Pular portos inacessíveis no caminho
        while (nextIndex < portoIds.size() &&
               !dijkstra.hasPathTo(harbors[portoIds[nextIndex]])) {
            portosIgnorados.push_back("Porto " + string(1, portoIds[nextIndex]) + " inacessível – ignorado)");
            ++nextIndex;
        }

        if (nextIndex >= portoIds.size())
            break;

        vector<Edge> path = dijkstra.pathTo(harbors[portoIds[nextIndex]]);
        double cost = calcPathCostWithPenalty(path);
        totalFuel += cost;

        trechos.push_back("Trecho " + string(1, portoIds[i]) + " -> " + string(1, portoIds[nextIndex]) + ": " + to_string((int)cost));
        
        lastValidIndex = nextIndex;  // Atualiza último porto acessível
        i = nextIndex;
    }

    // Retornar ao porto 1 a partir do último porto acessível
    if (!trechos.empty()) {
        char ultimoPorto = portoIds[lastValidIndex];  // último porto acessível
        if (harbors.find('1') != harbors.end() && ultimoPorto != '1') {
            Dijkstra dijkstraBack(graph, harbors[ultimoPorto]);
            if (dijkstraBack.hasPathTo(harbors['1'])) {
                vector<Edge> pathBack = dijkstraBack.pathTo(harbors['1']);
                double costBack = calcPathCostWithPenalty(pathBack);
                totalFuel += costBack;
                trechos.push_back("Trecho " + string(1, ultimoPorto) + " -> 1: " + to_string((int)costBack));
            }
        }
    }

    // Impressão final
    cout << "Mapa " << filePath << " – Combustível mínimo: " << (int)totalFuel << endl;
    for (const string &trecho : trechos)
        cout << trecho << endl;
    for (const string &p : portosIgnorados)
        cout << p << endl;

    return 0;
}
