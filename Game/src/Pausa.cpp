#include "../include/Ente/Estados/Menus/Pausa.hpp"
#include "../include/Ente/Estados/Fases/Fase.hpp"

states::Pausa::Pausa() : faseAtual(FASE1) {
    salvo = false;
    criarUtilits();
    iniciarTextos();
}

states::Pausa::~Pausa(){

}
void states::Pausa::criarUtilits(){
    sf::RectangleShape placa = criarShapeTextura("PLACA", sf::Vector2f(1100, 750), sf::Vector2f(420, 150), false);
    utilits["PLACA"] = std::pair<sf::Vector2f, sf::RectangleShape>(placa.getPosition(), placa);
}

void states::Pausa::setAnimacao(int fase){
    faseAtual = fase;
    switch(fase){
        case FASE1 :
            animacao.criaFrames("VULCAO", 8, false);
            break;
        case FASE2 :
            animacao.criaFrames("CAVERNA", 12, false);
            break;
    }
}

void states::Pausa::iniciarEstado(){
    observar(pEventos);
    pView->setCenter(sf::Vector2f(pGrafico->get_JANELAX()/2, pGrafico->get_JANELAY()/2));
    pGrafico->getJanela()->setView(*pView);
    textos.clear();
    titulos.clear();
    salvo = false;
    iniciarTextos();
}

void states::Pausa::iniciarTextos(){
    int JANELAX = pGrafico->get_JANELAX();
    int JANELAY = pGrafico->get_JANELAY();

    sf::Text bgContinuar(criarTexto(("CONTINUAR"), 70, sf::Vector2f(JANELAX/2 - 9*19 - 5, JANELAY/2 - 170), sf::Color::Black));
    titulos.push_back(bgContinuar);

    sf::Text continuar(criarTexto(("CONTINUAR"), 70, sf::Vector2f(JANELAX/2 - 9*19, JANELAY/2 - 170), AZULVERDE));
    textos.push_back(continuar);

    sf::Text bgSair(criarTexto(("LOBBY"), 60, sf::Vector2f(JANELAX/2 - 5*14 - 10, JANELAY - 310), sf::Color::Black));
    titulos.push_back(bgSair);

    sf::Text sair(criarTexto(("LOBBY"), 60, sf::Vector2f(JANELAX/2 - 5*14  - 5, JANELAY - 310), AZULVERDE));
    textos.push_back(sair);

    if(!salvo){
        sf::Text bgSalvar(criarTexto("SALVAR", 60, sf::Vector2f(JANELAX/2 - 6*15 - 5, JANELAY/2 + 30), sf::Color::Black));
        titulos.push_back(bgSalvar);

        sf::Text salvar(criarTexto("SALVAR", 60, sf::Vector2f(JANELAX/2 - 6*15, JANELAY/2 + 30), AZULVERDE));
        textos.push_back(salvar);
    }
    else {
        sf::Text salvar(criarTexto("SALVO", 60, sf::Vector2f(JANELAX/2 - 6*15 + 5, JANELAY/2 + 30), AZULVERDE));
        titulos.push_back(salvar);

        sf::Text bgSalvar(criarTexto("SALVO", 60, sf::Vector2f(JANELAX/2 - 6*15, JANELAY/2 + 30), sf::Color::Black));
        titulos.push_back(bgSalvar);
    }


    sf::Text pausa(criarTexto("PAUSA", 110, sf::Vector2f(JANELAX/2 - 5*26 - 5, 160), AZULVERDE));
    titulos.push_back(pausa);

    sf::Text bgPausa(criarTexto("PAUSA", 110, sf::Vector2f(JANELAX/2 - 5*26 - 10, 160), sf::Color::Black));
    titulos.push_back(bgPausa);

}

void states::Pausa::tratarSelecao(sf::String selecao){
    if(selecao == "LOBBY") { pEstados->trocarEstado(LOBBY); }
    else if (selecao == "CONTINUAR") { pEstados->trocarEstado(faseAtual); }
    else if (selecao == "SALVAR") {  
        dynamic_cast<states::Fases::Fase*>(pEstados->getEstado(faseAtual))->salvarFase(); 
        salvo = true;
        textos.clear();
        titulos.clear();
        iniciarTextos();
    }
}