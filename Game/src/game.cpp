#include "../include/game.hpp"
#include <chrono>
#include <iostream>
#include <windows.h>

Game::Game(){
    pImagens = GR::GerenciadorImagens::getInstancia();
    pGrafico = GR::GerenciadorGrafico::getInstancia();
    pEventos = GR::GerenciadorEventos::getInstancia();
    pEstados = GR::GerenciadorEstados::getInstancia();

    pEstados->criarEstados();
    
    execute();
}

Game::~Game(){

}

void Game::execute(){
    while(pGrafico->janelaAberta()){
        pGrafico->limpar();
        pEventos->execute();
        pEstados->execute();
        pGrafico->mostrar();
    }
}