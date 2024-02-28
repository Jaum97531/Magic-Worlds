#pragma once
#include "../Ente.hpp"
#include "../../Gerenciadores/GerenciadorColisoes.hpp"
#include "../../Gerenciadores/GerenciadorEstados.hpp"
#include "../../Gerenciadores/Animacao.hpp"
#include "../../Gerenciadores/Observer/Observador.hpp"
#include <vector>
#include <string>
#include <map>

/*
        Estados: 
    0 - Menu inicial;
    1 - Selecionar Jogadores;
    2 - Selecionar fase;
    3 - Fase 1;
    4 - Fase 2;
    5 - Rank;
    6 - Pausa;
    7 - GameOver;
    8 - Wins;

*/

namespace states{
    class Estado : public Ente, public Observador{
        protected:
            GR::GerenciadorColisao* pColisao;
            GR::GerenciadorEstados* pEstados;
            sf::View* pView;
            sf::CircleShape mouse;
            
            Animacao animacao;
            sf::Texture textura;
            sf::RectangleShape background;

            std::vector<sf::Text> textos;
            std::vector<sf::Text> titulos; 
            std::map<std::string, std::pair<sf::Vector2f, sf::RectangleShape>> utilits;

        public:
            Estado();
            ~Estado();

            sf::Text getTexto(int i) const { return textos[i]; }
            
            virtual void desenhar();
            virtual void tratarSelecao(sf::String){}
            virtual void tratarSelecao(){}
            virtual void selecionar();

            void desenharTexto();
            void desenharUtilits();
            virtual void execute() = 0;
            virtual void encerrarEstado();
            virtual void iniciarEstado();
            virtual void notifica(int tipo);

            virtual void resized() = 0;

            virtual void criarUtilits(){}

            sf::RectangleShape criarShapeTextura(std::string textura, sf::Vector2f size, sf::Vector2f posicao, bool repeated);
            sf::Text criarTexto(std::string texto, int size, sf::Vector2f posicao, sf::Color cor);
    };
}