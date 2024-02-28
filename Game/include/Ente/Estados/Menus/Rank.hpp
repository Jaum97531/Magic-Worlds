#pragma once
#include "Menu.hpp"
#include <fstream>


namespace states{
    class Rank : public Menu{
        private:
            sf::RectangleShape placa;
            sf::RectangleShape placa2;

        public:
            Rank();
            ~Rank();

            std::vector<std::pair<std::string, std::string>> criaNomesPts();

            void iniciarTextos() override;
            void iniciarEstado();
            void tratarSelecao(sf::String selecao);
            void desenhar();
            void abrirArquivo();
            std::vector<std::pair<std::string, std::string>> organizarPontos(std::vector<std::pair<std::string, std::string>> nome_pontos);
            void completarComPontos(int i);
            void reorganizarArquivoRank(std::vector<std::pair<std::string, std::string>> vetor_nomes_pontos);
            void salvarPontuacao(std::string nome, int pontos);
    };
}