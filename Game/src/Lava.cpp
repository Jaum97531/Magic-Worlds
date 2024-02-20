#include "../include/Ente/Entidades/Objetos/Lava.hpp"
#include "../include/Ente/Entidades/Personagens/Personagem.hpp"


Entidades::Objetos::Lava::Lava(){
    
}

Entidades::Objetos::Lava::~Lava(){

}

void Entidades::Objetos::Lava::desenhar(){
    pGrafico->draw(shapeAnimacao);
}

void Entidades::Objetos::Lava::execute(){
    
}

void Entidades::Objetos::Lava::tratarColisao(Personagens::Personagem* personagem, std::string direcao){
    queimarPersonagem(personagem);
}


void Entidades::Objetos::Lava::queimarPersonagem(Personagens::Personagem* personagem){
    personagem->setEstadoFisico(QUEIMANDO);
}

void Entidades::Objetos::Lava::setPosition(sf::Vector2f pos){
    corpo.setPosition(pos);
    shapeAnimacao.setPosition(pos.x, pos.y - corpo.getSize().y-30);
}

void Entidades::Objetos::Lava::setSize(sf::Vector2f size){
    corpo.setSize(size);
    shapeAnimacao.setSize(sf::Vector2f(size.x, size.y*2 + 30));
}
