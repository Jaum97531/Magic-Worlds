#include "../include/Ente/Estados/Menus/Lobby.hpp"
#include<iostream>
#include "../include/Ente/Entidades/Projetil.hpp"
#include "../include/Ente/Entidades/EntidadeSaver.hpp"

using namespace std;
states::Lobby::Lobby() : strNome("destruidor"){
    animacao.criaFrames("LOBBY BG", 6, false);
    jogador = Entidades::Personagens::Jogador::getInstancia();
    iniciarTextos();

    criarUtilits();
}

states::Lobby::~Lobby(){
   
}

void states::Lobby::criarUtilits(){

    sf::RectangleShape placa1 = criarShapeTextura("PLACA", sf::Vector2f(400, 400), sf::Vector2f(60, 100), false);
    utilits["PLACA 1"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(60, 100), placa1);

    sf::RectangleShape placa2 = criarShapeTextura("PLACA 2", sf::Vector2f(520, 130), sf::Vector2f(20, 0), false);
    utilits["PLACA 2"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(20, 0), placa2);

    sf::RectangleShape logoVento = criarShapeTextura("LOGO VENTO", sf::Vector2f(70, 80), sf::Vector2f(110, 130), false);
    utilits["ZLOGO VENTO"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(110, 130), logoVento);

    sf::RectangleShape logoFogo = criarShapeTextura("LOGO FOGO", sf::Vector2f(70, 80), sf::Vector2f(110, 210), false);
    utilits["ZLOGO FOGO"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(110, 210), logoFogo);

    sf::RectangleShape logoAgua = criarShapeTextura("LOGO AGUA", sf::Vector2f(70, 80), sf::Vector2f(110, 300), false);
    utilits["ZLOGO AGUA"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(110, 300), logoAgua);

    sf::RectangleShape logoTerra = criarShapeTextura("LOGO TERRA", sf::Vector2f(70, 80), sf::Vector2f(110, 390), false);
    utilits["ZLOGO TERRA"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(110, 390), logoTerra);

    sf::RectangleShape placa3 = criarShapeTextura("PLACA 2", sf::Vector2f(700, 280), sf::Vector2f(pGrafico->get_JANELAX()/2 - 350, 30), false);
    utilits["PLACA 3"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(pGrafico->get_JANELAX()/2 - 350, 30), placa3);
}

void states::Lobby::criaEnt(){
    jogador->setPosition(sf::Vector2f(pGrafico->get_JANELAX()/2, pGrafico->get_JANELAY()/2-300));
    listaEntidades.push_back(jogador);
    jogador->setListaEntidades(&listaEntidades);
    listaEntidades.push_back(jogador->getArea());

    Entidades::Objetos::Plataforma* plataforma = new Entidades::Objetos::Plataforma(TIPO1, sf::Vector2f(1500, 50));
    plataforma->setPosition(sf::Vector2f(200, 700));
    listaEntidades.push_back(plataforma);
}

void states::Lobby::iniciarTextos(){
    const int JANELAX = pGrafico->get_JANELAX();
    const int JANELAY = pGrafico->get_JANELAY();

    sf::Text fase1(criarTexto("FASE 1", 60, sf::Vector2f(JANELAX - 200,JANELAY - 160), AZULVERDE));
    textos.push_back(fase1);

    sf::Text fase2(criarTexto("FASE 2", 60, sf::Vector2f(JANELAX - 200,JANELAY - 80), AZULVERDE));
    textos.push_back(fase2);

    sf::Text quit(criarTexto("VOLTAR", 60, sf::Vector2f(25, JANELAY - 80), AZULVERDE));
    textos.push_back(quit);

    sf::Text rank(criarTexto("RANK", 60, sf::Vector2f(JANELAX/2 - 4*30, JANELAY - 80), AZULVERDE));
    textos.push_back(rank);

    sf::Text elementos(criarTexto("ELEMENTOS:", 55, sf::Vector2f(95, 45), sf::Color::Black));
    elementos.setStyle(sf::Text::Style::Bold);
    titulos.push_back(elementos);

    nomeJogador = criarTexto(strNome, 70, sf::Vector2f(JANELAX/2 - 17.5*strNome.length(), 170), sf::Color::Black);

    sf::Text fogo(criarTexto("FOGO", 50, sf::Vector2f(190, 220), FOGO));
    textos.push_back(fogo);

    sf::Text vento(criarTexto("VENTO", 50, sf::Vector2f(190, 130), VENTO));
    textos.push_back(vento);

    sf::Text agua(criarTexto("AGUA", 50, sf::Vector2f(190, 310), AGUA));
    textos.push_back(agua);

    sf::Text pedra(criarTexto("TERRA", 50, sf::Vector2f(190, 400), TERRA));
    textos.push_back(pedra);

    sf::Text continuar(criarTexto("CONTINUAR", 60, sf::Vector2f(JANELAX - 200, JANELAY - 230), AZULVERDE));
    textos.push_back(continuar);

}

void states::Lobby::tratarSelecao(sf::String selecao){
    if(selecao == "VOLTAR"){  pEstados->trocarEstado(INICIAL); }
    else if (selecao == "FOGO"){ jogador->trocarElemento(selecao); }
    else if (selecao == "VENTO"){ jogador->trocarElemento(selecao); }
    else if (selecao == "AGUA"){ jogador->trocarElemento(selecao); }
    else if (selecao == "TERRA"){  jogador->trocarElemento(selecao); }
    else if(selecao == "FASE 1") { pEstados->trocarEstado(FASE1); jogador->setNome(strNome); }
    else if(selecao == "RANK") { pEstados->trocarEstado(RANK); }
    else if(selecao == "CONTINUAR") { pEstados->trocarEstado(FASE_1); }
}

void states::Lobby::iniciarEstado(){
    observar(pEventos);
    pView->setCenter(sf::Vector2f(pGrafico->get_JANELAX()/2, pGrafico->get_JANELAY()/2));
    pGrafico->getJanela()->setView(*pView);
    jogador->revive();
    criaEnt();
}

void states::Lobby::encerrarEstado(){
    for(auto* ent : listaEntidades){
        if(ent != jogador && ent != jogador->getArea()){ delete ent; }
    }
    listaEntidades.clear();
    pararDeObservar(pEventos);
}

void states::Lobby::verificaJogador(){
    sf::FloatRect jog = jogador->getShape()->getGlobalBounds();
    sf::FloatRect view (0, 0,pView->getSize().x,pView->getSize().y);
    
    if(!pColisao->verificaEntidadeDentroDaTela(jogador)){
        jogador->setPosition(sf::Vector2f(pGrafico->get_JANELAX()/2, pGrafico->get_JANELAY()/2));
        jogador->zerarGravidade();
    }
}

void states::Lobby::notifica(int tipo){
    if(tipo == MOUSE) selecionar();
    else if(tipo == KEYBOARD && digitando) { digitar(); }
}

void states::Lobby::execute(){
    nomeJogador.setString(strNome);
    verificaJogador();
    for(auto* ent : listaEntidades) { 
        ent->execute(); 

        if(!ent->getEstatico()) ent->acelerarGravidade(); 
    }
    pColisao->executeColisoes(&listaEntidades);
    desenhar();
}

void states::Lobby::desenhar(){
    if(animacao.TemAnimacao()) { bool animou = animacao.anima(&background); }
    pGrafico->draw(background);

    desenharUtilits();
    desenharTexto();
    for(auto* ent : listaEntidades) { ent->desenhar(); }    

    pGrafico->draw(nomeJogador);
}

void states::Lobby::digitar(){
    sf::Event* evento = pEventos->getEvento();
    if (evento->text.unicode < 128 && evento->text.unicode != 8 && strNome.length() < 16) {
        strNome += static_cast<char>(evento->text.unicode);
    }
    else if (evento->text.unicode == 8 && !strNome.empty()){
        strNome.pop_back();
    }

    nomeJogador.setPosition(sf::Vector2f(pGrafico->get_JANELAX()/2 - 17.5*strNome.length(), 170));
}

void states::Lobby::carregarFaseSalva(){
    
}

void states::Lobby::selecionar(){
    mouse.setPosition(sf::Vector2f(sf::Mouse::getPosition(*pGrafico->getJanela())));

    for(auto& texto : textos){
        sf::String str = texto.getString();

        if (pColisao->colideRect(mouse.getGlobalBounds(), texto.getGlobalBounds()) && !digitando){
            if(str == "FOGO"){ texto.setFillColor(FOGO_SELECIONADO); }
            else if(str == "VENTO"){ texto.setFillColor(VENTO_SELECIONADO);}
            else if(str == "TERRA"){ texto.setFillColor(TERRA_SELECIONADO); }
            else if(str == "AGUA"){ texto.setFillColor(AGUA_SELECIONADO); }
            else { texto.setFillColor(CYANOCLARO); }

            if (pEventos->verificaClickMouse()) { 
                tratarSelecao(str);
            }

        } else{
            if(str == "FOGO"){ texto.setFillColor(FOGO); }
            else if(str == "VENTO"){ texto.setFillColor(VENTO); }
            else if(str == "TERRA"){ texto.setFillColor(TERRA); }
            else if(str == "AGUA") { texto.setFillColor(AGUA); }
            else { texto.setFillColor(AZULVERDE); }
        }
    }
    
    if(pEventos->verificaClickMouse()){
        if(pColisao->colideRect(utilits["PLACA 3"].second.getGlobalBounds(), mouse.getGlobalBounds())){ digitando = true; } 
        else { digitando = false; }
        jogador->setPodeMover(!digitando);
    }
}

