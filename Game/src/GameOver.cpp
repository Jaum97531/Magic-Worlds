#include "../include/Ente/Estados/Menus/GameOver.hpp"
#include "../include/Ente/Estados/Menus/Rank.hpp"
#include "../include/Ente/Entidades/Personagens/Jogador.hpp"

states::GameOver::GameOver() : ptsJogador(0){
    salvo = false;
    iniciarTextos();
}

states::GameOver::~GameOver(){

}

void states::GameOver::iniciarEstado(){
    observar(pEventos);
    salvo = false;
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
    else if (selecao == "SALVAR NO RANKING"){
        dynamic_cast<Rank*>(pEstados->getEstado(RANK))->salvarPontuacao(nome, ptsJogador);
        salvo = true;
        textos.clear();
        titulos.clear();
        iniciarTextos();
    }
    
}

void states::GameOver::iniciarTextos(){
    const int JANELAX = pGrafico->get_JANELAX();
    const int JANELAY = pGrafico->get_JANELAY();

    this->ptsJogador = Entidades::Personagens::Jogador::getInstancia()->getPontos();
    this->nome = Entidades::Personagens::Jogador::getInstancia()->getNome();

    sf::Text pontos = criarTexto(std::to_string(ptsJogador), 70, sf::Vector2f(JANELAX/2 + 60, JANELAY/2 - 100), AZULVERDE);
    titulos.push_back(pontos);

    sf::Text bgPontos = criarTexto(std::to_string(ptsJogador), 70, sf::Vector2f(JANELAX/2 + 60 - 5, JANELAY/2 - 100), sf::Color::Black);
    titulos.push_back(bgPontos);
    
    sf::Text pontosJogador = criarTexto("PONTOS: ", 70, sf::Vector2f(JANELAX/2 - 220, JANELAY/2 - 100), AZULVERDE);
    titulos.push_back(pontosJogador);

    sf::Text bgPontosJogador = criarTexto("PONTOS: ", 70, sf::Vector2f(JANELAX/2 - 220 - 5, JANELAY/2 - 100), sf::Color::Black);
    titulos.push_back(bgPontosJogador);

    sf::Text perdeu = criarTexto("VOCE MORREU", 120, sf::Vector2f(JANELAX/2 - 410, 60), AZULVERDE);
    titulos.push_back(perdeu);

    sf::Text bgPerdeu = criarTexto("VOCE MORREU", 120, sf::Vector2f(JANELAX/2 - 410 - 5, 60), sf::Color::Black);
    titulos.push_back(bgPerdeu);

    sf::Text lobby = criarTexto("LOBBY", 70, sf::Vector2f(JANELAX/2 - 130, JANELAY - 150), AZULVERDE);
    textos.push_back(lobby);

    sf::Text bgLobby = criarTexto("LOBBY", 70, sf::Vector2f(JANELAX/2 - 130 - 5, JANELAY - 150), sf::Color::Black);
    titulos.push_back(bgLobby);

    if(!salvo){
        sf::Text salvar = criarTexto("SALVAR NO RANKING", 70, sf::Vector2f(JANELAX/2 - 330, JANELAY/2 + 50), AZULVERDE);
        textos.push_back(salvar);

        sf::Text BGsalvar = criarTexto("SALVAR NO RANKING", 70, sf::Vector2f(JANELAX/2 - 330 - 5, JANELAY/2 + 50), sf::Color::Black);
        titulos.push_back(BGsalvar);
    } else{
        sf::Text salvar = criarTexto("SALVO NO RANKING", 70, sf::Vector2f(JANELAX/2 - 330, JANELAY/2 + 50 + 5), AZULVERDE);
        titulos.push_back(salvar);

        sf::Text BGsalvar = criarTexto("SALVO NO RANKING", 70, sf::Vector2f(JANELAX/2 - 330 - 5, JANELAY/2 + 50 + 5), sf::Color::Black);
        titulos.push_back(BGsalvar);
    }
}

void states::GameOver::setAnimacao(int fase){
    switch(fase){
        case FASE1 :
            animacao.criaFrames("VULCAO", 8, false);
            break;
    }
}