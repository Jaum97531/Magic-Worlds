#include "../include/Ente/Entidades/Personagens/Inimigos/Polvo.hpp"

Entidades::Personagens::Polvo::Polvo(){
    vida = 500;
    estagiosDash = {5, 4.5, 4, 3.5, 3, 2};
    dash = false;
    clockDash.restart();

}

Entidades::Personagens::Polvo::~Polvo(){
    
}

void Entidades::Personagens::Polvo::move(){

}

void Entidades::Personagens::Polvo::execute(){

}

void Entidades::Personagens::Polvo::determinaDirecao(){
   
}

void Entidades::Personagens::Polvo::tratarColisaoDaArea(std::string direcao, Type classe){
    if(classe == Type::Jogador){
        dash = true;
        clockDash.restart();
    }
}

void Entidades::Personagens::Polvo::tratarColisao(Jogador* jogador, std::string direcao){
    jogador->diminuiVida(3);
    this->direcao = !this->direcao;
}
