#include "../include/Ente/Entidades/AreaDeEfeito.hpp"
#include "../include/Ente/Entidades/Personagens/Inimigos/Esqueleto.hpp"
#include <iostream>

Entidades::AreaDeEfeito::AreaDeEfeito(Entidade* dona, bool* ativado, int dano, bool colide) : entidadeDona(dona), ativado(ativado),
colideObjeto(colide), dano(dano){
    impulso = sf::Vector2f(0, 0); 
    efeito = NORMAL;
}

void Entidades::AreaDeEfeito::tratarColisao(Objetos::Objeto* obj, std::string direcao){
    if(entidadeDona->getTipoSecundario(Type::Inimigo)){
        Personagens::Inimigo* ini = dynamic_cast<Personagens::Inimigo*>(entidadeDona);
        ini->tratarColisaoDaArea(direcao, Type::Objeto);
    }
}

void Entidades::AreaDeEfeito::tratarColisao(Personagens::Personagem* perso, std::string dir){
    if(dano > 0){
        if(entidadeDona->getShape()->getPosition().x < perso->getShape()->getPosition().x){ perso->deslocar(impulso); }
        else { perso->deslocar(sf::Vector2f(-impulso.x, impulso.y)); }
        perso->setEstadoFisico(efeito);
    }
    else if(perso->getTipoSecundario(Type::Jogador) && entidadeDona->getTipoSecundario(Type::Inimigo)){
        Personagens::Inimigo* ini = dynamic_cast<Personagens::Inimigo*>(entidadeDona);
        ini->tratarColisaoDaArea(dir, Type::Jogador);
    }
}

void Entidades::AreaDeEfeito::atualizaPosicao(bool direcao){ 
    sf::Vector2f sizeEnt = entidadeDona->getShape()->getSize();
    sf::Vector2f posEnt = entidadeDona->getShape()->getPosition();
    sf::Vector2f sizeArea = corpo.getSize();
    sf::Vector2f posArea = corpo.getPosition();

    if(direcao)  corpo.setPosition(sf::Vector2f(posEnt.x + sizeEnt.x + 20, posEnt.y - sizeArea.y + sizeEnt.y + 5)); 
    else corpo.setPosition(sf::Vector2f(posEnt.x - sizeArea.x - 20, posEnt.y - sizeArea.y + sizeEnt.y + 5)); 
}