#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include <map>

using namespace std;

class Mapa
{
    public:
        Mapa(const string &caminhoArquivo);

        const vector<string> &getGrade() const;
        int getLinhas() const;
        int getColunas() const;
        map<char, pair<int, int>> getPortos() const;

    private:
        vector<string> grade;
        int linhas;
        int colunas;
        map<char, pair<int, int>> portos;

        void carregar(const string &caminhoArquivo);
        void achaPortos();
};

#endif
