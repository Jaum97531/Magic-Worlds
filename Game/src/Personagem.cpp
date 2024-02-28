#include "../include/Ente/Entidades/Personagens/Personagem.hpp"
#include "../include/Ente/Entidades/Projetil.hpp"
#include "../include/Ente/Entidades/AreaDeEfeito.hpp"
#include "../include/Ente/Entidades/Objetos/Objeto.hpp"


Entidades::Personagens::Personagem::Personagem(){
    direcao = true;
    estatico = false;
    estadoFisico = NORMAL;
    tipos[Type::Personagem] = true;
    Tipocolision = Type::Personagem;
}

Entidades::Personagens::Personagem::~Personagem(){

}

void Entidades::Personagens::Personagem::setFalseResistencias(){
    resistencias[QUEIMANDO] = false;
    resistencias[CONGELADO] = false;
    resistencias[INTANGIVEL] = false;
    resistencias[TONTO] = false;
    resistencias[ENVENENADO] = false;
}

void Entidades::Personagens::Personagem::encerrarEstadoFisico(){
    float tempo = tempoEstado.getElapsedTime().asSeconds();
    switch (estadoFisico){
        case QUEIMANDO : 
            if(tempo >= 2){
                tempoEstado.restart();
                estadoFisico = NORMAL;
            }
            break;
        case CONGELADO:
            if(tempo >= 5){
                tempoEstado.restart();
                estadoFisico = NORMAL;
            }
            break;
        case INTANGIVEL:
            break;
    }
}

void Entidades::Personagens::Personagem::setEstadoFisico(const int estadoF) { 
    if(!resistencias[estadoF]) {
        estadoFisico = estadoF; 
        tempoEstado.restart();
    } 
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
    encerrarEstadoFisico();

    switch (estadoFisico){
        case NORMAL:
            corpo.setFillColor(sf::Color::White);
            break;
        case QUEIMANDO :
            if(vida > 0) vida -= 1;
            corpo.setFillColor(COR_FOGO);
            break;
        case CONGELADO :
            movimento = sf::Vector2f(movimento.x/3, movimento.y/3);
            corpo.setFillColor(COR_AGUA);
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