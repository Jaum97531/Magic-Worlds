#include "../include/Gerenciadores/Algoritimos.hpp"

Algoritimos* Algoritimos::instancia = nullptr;
Algoritimos* Algoritimos::getInstancia(){
    if(instancia == nullptr){ instancia = new Algoritimos(); }
    return instancia;
}


// Função para trocar dois elementos em um vetor
void Algoritimos::trocar(std::pair<std::string, int> &a, std::pair<std::string, int> &b) {
    std::swap(a, b);
}

// Função para encontrar o pivo e particionar o vetor
int Algoritimos::particionar(std::vector<std::pair<std::string, int>> &vetor, int baixo, int alto) {
    int pivo = vetor[alto].second; // Segundo elemento do par como pivo
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (vetor[j].second >= pivo) {
            i++;
            trocar(vetor[i], vetor[j]);
        }
    }

    trocar(vetor[i + 1], vetor[alto]);
    return (i + 1);
}

// Função principal de Quicksort
void Algoritimos::quicksort(std::vector<std::pair<std::string, int>> &vetor, int baixo, int alto) {
    if (baixo < alto) {
        int indice_pivo = particionar(vetor, baixo, alto);
        quicksort(vetor, baixo, indice_pivo - 1);
        quicksort(vetor, indice_pivo + 1, alto);
    }
}