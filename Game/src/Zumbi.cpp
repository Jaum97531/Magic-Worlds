#include "../include/Ente/Entidades/Personagens/Inimigos/Zumbi.hpp"

bool Entidades::Personagens::Zumbi::CACANDO = false;
Entidades::Personagens::Zumbi::Zumbi(){
    animaAndando.criaFrames("ZUMBI ANDANDO", 12, false);
    tipos[Type::Zumbi] = true;
    corpo.setSize(sf::Vector2f(70, 70));
    velocidade = sf::Vector2f(7, 0);
    vida = 70;
    nvlMaldade = 70;
    animaAndando.anima(&corpo, true);
}

Entidades::Personagens::Zumbi::~Zumbi(){

}

void Entidades::Personagens::Zumbi::execute(){
    movimento = sf::Vector2f(0, 0);
    if(CACANDO) { estado = PERSEGUINDO; }
    
    aplicarEstadoFisico();

    determinaDirecao();

    move();

    corpo.move(sf::Vector2f(movimento.x, gravidade + movimento.y));
    
    bool animou = animaAndando.anima(&corpo, direcao, false);

    area.atualizaPosicao(direcao);

    caminhar = false;

    verificaMorte();
    posAntigaColision = corpo.getPosition();
}