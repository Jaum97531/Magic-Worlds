#pragma once
#include "../Ente/Entidades/Entidade.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <random>


class Algoritimos{
  private:
    std::random_device rd;
    std::mt19937 gen;

    static Algoritimos* instancia;

    Algoritimos(){ }
  public:
    static Algoritimos* getInstancia();   
    ~Algoritimos(){}
  

    static void trocar(std::pair<std::string, int> &a, std::pair<std::string, int> &b);
    static int particionar(std::vector<std::pair<std::string, int>> &vetor, int baixo, int alto);
    static void quicksort(std::vector<std::pair<std::string, int>> &vetor, int baixo, int alto);
    static std::mt19937& getGenerator() { return getInstancia()->gen; }
};