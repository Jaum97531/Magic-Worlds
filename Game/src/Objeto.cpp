#include "../include/Ente/Entidades/Objetos/Objeto.hpp"

Entidades::Objetos::Objeto::Objeto(){

}

Entidades::Objetos::Objeto::~Objeto(){

}

bool Entidades::Objetos::Objeto::getEspecial() const{
    return especial;
}

void Entidades::Objetos::Objeto::execute(){

}

const Type Entidades::Objetos::Objeto::getType() const{
    return Type::Objeto;
}