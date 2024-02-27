#include "../include/Ente/Estados/Menus/Pausa.hpp"

states::Pausa::Pausa() : faseAtual(FASE1) {
    iniciarTextos();
}

states::Pausa::~Pausa(){

}

void states::Pausa::setAnimacao(int fase){
    faseAtual = fase;
    switch(fase){
        case FASE1 :
            animacao.criaFrames("VULCAO", 8, false);
            break;
    }
}

void states::Pausa::iniciarTextos(){
    sf::Text continuar(criarTexto(("CONTINUAR"), 70, sf::Vector2f(pGrafico->get_JANELAX()/2 - 200, pGrafico->get_JANELAY()/2 - 30), AZULVERDE));
    textos.push_back(continuar);

    sf::Text sair(criarTexto(("LOBBY"), 60, sf::Vector2f(pGrafico->get_JANELAX()/2 - 100, pGrafico->get_JANELAY() - 120), AZULVERDE));
    textos.push_back(sair);

    sf::Text pausa(criarTexto("PAUSA", 110, sf::Vector2f(pGrafico->get_JANELAX()/2 - 180, 60), AZULVERDE));
    titulos.push_back(pausa);
}

void states::Pausa::tratarSelecao(sf::String selecao){
    if(selecao == "LOBBY") { pEstados->trocarEstado(LOBBY); }
    else if (selecao == "CONTINUAR") { pEstados->trocarEstado(faseAtual); }
}