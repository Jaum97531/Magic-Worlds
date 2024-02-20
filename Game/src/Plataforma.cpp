#include "../include/Ente/Entidades/Objetos/Plataforma.hpp"

Entidades::Objetos::Plataforma::Plataforma(int type){
    tipo = type;
    corpo.setSize(sf::Vector2f(42, 1000));
    atribuirTexture();
    addTipoSecundario(Type::Plataforma);
}

Entidades::Objetos::Plataforma::Plataforma(int type, sf::Vector2f size){
    tipo = type;
    corpo.setSize(size);
    atribuirTexture();
    addTipoSecundario(Type::Plataforma);
}


Entidades::Objetos::Plataforma::~Plataforma(){

}

Entidades::Objetos::Plataforma::Plataforma() : tipo(0){

}

void Entidades::Objetos::Plataforma::desenhar() {
    if(tipo)pGrafico->draw(corpo); 
}

void Entidades::Objetos::Plataforma::setTipe(int type) { 
    tipo = type; atribuirTexture(); 
}

void Entidades::Objetos::Plataforma::atribuirTexture(){
    sf::Texture* textura = nullptr;
    switch (tipo){
        case TIPO1 :
            textura = pGrafico->getPimagens()->getTextura("PLATAFORMA 1");
            break;
        case TIPO2 :
            textura = pGrafico->getPimagens()->getTextura("PLATAFORMA 2");
            break;
    }
    textura->setRepeated(true);
    corpo.setTexture(textura);
    corpo.setTextureRect(sf::IntRect(0, 0, corpo.getSize().x, textura->getSize().y));
}

