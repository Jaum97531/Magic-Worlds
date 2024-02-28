#include "../include/Ente/Estados/Fases/Fase1.hpp"
#include "../include/Ente/Entidades/Objetos/Porta.hpp"
#include <iostream>
states::Fases::Fase1::Fase1() {
    limiteDaFase = sf::FloatRect(-20, -20, 3834, 1080);
    valorTileMap = 32;
    determinarPosicaoInimigos();
    criarFase();
}


states::Fases::Fase1::Fase1(std::unordered_map<int, Entidade*> map) : Fase(map){
    limiteDaFase = sf::FloatRect(-20, -20, 3834, 1080);
    valorTileMap = 32;
    determinarPosicaoInimigos(); 
    carregarFase();
}

states::Fases::Fase1::~Fase1(){
    pararDeObservar(pEventos);
    textos.clear();
    titulos.clear();
    listaEntidades.clear();
    jogador = nullptr;
    gerenAnimacao = nullptr;
}

void states::Fases::Fase1::determinarPosicaoInimigos(){
    posInimigos[sf::Vector2f(3041, 710)] = -1; 
    posInimigos[sf::Vector2f(315, 950)] = -1; 
    posInimigos[sf::Vector2f(264, 290)] = -1;
    posInimigos[sf::Vector2f(2237, 470)] = -1;
    posInimigos[sf::Vector2f(1247, 650)] = -1;
    posInimigos[sf::Vector2f(2963, 710)] = -1;
    posInimigos[sf::Vector2f(3517, 230)] = -1;
    posInimigos[sf::Vector2f(3490, 230)] = -1;
}

void states::Fases::Fase1::criaObstaculos(){
    criarLava(sf::Vector2f(567, 100), sf::Vector2f(1752, pGrafico->get_JANELAY()-100));
    criarLava(sf::Vector2f(679, 45), sf::Vector2f(945, pGrafico->get_JANELAY()/2 + 260));
    Objetos::Porta* porta = new Objetos::Porta(this);
    porta->setPosition(sf::Vector2f(3700, pGrafico->get_JANELAY()/2 + 200));
    listaEntidades.push_back(porta);
}

void states::Fases::Fase1::criarFase() {

    gerenAnimacao->criarAnimacaoLava();
    jogador->setPosition(sf::Vector2f (70, pGrafico->get_JANELAY()/2 + 100));
    if(!animacao.TemAnimacao()) animacao.criaFrames("VULCAO", 8, false);
    criarMapa("FASE FOGO PLATAFORMAS", "FASE FOGO");
    criaObstaculos();
    criaInimigos();
}

void states::Fases::Fase1::carregarFase(){
    gerenAnimacao->criarAnimacaoLava();
    if(!animacao.TemAnimacao()) animacao.criaFrames("VULCAO", 8, false);
    setInimigos();
    criarMapa("FASE FOGO PLATAFORMAS", "FASE FOGO");
    criaObstaculos();
}