#include "../include/Ente/Estados/Fases/Fase1.hpp"
#include "../include/Ente/Entidades/Objetos/Porta.hpp"
#include <iostream>
using namespace std;

states::Fases::Fase1::Fase1(){
    listaEntidades.clear();
    limiteDaFase = sf::Vector2f(3834, 1980);
    valorTileMap = 32;
    setJogador(Personagens::Jogador::getInstancia());
    listaEntidades.push_back(jogador);
    listaEntidades.push_back(jogador->getArea());
    determinarPosicaoInimigos();
    criarFase();
    criarUtilits();
}

states::Fases::Fase1::Fase1(std::vector<Entidade*> list){
    limiteDaFase = sf::Vector2f(3834, 1980);
    valorTileMap = 32;
    listaEntidades = list;
    setJogador(Personagens::Jogador::getInstancia());
    determinarPosicaoInimigos(); 
    carregarFase();
    criarUtilits();
}

states::Fases::Fase1::~Fase1(){
    pararDeObservar(pEventos);
    textos.clear();
    titulos.clear();
    for(auto* ent : listaEntidades){ if(ent != jogador && ent != jogador->getArea()) delete ent; }
    listaEntidades.clear();
    jogador = nullptr;
    gerenAnimacao = nullptr;
}

void states::Fases::Fase1::determinarPosicaoInimigos(){
    posInimigos[new sf::Vector2f(3041, 710)] = nullptr;
    posInimigos[new sf::Vector2f(315, 950)] = nullptr;
    posInimigos[new sf::Vector2f(264, 290)] = nullptr;
    posInimigos[new sf::Vector2f(2237, 470)] = nullptr;
    posInimigos[new sf::Vector2f(1247, 650)] = nullptr;
    posInimigos[new sf::Vector2f(2963, 710)] = nullptr;
    posInimigos[new sf::Vector2f(3517, 230)] = nullptr;
    posInimigos[new sf::Vector2f(3490, 230)] = nullptr;
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
    jogador->revive();
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

void states::Fases::Fase1::setInimigos(){
    for(auto* it : listaEntidades){
        if(it != nullptr){
            if(it->getTipoSecundario(Type::Inimigo)){
                for(auto it2 : posInimigos){
                    if(it2.second == nullptr){
                        posInimigos[it2.first] =  dynamic_cast<Personagens::Inimigo*>(it);
                        break;
                    }
                }
            }
        }
    }
}