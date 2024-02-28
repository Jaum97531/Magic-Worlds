#include "../include/Ente/Entidades/Personagens/Inimigos/Fantasma.hpp"
#include "../include/Gerenciadores/Algoritimos.hpp"

Entidades::Personagens::Fantasma::Fantasma(){
    animaAndando.criaFrames("FANTASMA ANDANDO", 26, false);
    corpo.setSize(sf::Vector2f(70, 80));
    animaAndando.anima(&corpo, true);
    nvlMaldade = 100;
    relogioInivisibilidade.restart();
    tempoMax = 4;
    invisivel = false;
    vida = 100;
    tipos[Type::Fantasma] = true;
}

Entidades::Personagens::Fantasma::~Fantasma(){

}

void Entidades::Personagens::Fantasma::move(){  
    std::uniform_int_distribution<> distribuicao(0, 9);
    int rand = distribuicao(Algoritimos::getGenerator());

    //VELOCIDADE NORMAL
    velocidade = sf::Vector2f(8, 0);

    if(rand < 3){ velocidade.x *= 2; }
    else if(rand < 8){ velocidade.x /= 2; }

    //TRATAR MOVIMENTACAO EM X
    if(direcao){ movimento.x += velocidade.x; } 
    else{ movimento.x -= velocidade.x; }

}

void Entidades::Personagens::Fantasma::invisibilidade(){ 
    float previusInvisivel = relogioInivisibilidade.getElapsedTime().asSeconds();
    
    if(previusInvisivel > tempoMax){ 
        invisivel = !invisivel;
        relogioInivisibilidade.restart();
        
        std::uniform_int_distribution<> distribuicao(1, 10);
        tempoMax = distribuicao(Algoritimos::getGenerator());
    }

    if(invisivel){ estadoFisico = INTANGIVEL; }
    else { estadoFisico = NORMAL; }

}

void Entidades::Personagens::Fantasma::execute(){ 
    movimento = sf::Vector2f(0, 0);
    invisibilidade(); 

    aplicarEstadoFisico();

    determinaDirecao();

    move();

    corpo.move(sf::Vector2f(movimento.x, gravidade + movimento.y));
    
    bool animou = animaAndando.anima(&corpo, direcao, false);

    area.atualizaPosicao(direcao);

    caminhar = false;

    verificaMorte();
    posAntigaColision = corpo.getPosition();
}