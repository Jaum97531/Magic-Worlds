#include "../include/Ente/Estados/Menus/Lobby.hpp"
#include "../include/Ente/Entidades/Projetil.hpp"
#include "../include/Ente/FaseSaver.hpp"

states::Lobby::Lobby() : strNome("destruidor"){
    animacao.criaFrames("LOBBY BG", 6, false);
    jogador = Entidades::Personagens::Jogador::getInstancia();
}

states::Lobby::~Lobby(){
   
}

void states::Lobby::criarUtilits(){

    sf::RectangleShape placa1 = criarShapeTextura("PLACA", sf::Vector2f(400, 400), sf::Vector2f(60, 100), false);
    utilits["PLACA 1"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(60, 100), placa1);

    sf::RectangleShape placa2 = criarShapeTextura("PLACA 2", sf::Vector2f(520, 130), sf::Vector2f(20, 0), false);
    utilits["PLACA 2"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(20, 0), placa2);

    sf::RectangleShape logoVento = criarShapeTextura("FURACAO", sf::Vector2f(75, 65), sf::Vector2f(110, 145), false);
    utilits["ZLOGO VENTO"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(110, 145), logoVento);

    sf::RectangleShape logoFogo = criarShapeTextura("LOGO FOGO", sf::Vector2f(70, 80), sf::Vector2f(110, 210), false);
    utilits["ZLOGO FOGO"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(110, 210), logoFogo);

    sf::RectangleShape logoAgua = criarShapeTextura("LOGO AGUA", sf::Vector2f(70, 80), sf::Vector2f(110, 300), false);
    utilits["ZLOGO AGUA"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(110, 300), logoAgua);

    sf::RectangleShape logoTerra = criarShapeTextura("LOGO TERRA", sf::Vector2f(70, 80), sf::Vector2f(110, 390), false);
    utilits["ZLOGO TERRA"] = std::pair<sf::Vector2f, sf::RectangleShape>(sf::Vector2f(110, 390), logoTerra);

    sf::RectangleShape placa3 = criarShapeTextura("PLACA 2", sf::Vector2f(600, 250), sf::Vector2f(pGrafico->get_JANELAX()/2 - 300, 30), false);
    utilits["PLACA 3"] = std::pair<sf::Vector2f, sf::RectangleShape>(placa3.getPosition(), placa3);
}

void states::Lobby::criaEnt(){
    jogador->setPosition(sf::Vector2f(pGrafico->get_JANELAX()/2, pGrafico->get_JANELAY()/2-300));
    listaEntidades.push_back(jogador);
    jogador->setListaEntidades(listaEntidades.getListaTemporaria());
    listaEntidades.push_back(jogador->getArea());

    Entidades::Objetos::Plataforma* plataforma = new Entidades::Objetos::Plataforma(TIPO1, sf::Vector2f(1500, 50));
    plataforma->setPosition(sf::Vector2f(200, 700));
    listaEntidades.push_back(plataforma);
}

void states::Lobby::resized(){

}

void states::Lobby::iniciarTextos(){
    const int JANELAX = pGrafico->get_JANELAX();
    const int JANELAY = pGrafico->get_JANELAY();

    sf::Text novoJogo(criarTexto("NOVO JOGO", 60, sf::Vector2f(JANELAX - 300, JANELAY - 90), AZULVERDE));
    textos.push_back(novoJogo);

    sf::Text bgNovoJogo(criarTexto("NOVO JOGO", 60, sf::Vector2f(JANELAX - 300 - 5, JANELAY - 90), sf::Color::Black));
    titulos.push_back(bgNovoJogo);

    sf::Text quit(criarTexto("VOLTAR", 60, sf::Vector2f(25, JANELAY - 80), AZULVERDE));
    textos.push_back(quit);

    sf::Text bgQuit(criarTexto("VOLTAR", 60, sf::Vector2f(25 - 5, JANELAY - 80), sf::Color::Black));
    titulos.push_back(bgQuit);

    sf::Text rank(criarTexto("RANK", 60, sf::Vector2f(JANELAX/2 - 4*30, JANELAY - 80), AZULVERDE));
    textos.push_back(rank);

    sf::Text bgRank(criarTexto("RANK", 60, sf::Vector2f(JANELAX/2 - 4*30 - 5, JANELAY - 80), sf::Color::Black));
    titulos.push_back(bgRank);

    sf::Text elementos(criarTexto("ELEMENTOS:", 55, sf::Vector2f(95, 45), sf::Color::Black));
    elementos.setStyle(sf::Text::Style::Bold);
    titulos.push_back(elementos);

    nomeJogador = criarTexto(strNome, 70, sf::Vector2f(JANELAX/2 - 17.5*strNome.length(), 150), sf::Color::Black);

    sf::Text fogo(criarTexto("FOGO", 50, sf::Vector2f(190, 220), COR_FOGO));
    textos.push_back(fogo);

    sf::Text bgfogo(criarTexto("FOGO", 50, sf::Vector2f(190 - 5, 220), sf::Color::Black));
    titulos.push_back(bgfogo);

    sf::Text vento(criarTexto("VENTO", 50, sf::Vector2f(190, 135), COR_VENTO));
    textos.push_back(vento);

    sf::Text bgvento(criarTexto("VENTO", 50, sf::Vector2f(190 - 5, 135), sf::Color::Black));
    titulos.push_back(bgvento);

    sf::Text agua(criarTexto("AGUA", 50, sf::Vector2f(190, 310), COR_AGUA));
    textos.push_back(agua);

    sf::Text bgagua(criarTexto("AGUA", 50, sf::Vector2f(190 - 5, 310), sf::Color::Black));
    titulos.push_back(bgagua);

    sf::Text pedra(criarTexto("TERRA", 50, sf::Vector2f(190, 400), COR_TERRA));
    textos.push_back(pedra);

    sf::Text bgpedra(criarTexto("TERRA", 50, sf::Vector2f(190 - 5, 400), sf::Color::Black));
    titulos.push_back(bgpedra);

    FaseSaver saver;
    if(!saver.vazio()){
        sf::Text continuar(criarTexto("CONTINUAR", 60, sf::Vector2f(JANELAX - 330, JANELAY - 190), AZULVERDE));
        textos.push_back(continuar);

        sf::Text bgcontinuar(criarTexto("CONTINUAR", 60, sf::Vector2f(JANELAX - 330 - 5, JANELAY - 190), sf::Color::Black));
        titulos.push_back(bgcontinuar);
    }
}

void states::Lobby::tratarSelecao(sf::String selecao){
    if(selecao == "VOLTAR"){  pEstados->trocarEstado(INICIAL); }
    else if (selecao == "FOGO"){ jogador->trocarElemento(selecao); }
    else if (selecao == "VENTO"){ jogador->trocarElemento(selecao); }
    else if (selecao == "AGUA"){ jogador->trocarElemento(selecao); }
    else if (selecao == "TERRA"){  jogador->trocarElemento(selecao); }
    else if(selecao == "NOVO JOGO") { pEstados->trocarEstado(NEWGAME); jogador->setNome(strNome); }
    else if(selecao == "RANK") { pEstados->trocarEstado(RANK); }
    else if(selecao == "CONTINUAR") { pEstados->trocarEstado(CONTINUE); }
}

void states::Lobby::iniciarEstado(){
    observar(pEventos);
    iniciarTextos();
    criarUtilits();
    pView->setCenter(sf::Vector2f(pGrafico->get_JANELAX()/2, pGrafico->get_JANELAY()/2));
    pGrafico->getJanela()->setView(*pView);
    jogador->revive();
    criaEnt();
}

void states::Lobby::encerrarEstado(){
    listaEntidades.clear();

    textos.clear();
    titulos.clear();
    utilits.clear();
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
    listaEntidades.executarEntidades();
    pColisao->executeColisoes(listaEntidades.getMapEntidade());
    desenhar();

    listaEntidades.mesclarListaTemporaria();
    listaEntidades.removerInativos();
}

void states::Lobby::desenhar(){
    if(animacao.TemAnimacao()) { bool animou = animacao.anima(&background, false); }
    pGrafico->draw(background);

    desenharUtilits();
    desenharTexto();
    listaEntidades.desenharEntidades();    

    pGrafico->draw(nomeJogador);
}

void states::Lobby::digitar(){
    sf::Event* evento = pEventos->getEvento();
    if (evento->text.unicode < 128 && evento->text.unicode != 8 && strNome.length() < 15 
        && evento->text.unicode != 32 && evento->text.unicode != 13) {
        strNome += static_cast<char>(evento->text.unicode);
    }
    else if (evento->text.unicode == 8 && !strNome.empty()){
        strNome.pop_back();
    }

    nomeJogador.setPosition(sf::Vector2f(pGrafico->get_JANELAX()/2 - 17.5*strNome.length(), 150));
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
            if(str == "FOGO"){ texto.setFillColor(COR_FOGO); }
            else if(str == "VENTO"){ texto.setFillColor(COR_VENTO); }
            else if(str == "TERRA"){ texto.setFillColor(COR_TERRA); }
            else if(str == "AGUA") { texto.setFillColor(COR_AGUA); }
            else { texto.setFillColor(AZULVERDE); }
        }
    }
    
    if(pEventos->verificaClickMouse()){
        if(pColisao->colideRect(utilits["PLACA 3"].second.getGlobalBounds(), mouse.getGlobalBounds())){ digitando = true; } 
        else { digitando = false; }
        jogador->setPodeMover(!digitando);
    }
}

