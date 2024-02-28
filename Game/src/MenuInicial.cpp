#include "../include/Ente/Estados/Menus/MenuInicial.hpp"

states::MenuInicial::MenuInicial(){
    animacao.criaFrames("MENU INICIAL", 5, false);
    iniciarTextos();
    observar(pEventos);
}

states::MenuInicial::~MenuInicial(){

}

void states::MenuInicial::iniciarTextos(){
    int JANELAX = pGrafico->get_JANELAX();
    int JANELAY = pGrafico->get_JANELAY();

    sf::Text bgPlay(criarTexto("JOGAR", 110, sf::Vector2f(JANELAX/2 - 150, JANELAY/2 - 50), sf::Color::Black));
    titulos.push_back(bgPlay);

    sf::Text play(criarTexto("JOGAR", 110, sf::Vector2f(JANELAX/2 - 140, JANELAY/2 - 50), AZULVERDE));
    textos.push_back(play);

    sf::Text quit(criarTexto("SAIR", 50, sf::Vector2f(JANELAX/2 - 50, JANELAY - 70), AZULVERDE));
    textos.push_back(quit);

    sf::Text bgQuit(criarTexto("SAIR", 50, sf::Vector2f(JANELAX/2 - 55, JANELAY - 70), sf::Color::Black));
    titulos.push_back(bgQuit);

    sf::Text tituloSombra(criarTexto("Magical world", 150, sf::Vector2f(JANELAX/2 - 515, 30), COR_AGUA));
    titulos.push_back(tituloSombra);

    sf::Text titulo(criarTexto("Magical world", 150, sf::Vector2f(JANELAX/2 - 510, 30), AZULVERDE));
    titulos.push_back(titulo);
}

void states::MenuInicial::tratarSelecao(sf::String selecao){
    if(selecao == "JOGAR") { pEstados->trocarEstado(LOBBY); }
    else if (selecao == "SAIR") { pGrafico->fecharJanela(); }
}