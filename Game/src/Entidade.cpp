#include "../include/Ente/Entidades/Entidade.hpp"

int Entidades::Entidade::proximoId = 0;
Entidades::Entidade::Entidade() : ID(NovoId()){
    corpo.setSize(sf::Vector2f(BLOCO, BLOCO));
    estatico = true;
    ativo = true;
    gravidade = 0;
    Tipocolision = Type::Entidade;

    tipos[Type::Entidade] = true;
    tipos[Type::Personagem] = false;
    tipos[Type::Plataforma] = false;
    tipos[Type::Zumbi] = false;
    tipos[Type::Inimigo] = false;
    tipos[Type::Esqueleto] = false;
    tipos[Type::Zumbi] = false;
    tipos[Type::Objeto] = false;
    tipos[Type::Plataforma] = false;
    tipos[Type::Caixa] = false;
    tipos[Type::Porta] = false;
    tipos[Type::Projetil] = false;
    tipos[Type::Lava] = false;
    tipos[Type::Area] = false;
}

Entidades::Entidade::~Entidade(){

}

void Entidades::Entidade::acelerarGravidade(){
    if(!estatico && gravidade <= VELOCIDADE_TERMINAL){ 
        gravidade += GRAVIDADE;
    }
}