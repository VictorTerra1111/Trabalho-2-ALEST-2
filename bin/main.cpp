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

    // Novo grafo entre portos, com custos reais e penalidade de curvas
    Graph portoGraph = buildHarborGraph(mapa, harbors);

    double totalFuel = 0;
    vector<string> trechos;
    vector<string> portosIgnorados;

    size_t i = 0;
    size_t lastValidIndex = 0;

    while (i < portoIds.size() - 1) {
        size_t nextIndex = i + 1;

        Dijkstra dijkstra(portoGraph, harbors[portoIds[i]]);

        while (nextIndex < portoIds.size() &&
               !dijkstra.hasPathTo(harbors[portoIds[nextIndex]])) {
            portosIgnorados.push_back("Porto " + string(1, portoIds[nextIndex]) + " inacessível – ignorado)");
            ++nextIndex;
        }

        if (nextIndex >= portoIds.size())
            break;

        vector<Edge> path = dijkstra.pathTo(harbors[portoIds[nextIndex]]);
        double cost = 0.0;

        for (const auto& e : path)
            cost += e.weight;

        totalFuel += cost;

        trechos.push_back("Trecho " + string(1, portoIds[i]) + " -> " + string(1, portoIds[nextIndex]) + ": " + to_string((int)cost));

        lastValidIndex = nextIndex;
        i = nextIndex;
    }

    // Voltar ao porto '1' se possível
    if (!trechos.empty()) {
        char ultimoPorto = portoIds[lastValidIndex];
        if (harbors.find('1') != harbors.end() && ultimoPorto != '1') {
            Dijkstra dijkstraBack(portoGraph, harbors[ultimoPorto]);
            if (dijkstraBack.hasPathTo(harbors['1'])) {
                vector<Edge> pathBack = dijkstraBack.pathTo(harbors['1']);
                double costBack = 0.0;
                for (const auto& e : pathBack)
                    costBack += e.weight;

                totalFuel += costBack;
                trechos.push_back("Trecho " + string(1, ultimoPorto) + " -> 1: " + to_string((int)costBack));
            }
        }
    }

    cout << "Mapa " << filePath.substr(filePath.find_last_of("/\\") + 1)
         << " – Combustível mínimo: " << (int)totalFuel << endl;

    for (const string &trecho : trechos)
        cout << trecho << endl;

    for (const string &p : portosIgnorados)
        cout << p << endl;

    return 0;
}
