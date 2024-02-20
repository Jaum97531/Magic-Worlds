#pragma once
#include "../Ente/Entidades/Entidade.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <random>


// Defina a função hash para Type
namespace std {
    template <>
    struct hash<Type> {
        size_t operator()(const Type& valor) const {
            // Use a função hash padrão para enums
            return static_cast<size_t>(valor);
        }
    };
}

// Defina a função hash para std::pair<Type, Type>
namespace std {
    template <>
    struct hash<std::pair<Type, Type>> {
        size_t operator()(const std::pair<Type, Type>& p) const {
            // Combine hashes dos enums do par
            size_t hash1 = std::hash<Type>()(p.first);
            size_t hash2 = std::hash<Type>()(p.second);

            // Simples algoritmo de combinação de hash
            return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
        }
    };
}

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