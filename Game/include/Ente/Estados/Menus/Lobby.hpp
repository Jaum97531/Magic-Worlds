#pragma once
#include "Menu.hpp"
#include "../../Entidades/Personagens/Jogador.hpp"
#include "../../Entidades/Objetos/Plataforma.hpp"
#include <vector>


namespace states{
    class Lobby : public Menu{
        private:
            Entidades::Personagens::Jogador* jogador;    
            std::vector<Entidades::Entidade*> listaEntidades;

            std::string strNome;
            sf::Text nomeJogador;
            bool digitando;

        public:
            Lobby();
            ~Lobby();

            void tratarSelecao(sf::String selecao);
            Entidades::Personagens::Jogador* getJog() { return jogador; }
            void desenhar();
            void criarUtilits();
            void criaEnt();
            void execute();
            void verificaJogador();
            void iniciarTextos() override;
            void iniciarEstado();
            void selecionar();
            void encerrarEstado();
            void digitar();
            void notifica(int tipo) override;
            void carregarFaseSalva();
    };
}