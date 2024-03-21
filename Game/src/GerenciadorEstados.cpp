#include "../include/Ente/Estados/Menus/MenuInicial.hpp"
#include "../include/Ente/Estados/Menus/Lobby.hpp"
#include "../include/Ente/Estados/Fases/Fase1.hpp"
#include "../include/Ente/Estados/Fases/Fase2.hpp"
#include "../include/Ente/Estados/Menus/Pausa.hpp"
#include "../include/Ente/Estados/Menus/GameOver.hpp"
#include "../include/Ente/Estados/Menus/Rank.hpp"
#include "../include/Ente/Estados/Menus/Continua.hpp"
#include <iostream>
#include "../include/Ente/FaseSaver.hpp"

GR::GerenciadorEstados* GR::GerenciadorEstados::instancia = nullptr;
GR::GerenciadorEstados::GerenciadorEstados() {
    estadoAtual = INICIAL;
    observar(GerenciadorEventos::getInstancia());
}

GR::GerenciadorEstados::~GerenciadorEstados(){
    for(auto it : mapEstados){
        delete it.second;
    }
    mapEstados.clear();
}

GR::GerenciadorEstados* GR::GerenciadorEstados::getInstancia(){
    if(instancia == nullptr)
        instancia = new GR::GerenciadorEstados();

    return instancia;
}

void GR::GerenciadorEstados::notifica(int tipo){
    if(tipo == RESIZED){
        for(auto it : mapEstados){
            if(it.second != nullptr){
                it.second->resized();
            }
        }
    }
}

void GR::GerenciadorEstados::deleteEstado(int estado){
    delete mapEstados[estado];
    mapEstados[estado] = nullptr;
}

void GR::GerenciadorEstados::criarEstados(){
    states::MenuInicial* menuInicial = new states::MenuInicial();
    mapEstados[INICIAL] = menuInicial;

    states::Lobby* lobby = new states::Lobby();
    mapEstados[LOBBY] = lobby;

    states::Pausa* pausa = new states::Pausa();
    mapEstados[PAUSA] = pausa;

    mapEstados[FASE1] = nullptr;
    mapEstados[FASE2] = nullptr;

    states::GameOver* gameOver = new states::GameOver();
    mapEstados[GAMEOVER] = gameOver;

    states::Rank* rank = new states::Rank();
    mapEstados[RANK] = rank;

    states::Continua* continua = new states::Continua();
    mapEstados[MENSAGEM] = continua;

}

bool GR::GerenciadorEstados::tratarTrocaEspecificas(int& estado){
    
    if(estado == GAMEOVER){
        states::GameOver* perdeu = dynamic_cast<states::GameOver*>(mapEstados[GAMEOVER]);
        perdeu->setAnimacao(estadoAtual);
        return true;
    }

    if (estado == NEWGAME) {
        deleteEstado(FASE2);
        states::Fases::Fase2* fase1 = new states::Fases::Fase2();
        mapEstados[FASE2] = fase1;
        estado = FASE2;
        return true;
    }
    
    if(estado == FASE2){
        deleteEstado(FASE2);
        states::Fases::Fase2* fase2 = new states::Fases::Fase2();
        mapEstados[FASE2] = fase2;
        estado = FASE2;
        return true;
    }

    if(estado == CONTINUE){
        FaseSaver load;
        states::Fases::Fase* fase = load.loadEntidades();
        mapEstados[fase->numeroDeFase()] = fase;
        estado = fase->numeroDeFase();
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