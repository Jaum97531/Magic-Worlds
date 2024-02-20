#include "../include/Ente/Entidades/Objetos/Caixa.hpp"
#include "../include/Ente/Entidades/Personagens/Jogador.hpp"

Entidades::Objetos::Caixa::Caixa(){
    corpo.setSize(sf::Vector2f(70, 70));
    corpo.setTexture(pGrafico->getPimagens()->getTextura("CAIXA"));
    addTipoSecundario(Type::Caixa);
    estatico = false;
}

Entidades::Objetos::Caixa::~Caixa(){

}

void Entidades::Objetos::Caixa::tratarColisao(Objeto* obj, std::string direcao){
    if(direcao == "BAIXO"){
        gravidade = 0;
    }
}

void Entidades::Objetos::Caixa::execute(){
    corpo.move(sf::Vector2f(0, gravidade));
}