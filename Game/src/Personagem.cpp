#include "../include/Ente/Entidades/Personagens/Personagem.hpp"
#include "../include/Ente/Entidades/Projetil.hpp"
#include "../include/Ente/Entidades/AreaDeEfeito.hpp"
#include "../include/Ente/Entidades/Objetos/Objeto.hpp"


Entidades::Personagens::Personagem::Personagem(){
    direcao = true;
    estatico = false;
    estadoFisico = NORMAL;
    
}

Entidades::Personagens::Personagem::~Personagem(){

}


void Entidades::Personagens::Personagem::tratarColisao(Projetil* projetil, std::string direcao){
    vida -= projetil->getDano();
}

void Entidades::Personagens::Personagem::tratarColisao(AreaDeEfeito* area, std::string direcao){
    vida -= area->getDano();
}

void Entidades::Personagens::Personagem::tratarColisao(Objetos::Objeto* obj, std::string direcao){
    if(direcao == "BAIXO"){
        gravidade = 0;
    }
}

bool Entidades::Personagens::Personagem::verificaMorte(){
    if(vida <= 0){ ativo = false; return true; }
    return false;
}

void Entidades::Personagens::Personagem::aplicarEstadoFisico(){
    if(tempoEstado.getElapsedTime().asSeconds() > 4 && estadoFisico != INTANGIVEL){ estadoFisico = NORMAL; }
    
    switch (estadoFisico){
        case NORMAL:
            corpo.setFillColor(sf::Color::White);
            break;
        case QUEIMANDO :
            if(vida > 0) vida -= 1;
            corpo.setFillColor(FOGO);
            break;
        case CONGELADO :
            corpo.setFillColor(AGUA);
            break;
        case INTANGIVEL :
            sf::Color cor = sf::Color::White;
            cor.a = 50;
            corpo.setFillColor(cor);
            break;
    }
}

void Entidades::Personagens::Personagem::execute(){
    aplicarEstadoFisico();
    move();
    desenhar();
    verificaMorte();
    posAntigaColision = corpo.getPosition();
}