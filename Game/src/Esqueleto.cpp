#include "../include/Ente/Entidades/Personagens/Inimigos/Esqueleto.hpp"


Entidades::Personagens::Esqueleto::Esqueleto() {
    animaAndando.criaFrames("ESQUELETO ANDANDO", 20, false);
    addTipoSecundario(Type::Esqueleto);
    corpo.setSize(sf::Vector2f(75, 65));
    velocidade = sf::Vector2f(10, 0);
    vida = 70;
    nvlMaldade = 50;
}

Entidades::Personagens::Esqueleto::~Esqueleto(){

}