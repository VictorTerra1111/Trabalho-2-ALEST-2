#include <iostream>
#include "../HPPS/map.hpp"
#include <fstream>
#include <string> 

Mapa::Mapa(const std::string &caminhoArquivo)
{
    carregar(caminhoArquivo);
    achaPortos();
}

void Mapa::carregar(const std::string &caminhoArquivo)
{
    std::ifstream entrada(caminhoArquivo);
    if (!entrada.is_open())
    {
        std::cerr << "ERRO: " << caminhoArquivo << std::endl;
        return;
    }

    entrada >> linhas >> colunas;
    entrada.ignore();

    std::string linha;
    while (std::getline(entrada, linha))
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

const std::vector<std::string> &Mapa::getGrade() const { return grade; }

int Mapa::getLinhas() const { return linhas; }

int Mapa::getColunas() const { return colunas; }

std::map<char, std::pair<int, int>> Mapa::getPortos() const { return portos; }