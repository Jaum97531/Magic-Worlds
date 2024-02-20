#include "../include/Ente/Estados/Fases/Fase.hpp"
#include <cmath>
#include <iostream>
#include "../include/Ente/Entidades/Objetos/Lava.hpp"
#include "../include/Ente/Entidades/Objetos/Caixa.hpp"
#include "../include/Ente/Entidades/Personagens/Inimigos/Esqueleto.hpp"
#include "../include/Ente/Entidades/Personagens/Inimigos/Zumbi.hpp"
#include "../include/Ente/Entidades/Personagens/Inimigos/Fantasma.hpp"
#include "../include/Gerenciadores/Algoritimos.hpp"
#include "../include/Ente/Entidades/Projetil.hpp"

using namespace std;

 states::Fases::Fase::Fase() {  
    posJogAntiga = sf::Vector2f(0, 0);
    aleatoria = false;
    Cronometro_De_Atualizacao.restart();
    forcarAtualizacao = false;
    salvo = false;
}

states::Fases::Fase::~Fase(){
    for(auto it : posInimigos){
        delete it.first;
    }
    posInimigos.clear();
}

void states::Fases::Fase::criarLava(sf::Vector2f size, sf::Vector2f pos){
    Entidades::Objetos::Lava* lava = new Entidades::Objetos::Lava();
    lava->setSize(size);
    lava->setPosition(pos);
    listaEntidades.push_back(lava);
    gerenAnimacao->pushLava(lava->getShapeAnimacao());
}

Personagens::Inimigo* states::Fases::Fase::criarZumbi(sf::Vector2f posicao){
    Entidades::Personagens::Zumbi* zumbi = new Entidades::Personagens::Zumbi();
    zumbi->setPosition(sf::Vector2f(posicao));
    listaEntidades.push_back(zumbi);
    listaEntidades.push_back(zumbi->getArea());
    return zumbi;
}

Personagens::Inimigo* states::Fases::Fase::criarEsqueleto(sf::Vector2f posicao){
    Entidades::Personagens::Esqueleto* esq = new Entidades::Personagens::Esqueleto();
    esq->setPosition(sf::Vector2f(posicao));
    listaEntidades.push_back(esq);
    listaEntidades.push_back(esq->getArea());
    return esq;
}

Personagens::Inimigo* states::Fases::Fase::criarFantasma(sf::Vector2f posicao){
    Entidades::Personagens::Fantasma* fantasma = new Entidades::Personagens::Fantasma();
    fantasma->setPosition(sf::Vector2f(posicao));
    listaEntidades.push_back(fantasma);
    listaEntidades.push_back(fantasma->getArea());
    return fantasma;
}

void states::Fases::Fase::criarUtilits(){
    sf::RectangleShape vidaJogador = criarShapeTextura("CORACAO", sf::Vector2f(70*jogador->getMaxVida(), 65), sf::Vector2f(235, 60), true);
    utilits["VIDA"] = std::pair<sf::Vector2f, sf::RectangleShape>(vidaJogador.getPosition(),vidaJogador);

    sf::RectangleShape bgVidaJogador = criarShapeTextura("CORACAO VAZIO", sf::Vector2f(70*jogador->getMaxVida(),65), sf::Vector2f(235, 60), true);
    utilits["BG VIDA"] = std::pair<sf::Vector2f, sf::RectangleShape>(bgVidaJogador.getPosition(), bgVidaJogador);

    std::string keyLogo = "LOGO ";
    keyLogo += jogador->getElementoo();
    sf::RectangleShape logoElemento = criarShapeTextura(keyLogo, sf::Vector2f(100, 110), sf::Vector2f(110, 40), false);
    utilits["LOGO ELEMENTO"] = std::pair<sf::Vector2f, sf::RectangleShape>(logoElemento.getPosition(), logoElemento);
}

void states::Fases::Fase::removerEntidade(Entidade* ent){
    if(ent->getTipoSecundario(Type::Inimigo)){
        Personagens::Inimigo* inimigo = dynamic_cast<Personagens::Inimigo*>(ent);
        auto it = std::find(listaEntidades.begin(), listaEntidades.end(), inimigo);
        if(listaEntidades.end() != it) listaEntidades.erase(it);  
    
        it = std::find(listaEntidades.begin(), listaEntidades.end(), inimigo->getArea());
        if(listaEntidades.end() != it) listaEntidades.erase(it);

        delete ent;
        ent = nullptr;
    }
    else if(ent->getTipoSecundario(Type::Objeto)){

    }
}

void states::Fases::Fase::criaInimigos(){ 
    std::uniform_int_distribution<> distribuicao(1, 30);
    for(auto it : posInimigos){
        if(it.second == nullptr){
            int rand = distribuicao(Algoritimos::getGenerator());
            if(rand < 11){  posInimigos[it.first] = criarEsqueleto(*it.first); }
            else if (rand < 20) {  posInimigos[it.first] =  criarZumbi(*it.first); }
            else { posInimigos[it.first] = criarFantasma(*it.first); }
        }
        else if(!it.second->getAtivo()) {
            removerEntidade(it.second); 
            it.second = nullptr;
            int rand = distribuicao(Algoritimos::getGenerator());
            if(rand < 11){  posInimigos[it.first] = criarEsqueleto(*it.first); }
            else if (rand < 20) {  posInimigos[it.first] =  criarZumbi(*it.first); }
            else { posInimigos[it.first] = criarFantasma(*it.first); }
        }
    }
}

void states::Fases::Fase::criarCaixa(sf::Vector2f posicao){
    Entidades::Objetos::Caixa* Caixa = new Entidades::Objetos::Caixa();
    Caixa->setPosition(sf::Vector2f(posicao));
    listaEntidades.push_back(Caixa);
}

void states::Fases::Fase::criarMapa(std::string plat, std::string fase) {
    sf::Image imagem = pGrafico->getPimagens()->getTextura(plat)->copyToImage();

    float sizeX = imagem.getSize().x;
    float sizeY = imagem.getSize().y;
    sf::Vector2f proporcao = sf::Vector2f(pGrafico->get_JANELAX()*2/sizeX, pGrafico->get_JANELAY()/sizeY);

    sf::Texture* textura = pGrafico->getPimagens()->getTextura(fase);
    textura->setSmooth(true);

    plataformas.setSize(sf::Vector2f(pGrafico->get_JANELAX()*2, pGrafico->get_JANELAY()));
    plataformas.setPosition(sf::Vector2f(0, 0));
    plataformas.setTexture( textura);

    for (int y = 0; y < sizeY; y += valorTileMap) {
        float posY = y * proporcao.y;
        for (int x = 0; x < sizeX; x += valorTileMap) {
            int posX = x * proporcao.x;

            sf::Color cor = imagem.getPixel(x, y);
            int tamanhoX = 0;
            while(cor.a){
                x += valorTileMap;
                tamanhoX += valorTileMap;
                cor = imagem.getPixel(x, y);
            }
            if (tamanhoX > 0) {
                // Usando 'float' para as coordenadas e 'round' para arredondar para o inteiro mais próximo
                int larguraBloco = tamanhoX * proporcao.x;
                int alturaBloco = valorTileMap * proporcao.y;
                
                criarPlataforma(sf::Vector2f(std::round(posX), std::round(posY)), sf::Vector2f(larguraBloco, alturaBloco));
            }
        }
    }
}

void states::Fases::Fase::criarPlataforma(sf::Vector2f pos, sf::Vector2f size){
    Objetos::Plataforma* plat = new Objetos::Plataforma();
    plat->setSize(size);
    plat->setColor(sf::Color::Red);
    plat->setPosition(pos);
    listaEntidades.push_back(plat);
}

void states::Fases::Fase::atualizarView(){
    float limiteMinimo = pGrafico->get_JANELAX()/2;
    float limiteMaximo = limiteDaFase.x - pGrafico->get_JANELAX()/2;
    sf::Vector2f centro = pView->getCenter();

    if(centro.x >= limiteMinimo && centro.x <= limiteMaximo){
        sf::Vector2f posJog = jogador->getShape()->getPosition();

        if(posJog.x >= 250 + centro.x || posJog.x <= centro.x - 250){
            
            int velocidadeJog = jogador->getVelocidade().x;
            int velocidade = (jogador->getEstado() == CORRENDO) ? (2*velocidadeJog-1) : velocidadeJog-1;

            if(forcarAtualizacao) { velocidade = 30; }

            float novaPosicaoX;
            if(posJog.x >= 250 + centro.x) { novaPosicaoX = std::max(limiteMinimo, std::min(limiteMaximo, centro.x + velocidade)); }
            else { novaPosicaoX = std::max(limiteMinimo, std::min(limiteMaximo, centro.x-velocidade)); }

            pView->setCenter(sf::Vector2f(novaPosicaoX, pGrafico->get_JANELAY() / 2));
            posJogAntiga = posJog;
            background.setPosition(sf::Vector2f(pView->getCenter().x - pGrafico->get_JANELAX()/2, 0));
            atualizarPosicaoDosUtilits();
            pGrafico->getJanela()->setView(*pView);
        
        }
        else{
            forcarAtualizacao = false;
        }
    }
}

void states::Fases::Fase::atualizarPosicaoDosUtilits(){
    sf::Vector2f centro = pView->getCenter();
    sf::Vector2f size = pView->getSize();
    sf::FloatRect rect = sf::FloatRect(centro.x - size.x/2, centro.y - size.y/2, centro.x + size.x/2, centro.y + size.y/2);
    for(auto& shape : utilits){
        sf::Vector2f posNova = sf::Vector2f(rect.left + shape.second.first.x, rect.top + shape.second.first.y);
        shape.second.second.setPosition(posNova);
    }
}

void states::Fases::Fase::atualizarVidaJogador(){
    int vidaAtual = jogador->getVida();
    int vidaMax = jogador->getMaxVida();
    
    if(vidaAtual < vidaMax){
        sf::RectangleShape& vida = utilits["VIDA"].second;
        vida.setSize(sf::Vector2f(70*vidaAtual, 65));
        vida.setTextureRect(sf::IntRect(0, 0, 70*vidaAtual, 65));
    }
}

bool states::Fases::Fase::verificarLimites(Entidade* ent){
    sf::FloatRect rect1 = ent->getShape()->getGlobalBounds();
    return !rect1.intersects(sf::FloatRect(-70, -1000, limiteDaFase.x, limiteDaFase.y + 100));
}

void states::Fases::Fase::desenharEntidades(){
    for(auto* ent : listaEntidades){
        if(ent->getAtivo() && ent != jogador && pColisao->verificaEntidadeDentroDaTela(ent))
            ent->desenhar();
    }

    if(jogador->getAtivo() &&  pColisao->verificaEntidadeDentroDaTela(jogador)){
        jogador->desenhar();
    }
}

void states::Fases::Fase::desenhar(){
    if(animacao.TemAnimacao()) bool animou = animacao.anima(&background);
    pGrafico->draw(background);
    pGrafico->draw(plataformas);
    desenharUtilits();
    desenharTexto();
    desenharEntidades();
}


void states::Fases::Fase::executarEntidades(){
    sf::FloatRect frustum = pView->getViewport();

    for(auto* ent : listaEntidades){ 
        if(ent->getAtivo()){
            if(pColisao->verificaEntidadeDentroDaTela(ent)){
                ent->execute(); 
                if(!ent->getEstatico()) { ent->acelerarGravidade(); }
            }
            if(verificarLimites(ent)) { ent->foraDosLimites(); }
        }
    }
}

void states::Fases::Fase::setJogador(Personagens::Jogador* jog){
    jogador = jog;
    //listaEntidades.push_back(jogador); 
    listaEntidades.push_back(jogador->getArea());
    gerenAnimacao =  GR::GerenciadorAnimacao::getInstacia(jogador);
    jogador->setListaEntidades(&listaEntidades);
    Personagens::Inimigo::setJogador(jogador);
}

void states::Fases::Fase::verificaAtualizacao(){
    if(Cronometro_De_Atualizacao.getElapsedTime().asSeconds() >= 90){
        criaInimigos();
        Cronometro_De_Atualizacao.restart();
    }
}

void states::Fases::Fase::iniciarEstado(){
    observar(pEventos);
    forcarAtualizacao = true;
}

void states::Fases::Fase::execute(){   
    executarEntidades();
    pColisao->executeColisoes(&listaEntidades);
    atualizarVidaJogador();
    atualizarView();
    
    gerenAnimacao->atualizaLavas();
    desenhar();
   
    if(pEventos->verificaClickTecla(sf::Keyboard::P)){
        pEstados->trocarEstado(PAUSA);
    }
    else if(jogador->verificaMorte()){
        pEstados->trocarEstado(GAMEOVER);
    }
    else if(pEventos->verificaClickTecla(sf::Keyboard::O) && !salvo){
        salvarFase();
        salvo = true;
    }
    verificaAtualizacao();
}

void states::Fases::Fase::salvarFase(){
    salvamento.salvarEntidades(listaEntidades);
}