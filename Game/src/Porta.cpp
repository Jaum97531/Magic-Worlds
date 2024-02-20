#include "../include/Ente/Entidades/Objetos/Porta.hpp"

Entidades::Objetos::Porta::Porta(states::Fases::Fase* fase){
    pFase = fase;
    corpo.setSize(sf::Vector2f(70, 104));
    addTipoSecundario(Type::Porta);
}

Entidades::Objetos::Porta::~Porta(){

}

void Entidades::Objetos::Porta::execute(){
    corpo.setTexture(pGrafico->getPimagens()->getTextura("PORTA FECHADA"));
}

void Entidades::Objetos::Porta::tratarColisao(Personagens::Personagem* perso, std::string direcao){
    if(perso->getTipoSecundario(Type::Jogador)){
        corpo.setTexture(pGrafico->getPimagens()->getTextura("PORTA ABERTA"));
        if(pEventos->verificaClickTecla(sf::Keyboard::Enter)){
            pFase->tratarSelecao("PROX FASE");
        }       
    }
}