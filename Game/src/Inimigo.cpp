#include "../include/Ente/Entidades/Personagens/Inimigos/Inimigo.hpp"

Entidades::Personagens::Jogador* Entidades::Personagens::Inimigo::jogador = NULL;
Entidades::Personagens::Inimigo::Inimigo() : estado(DEBOA), vendo(true), area(this, &vendo, 0, true), caminhar(true){
    tipos[Type::Inimigo] = true;
    cronometroDePerseguicao.restart();
    area.setSize(sf::Vector2f(20, 100));
    area.setColor(sf::Color::Transparent);
    area.setColideObjeto(true);
}

Entidades::Personagens::Inimigo::~Inimigo(){

}

void Entidades::Personagens::Inimigo::tratarColisaoDaArea(std::string dir, Type classe){
    if(classe == Type::Objeto){
        if(dir == "BAIXO") caminhar = true; 
        //else if( dir != "CIMA") direcao = !direcao;
    }
    else if (classe == Type::Jogador){
        estado = PERSEGUINDO;
        cronometroDePerseguicao.restart();
    }
}


void Entidades::Personagens::Inimigo::determinaDirecao(){
    if(estado == PERSEGUINDO){
        float difPos = jogador->getShape()->getPosition().x - corpo.getPosition().x;
        if(difPos < 0)  direcao = false; 
        else direcao = true;

        if(cronometroDePerseguicao.getElapsedTime().asSeconds() >= 5) { estado = DEBOA; }
    }

    if(!caminhar) { direcao = !direcao; caminhar = true; estado = DEBOA; }

}

void Entidades::Personagens::Inimigo::tratarColisao(Jogador* jogador, std::string direcao){
    if(corpo.getPosition().x < jogador->getPosition().x)
        jogador->deslocar(sf::Vector2f(20, -20));
    else
        jogador->deslocar(sf::Vector2f(-20, -20));

    this->direcao = !this->direcao;
    jogador->diminuiVida();
    estado = DEBOA;
    area.atualizaPosicao(this->direcao);
}

void Entidades::Personagens::Inimigo::execute(){
    movimento = sf::Vector2f(0, 0);

    determinaDirecao();

    move();

    aplicarEstadoFisico();

    corpo.move(sf::Vector2f(movimento.x, gravidade + movimento.y));
    
    bool animou = animaAndando.anima(&corpo, direcao, false);

    area.atualizaPosicao(direcao);

    caminhar = false;

    verificaMorte();
    posAntigaColision = corpo.getPosition();
}

bool Entidades::Personagens::Inimigo::verificaMorte(){
    if(vida <= 0){ 
        jogador->aumentarPontos(nvlMaldade);
        ativo = false; 
        return true; 
    }
    return false;
}

void Entidades::Personagens::Inimigo::move(){
    if(caminhar){
        if(direcao) movimento.x += velocidade.x;
        else movimento.x -= velocidade.x;
    }
}