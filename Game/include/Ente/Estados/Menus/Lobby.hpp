#pragma once
#include "Menu.hpp"
#include "../../Entidades/Personagens/Jogador.hpp"
#include "../../Entidades/Objetos/Plataforma.hpp"
#include "../../../Gerenciadores/ListaEntidades.hpp"
#include <vector>


namespace states{
    class Lobby : public Menu{
        private:
            Entidades::Personagens::Jogador* jogador;    
            ListaEntidades listaEntidades;

            std::string strNome;
            sf::Text nomeJogador;
            bool digitando;

        public:
            Lobby();
            ~Lobby();

            void tratarSelecao(sf::String selecao);
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
            void resized();
    };
}