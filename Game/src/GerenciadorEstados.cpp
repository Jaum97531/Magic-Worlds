#include "../include/Ente/Estados/Menus/MenuInicial.hpp"
#include "../include/Ente/Estados/Menus/Lobby.hpp"
#include "../include/Ente/Estados/Fases/Fase1.hpp"
#include "../include/Ente/Estados/Menus/Pausa.hpp"
#include "../include/Ente/Estados/Menus/GameOver.hpp"
#include "../include/Ente/Estados/Menus/Rank.hpp"
#include <iostream>
#include "../include/Ente/Entidades/EntidadeSaver.hpp"

GR::GerenciadorEstados* GR::GerenciadorEstados::instancia = nullptr;
GR::GerenciadorEstados::GerenciadorEstados() {
    estadoAtual = 0;
}

GR::GerenciadorEstados::~GerenciadorEstados(){
    for(auto it : mapEstados){
        delete it.second;
    }
    mapEstados.clear();
}

GR::GerenciadorEstados* GR::GerenciadorEstados::getInstancia(){
    if(instancia == nullptr){ instancia = new GR::GerenciadorEstados(); }
    return instancia;
}

void GR::GerenciadorEstados::criarEstados(){

    states::MenuInicial* menuInicial = new states::MenuInicial();
    mapEstados[INICIAL] = menuInicial;

    states::Lobby* lobby = new states::Lobby();
    mapEstados[LOBBY] = lobby;

    states::Pausa* pausa = new states::Pausa();
    mapEstados[PAUSA] = pausa;

    mapEstados[FASE1] = nullptr;

    states::GameOver* gameOver = new states::GameOver();
    mapEstados[GAMEOVER] = gameOver;

    states::Rank* rank = new states::Rank();
    mapEstados[RANK] = rank;

}

bool GR::GerenciadorEstados::tratarTrocaEspecificas(int& estado){
    if(estado == GAMEOVER){
        states::GameOver* perdeu = dynamic_cast<states::GameOver*>(mapEstados[GAMEOVER]);
        perdeu->setAnimacao(estadoAtual);
        perdeu->setPtsJogador(Personagens::Jogador::getInstancia()->getPontos());
        return true;
    }

    if (estadoAtual == LOBBY && estado == FASE1) {
        delete mapEstados[FASE1];
        mapEstados[FASE1] == nullptr;
        states::Fases::Fase1* fase1 = new states::Fases::Fase1();
        mapEstados[FASE1] = fase1;
        return true;
    }

    if(estado == FASE_1){
        delete mapEstados[FASE1];
        mapEstados[FASE1] == nullptr;
        EntidadeSaver load;
        states::Fases::Fase1* fase1 = new states::Fases::Fase1(load.loadEntidades());
        mapEstados[FASE1] = fase1;
        estado = FASE1;
        return true;
    }


    if(estado == PAUSA){
        states::Pausa* pausa = dynamic_cast<states::Pausa*>(mapEstados[PAUSA]);
        pausa->setAnimacao(estadoAtual);
        return true;
    }

    return true;
}

void GR::GerenciadorEstados::trocarEstado(int estado){
    if(tratarTrocaEspecificas(estado)){
        mapEstados[estadoAtual]->encerrarEstado();
        estadoAtual = estado;
        mapEstados[estadoAtual]->iniciarEstado();
    }
}

void GR::GerenciadorEstados::execute(){
    mapEstados[estadoAtual]->execute();
}