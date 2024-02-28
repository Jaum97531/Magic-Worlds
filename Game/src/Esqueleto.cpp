#include "../include/Ente/Entidades/Personagens/Inimigos/Esqueleto.hpp"


Entidades::Personagens::Esqueleto::Esqueleto() {
    animaAndando.criaFrames("ESQUELETO ANDANDO", 20, true);
    tipos[Type::Esqueleto] = true;
    corpo.setSize(sf::Vector2f(75, 65));
    velocidade = sf::Vector2f(5, 0);
    vida = 70;
    nvlMaldade = 50;
    animaAndando.anima(&corpo, true, true);
}

Entidades::Personagens::Esqueleto::~Esqueleto(){

}