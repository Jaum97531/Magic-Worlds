#include "../include/Ente/Estados/Menus/GameOver.hpp"

states::GameOver::GameOver() : ptsJogador(0){
    iniciarTextos();
}

states::GameOver::~GameOver(){

}

void states::GameOver::iniciarEstado(){
    observar(pEventos);
    pView->setCenter(sf::Vector2f(pGrafico->get_JANELAX()/2, pGrafico->get_JANELAY()/2));
    pGrafico->getJanela()->setView(*pView);
    textos.clear();
    titulos.clear();
    iniciarTextos();
}

void states::GameOver::tratarSelecao(sf::String selecao){
    if(selecao == "LOBBY"){
        pEstados->trocarEstado(LOBBY);
    }
}

void states::GameOver::iniciarTextos(){
    const int JANELAX = pGrafico->get_JANELAX();
    const int JANELAY = pGrafico->get_JANELAY();

    sf::Text pontos = criarTexto(std::to_string(ptsJogador), 70, sf::Vector2f(JANELAX/2 + 50, JANELAY/2), AZULVERDE);
    titulos.push_back(pontos);
    
    sf::Text pontosJogador = criarTexto("PONTOS: ", 70, sf::Vector2f(JANELAX/2 - 230, JANELAY/2), AZULVERDE);
    titulos.push_back(pontosJogador);

    sf::Text perdeu = criarTexto("VOCE MORREU", 120, sf::Vector2f(JANELAX/2 - 410, 60), AZULVERDE);
    titulos.push_back(perdeu);

    sf::Text lobby = criarTexto("LOBBY", 70, sf::Vector2f(JANELAX/2 - 140, JANELAY - 150), AZULVERDE);
    textos.push_back(lobby);
}

void states::GameOver::setAnimacao(int fase){
    switch(fase){
        case FASE1 :
            animacao.criaFrames("VULCAO", 8, false);
            break;
        case FASE2 :
            animacao.criaFrames("FASE LAVA", 8, false);
            break;
    }
}