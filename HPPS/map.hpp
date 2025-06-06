#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include <map>

using namespace std;

class Mapa
{
public:
    Mapa(const std::string &caminhoArquivo);

    const std::vector<std::string> &getGrade() const;
    int getLinhas() const;
    int getColunas() const;
    std::map<char, std::pair<int, int>> getPortos() const;

private:
    std::vector<std::string> grade;
    int linhas;
    int colunas;
    std::map<char, std::pair<int, int>> portos;

    void carregar(const std::string &caminhoArquivo);
    void achaPortos();
};

#endif
