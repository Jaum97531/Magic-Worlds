#include "../include/Ente/Entidades/Entidade.hpp"

int Entidades::Entidade::proximoId = 0;
Entidades::Entidade::Entidade() : ID(NovoId()){
    corpo.setSize(sf::Vector2f(BLOCO, BLOCO));
    estatico = true;
    ativo = true;
    gravidade = 0;
}

Entidades::Entidade::~Entidade(){

}

const bool Entidades::Entidade::getTipoSecundario(Type tipo){
    for(auto type : tiposSecundarios){
        if(type == tipo) { return true; }
    }
    return false;
}

void Entidades::Entidade::acelerarGravidade(){
    if(!estatico && gravidade <= VELOCIDADE_TERMINAL){ 
        gravidade += GRAVIDADE;
    }
}