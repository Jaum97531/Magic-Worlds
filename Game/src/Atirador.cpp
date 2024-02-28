#include "../include/Ente/Entidades/Personagens/Atirador.hpp"
#include "../include/Ente/Entidades/Projetil.hpp"

Classes::Atirador::Atirador(){
    listaEntidades = nullptr;

}


Classes::Atirador::~Atirador(){
}

void Classes::Atirador::criarProjetil(bool direcao, sf::RectangleShape corpo){
    if(listaEntidades == nullptr) return;
    
    Entidades::Projetil* tiro = new Entidades::Projetil(this, elementoProjeteis, direcao);
    
    sf::Vector2f posicao = corpo.getPosition();

    if(direcao){ tiro->setPosition(sf::Vector2f(posicao.x + 75, posicao.y + 35)); }
    else{ tiro->setPosition(sf::Vector2f(posicao.x - 5 - tiro->getSize().x , posicao.y + 35)); }

    listaEntidades->push_back(tiro);
}


void Classes::Atirador::atirar(bool direcao, sf::RectangleShape corpo){
    criarProjetil(direcao, corpo);
}