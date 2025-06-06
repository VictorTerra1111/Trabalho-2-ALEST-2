#include <iostream>
#include <fstream>
#include <string> 
#include "../HPPS/map.hpp"

using namespace std;

Mapa::Mapa(const string &caminhoArquivo)
{
    carregar(caminhoArquivo);
    achaPortos();
}

void Mapa::carregar(const string &caminhoArquivo)
{
    string linha; 
    ifstream entrada(caminhoArquivo);
    if (!entrada.is_open())
    {
        cerr << "ERRO: " << caminhoArquivo << endl;
        return;
    }

    entrada >> linhas >> colunas;
    entrada.ignore(); // para limpar lina nova

    while (getline(entrada, linha))
    {
        if (!linha.empty())
        {
            grade.push_back(linha);
        }
    }
    entrada.close();
}

void Mapa::achaPortos()
{
    for (int i = 0; i < grade.size(); ++i)
    {
        for (int j = 0; j < grade[i].size(); ++j)
        {
            char c = grade[i][j];
            if (c >= '1' && c <= '9')
            {
                portos[c] = {i, j};
            }
        }
    }
}

const vector<string> &Mapa::getGrade() const { return grade; }

int Mapa::getLinhas() const { return linhas; }

int Mapa::getColunas() const { return colunas; }

map<char, pair<int, int>> Mapa::getPortos() const { return portos; }