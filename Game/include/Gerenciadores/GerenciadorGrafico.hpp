#pragma once
#include <SFML/Graphics.hpp>
#include "GerenciadorImagens.hpp"
#include <random>

const sf::Color AZULVERDE(72,209,204);
const sf::Color CYANO(0,255,255);
const sf::Color CYANOCLARO(224,255,255);
const sf::Color AMARELORAIO(240,230,140);
const sf::Color MARROM(139,69,19);

const sf::Color TERRA(139,69,19);
const sf::Color VENTO(176,224,230);
const sf::Color AGUA(0,139,139);
const sf::Color FOGO(139,0,0);

const sf::Color TERRA_SELECIONADO(210,105,30);
const sf::Color AGUA_SELECIONADO(102,205,170);
const sf::Color FOGO_SELECIONADO(255,0,0);
const sf::Color VENTO_SELECIONADO(245,255,250);

class Ente;

namespace GR{

    class GerenciadorGrafico{
        private:
            sf::RenderWindow* janela;
            sf::Font* fonte;
            GerenciadorImagens* pImagens;

            static GerenciadorGrafico* instancia;
            sf::View camera;

            GerenciadorGrafico();

        public:

            ~GerenciadorGrafico();

            sf::Font* getFont() const { return fonte; }

            static GerenciadorGrafico* getInstancia();
            sf::RenderWindow* getJanela() const { return janela; }
            GerenciadorImagens* getPimagens() { return pImagens; }

            void fecharJanela();
            void limpar();
            const bool janelaAberta() const;
            void mostrar();
            int get_JANELAX() { return janela->getSize().x; }
            int get_JANELAY(){ return janela->getSize().y; }
            
            void centralizarCamera(sf::Vector2f pos);
            sf::View* getCamera() { return &camera; }
            
            void desenhar(Ente* ent);

            void draw(sf::RectangleShape shape) { janela->draw(shape); }
            void draw(sf::CircleShape shape) { janela->draw(shape); }
            void draw(sf::Text text) { janela->draw(text); }
    };

}