#include "../include/Ente/Estados/Fases/Fase2.hpp"
#include "../include/Ente/Entidades/Objetos/Porta.hpp"

states::Fases::Fase2::Fase2(){
    limiteDaFase = sf::FloatRect(-20, -20, 3834, 1080);
    valorTileMap = 32;
    determinarPosicaoInimigos();
    criarFase();
}

states::Fases::Fase2::Fase2(std::unordered_map<int, Entidade*> map) : Fase(map){
    limiteDaFase = sf::FloatRect(-20, -20, 3834, 1080);sf::FloatRect(0, 0, 0, 0);
    valorTileMap = 32;
    determinarPosicaoInimigos(); 
    carregarFase();
}

void states::Fases::Fase2::tratarSelecao(sf::String selecao){ 
    if(this->numeroDeFase() == FASE2) {
        if(jogador->getShape()->getPosition().x > limiteDaFase.width/2)
            pEstados->trocarEstado(MENSAGEM);
        else 
            pEstados->trocarEstado(FASE1);
    }

}

states::Fases::Fase2::~Fase2(){
    pararDeObservar(pEventos);
    textos.clear();
    titulos.clear();
    listaEntidades.clear();
    jogador = nullptr;
    gerenAnimacao = nullptr;
}

void states::Fases::Fase2::criarFase(){
    gerenAnimacao->criarAnimacaoLava();
    jogador->setPosition(sf::Vector2f (50, 100));
    if(!animacao.TemAnimacao()) animacao.criaFrames("CAVERNA", 12, false);
    criarMapa("FASE CAVERNA PLATAFORMAS", "FASE CAVERNA");
    criaObstaculos();
    criaInimigos();
}

void states::Fases::Fase2::carregarFase(){
    gerenAnimacao->criarAnimacaoLava();
    if(!animacao.TemAnimacao()) animacao.criaFrames("CAVERNA", 12, false);
    setInimigos();
    criarMapa("FASE CAVERNA PLATAFORMAS", "FASE CAVERNA");
    criaObstaculos();
}

void states::Fases::Fase2::criaObstaculos(){
    Entidades::Objetos::Porta* porta1 = new Entidades::Objetos::Porta(this);
    porta1->setPosition(sf::Vector2f(108, 200));
    listaEntidades.push_back(porta1);

    Entidades::Objetos::Porta* porta2 = new Entidades::Objetos::Porta(this);
    porta2->setPosition(sf::Vector2f(3661,200));
    listaEntidades.push_back(porta2);
}

void states::Fases::Fase2::determinarPosicaoInimigos(){

}