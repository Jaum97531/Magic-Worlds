#pragma once
#include "Animacao.hpp"

#define PARADO 0
#define CORRENDO 1
#define ANDANDO 2
#define ATACANDO 3
#define MORRENDO 4
#define EFEITO 5

namespace Entidades{
    namespace Personagens{
        class Jogador;
    };
}

namespace GR{
    class GerenciadorAnimacao {
        public:
            static GerenciadorAnimacao* instancia;

        // ---------------  RELACIONADA A JOGADOR ------------------//
            Entidades::Personagens::Jogador* jogador; 
            int ultimaAnimacaoJogador;
            Animacao animaAndando;
            Animacao animaCorrendo;
            Animacao animaAtacando;
            Animacao animaMorrendo;
            Animacao animaParado;
            Animacao animaEfeito;
        //----------------------------------------------------------------//

        //----------------- LAVAS ----------------------------------------//
            Animacao animaLavas;
            std::vector<sf::RectangleShape*> vetorDeLavas;
            sf::Clock relogioLavas;
        //---------------------------------------------------------------//
            GerenciadorAnimacao(Entidades::Personagens::Jogador* jog);
        public:
            static GerenciadorAnimacao* getInstacia(Entidades::Personagens::Jogador* jog);
            ~GerenciadorAnimacao();

            void criarAnimacoesJogador();
            void criarAnimacaoLava();
            void trocaAnimacaoJogador(sf::String elemento);
            void animarEfeitoJogador();
            void morrendo();
            void atualizarJogador(int estado);
            void resetarAnimacaoJogador(int estado);
            void pushLava(sf::RectangleShape* lava) { vetorDeLavas.push_back(lava); }
            void atualizaLavas();
    };
}