#include "../include/Ente/Estados/Menus/MenuInicial.hpp"

states::MenuInicial::MenuInicial(){
    animacao.criaFrames("MENU INICIAL", 5, false);
    iniciarTextos();
    observar(pEventos);
}

states::MenuInicial::~MenuInicial(){

}

void states::MenuInicial::iniciarTextos(){
    sf::Text play(criarTexto("JOGAR", 110, sf::Vector2f(pGrafico->get_JANELAX()/2 - 135, pGrafico->get_JANELAY()/2 - 50), AZULVERDE));
    textos.push_back(play);

    sf::Text quit(criarTexto("SAIR", 50, sf::Vector2f(pGrafico->get_JANELAX()/2 - 50, pGrafico->get_JANELAY() - 70), AZULVERDE));
    textos.push_back(quit);

    sf::Text tituloSombra(criarTexto("The magical world", 150, sf::Vector2f(pGrafico->get_JANELAX()/2 - 660, 30), AGUA));
    titulos.push_back(tituloSombra);

    sf::Text titulo(criarTexto("The magical world", 150, sf::Vector2f(pGrafico->get_JANELAX()/2 - 650, 30), AZULVERDE));
    titulos.push_back(titulo);
}

void states::MenuInicial::tratarSelecao(sf::String selecao){
    if(selecao == "JOGAR") { pEstados->trocarEstado(LOBBY); }
    else if (selecao == "SAIR") { pGrafico->fecharJanela(); }
}