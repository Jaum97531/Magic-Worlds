#include "../include/Ente/Estados/Fases/Fase.hpp"
#include <cmath>
#include "../include/Ente/Entidades/Objetos/Lava.hpp"
#include "../include/Ente/Entidades/Objetos/Caixa.hpp"
#include "../include/Ente/Entidades/Personagens/Inimigos/Esqueleto.hpp"
#include "../include/Ente/Entidades/Personagens/Inimigos/Zumbi.hpp"
#include "../include/Ente/Entidades/Personagens/Inimigos/Fantasma.hpp"
#include "../include/Gerenciadores/Algoritimos.hpp"
#include "../include/Ente/Entidades/Projetil.hpp"

 states::Fases::Fase::Fase() {  
    posJogAntiga = sf::Vector2f(0, 0);
    Cronometro_De_Atualizacao.restart();
    forcarAtualizacao = false;

    setJogador(Personagens::Jogador::getInstancia());
    listaEntidades.push_back(jogador);
    listaEntidades.push_back(jogador->getArea());
    criarUtilits();
    jogador->revive();
    iniciarTextos();
}

states::Fases::Fase::Fase(std::unordered_map<int, Entidade*> map){
    posJogAntiga = sf::Vector2f(0, 0);
    Cronometro_De_Atualizacao.restart();
    forcarAtualizacao = false;

    listaEntidades = map; 
    setJogador(Personagens::Jogador::getInstancia());
    criarUtilits();
    iniciarTextos();
}

states::Fases::Fase::~Fase(){
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
    sf::Vector2f SIZE_VIDA = sf::Vector2f(70*jogador->getMaxVida(), 65);
    sf::Vector2f POS_VIDA = sf::Vector2f(80, 60);

    sf::RectangleShape vidaJogador = criarShapeTextura("CORACAO", SIZE_VIDA, POS_VIDA, true);
    utilits["VIDA"] = std::pair<sf::Vector2f, sf::RectangleShape>(POS_VIDA, vidaJogador);

    sf::RectangleShape bgVidaJogador = criarShapeTextura("CORACAO VAZIO", SIZE_VIDA, POS_VIDA, true);
    utilits["BG VIDA"] = std::pair<sf::Vector2f, sf::RectangleShape>(POS_VIDA, bgVidaJogador);

    sf::String elemento = jogador->getElementoo();
    std::string keyLogo = "";
    if(elemento == "FOGO"){ keyLogo = "LOGO FOGO"; animaCarga.criaFrames("BARRA FOGO", 13, false); }
    else if(elemento == "VENTO") { keyLogo = "FURACAO"; animaCarga.criaFrames("BARRA VENTO", 13, false); }
    else if(elemento == "AGUA") { keyLogo = "LOGO AGUA"; animaCarga.criaFrames("BARRA AGUA", 13, false); }
    else { keyLogo = "LOGO TERRA"; animaCarga.criaFrames("BARRA TERRA", 13, false); }

    sf::RectangleShape logoElemento = criarShapeTextura(keyLogo, sf::Vector2f(115, 100), sf::Vector2f(pGrafico->get_JANELAX() - 531, 35), false);
    utilits["LOGO ELEMENTO"] = std::pair<sf::Vector2f, sf::RectangleShape>(logoElemento.getPosition(), logoElemento);

    sf::RectangleShape barraCarga = criarShapeTextura("BARRA VENTO", sf::Vector2f(426, 60), sf::Vector2f(pGrafico->get_JANELAX() - 486, 60), false);
    utilits["BARRA DE CARGA"] = std::pair<sf::Vector2f, sf::RectangleShape>(barraCarga.getPosition(), barraCarga);

    sf::RectangleShape retanguloPontos = criarShapeTextura("", sf::Vector2f(100, 60), sf::Vector2f(pGrafico->get_JANELAX()/2, 60), false);
    utilits["BARRA PONTOS"] = std::pair<sf::Vector2f, sf::RectangleShape>(retanguloPontos.getPosition(), retanguloPontos);
}

void states::Fases::Fase::criaInimigos(){ 
    std::uniform_int_distribution<> distribuicao(1, 30);
    for(auto it : posInimigos){
        if(it.second == -1 || !listaEntidades.returnEntidade(it.second)){
            int randonValue = distribuicao(Algoritimos::getGenerator());
            if(randonValue < 6){  posInimigos[it.first] = criarFantasma(it.first)->getId(); }
            else if (randonValue < 23) {  posInimigos[it.first] =  criarZumbi(it.first)->getId(); }
            else { posInimigos[it.first] = criarEsqueleto(it.first)->getId(); }
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
    
    for (int y = 0; y < sizeY; y += valorTileMap) 
    {
        float posY = y * proporcao.y;

        for (int x = 0; x < sizeX; x += valorTileMap) 
        {
            int posX = x * proporcao.x;

            sf::Color cor = imagem.getPixel(x, y);
            int tamanhoX = 0;

            while(cor.a)
            {
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

void states::Fases::Fase::iniciarTextos(){
    int JANELAX = pGrafico->get_JANELAX();
    int JANELAY = pGrafico->get_JANELAY();
    
    sf::Text bgpontos = criarTexto(std::to_string(jogador->getPontos()), 60, sf::Vector2f(JANELAX/2 - 15, 60), sf::Color::Black);
    titulos.push_back(bgpontos);

    sf::Text pontos = criarTexto(std::to_string(jogador->getPontos()), 60, sf::Vector2f(JANELAX/2 - 10, 60), AZULVERDE);
    titulos.push_back(pontos);
}

void states::Fases::Fase::atualizarPontos(){
    for(auto& it : titulos){
        it.setString(std::to_string(jogador->getPontos()));
    }
}

void states::Fases::Fase::criarPlataforma(sf::Vector2f pos, sf::Vector2f size){
    Objetos::Plataforma* plat = new Objetos::Plataforma();
    plat->setSize(size);
    plat->setPosition(pos);
    listaEntidades.push_back(plat);
}

void states::Fases::Fase::atualizarView(){
    float limiteMinimo = pGrafico->get_JANELAX()/2;
    float limiteMaximo = limiteDaFase.width - pGrafico->get_JANELAX()/2;

    sf::Vector2f centro = pView->getCenter();

    if(centro.x >= limiteMinimo && centro.x <= limiteMaximo){
        sf::Vector2f posJog = jogador->getShape()->getPosition();

        if(posJog.x >= 250 + centro.x || posJog.x <= centro.x - 250){
            
            int velocidadeJog = jogador->getVelocidade().x;
            int velocidade = (jogador->getEstado() == CORRENDO) ? (2*velocidadeJog-1) : velocidadeJog-1;

            if(forcarAtualizacao){ velocidade = 20; }

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
    sf::FloatRect rect(
        centro.x - size.x/2,
        centro.y - size.y/2,
        centro.x + size.x/2,
        centro.y + size.y/2
    );

    for(auto& shape : utilits){
        sf::Vector2f posNova = sf::Vector2f(rect.left + shape.second.first.x, rect.top + shape.second.first.y);
        shape.second.second.setPosition(posNova);
    }
    bool entrou = false;
    sf::Vector2f posicao = utilits["BARRA PONTOS"].second.getPosition();
    for(auto& it : titulos){
        if(!entrou) { it.setPosition(sf::Vector2f(posicao.x-5, posicao.y)); entrou = true; }
        else it.setPosition(posicao);
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

void states::Fases::Fase::desenhar(){
    if(animacao.TemAnimacao()) bool animou = animacao.anima(&background, false);
    pGrafico->draw(background);
    pGrafico->draw(plataformas);
    desenharTexto();
    listaEntidades.desenharEntidades();
    desenharUtilits();
}

void states::Fases::Fase::setJogador(Personagens::Jogador* jog){
    jogador = jog;
    gerenAnimacao =  GR::GerenciadorAnimacao::getInstacia(jogador);
    jogador->setListaEntidades(listaEntidades.getListaTemporaria());
    Personagens::Inimigo::setJogador(jogador);
}

void states::Fases::Fase::verificaAtualizacao(){
    int tempo = Cronometro_De_Atualizacao.getElapsedTime().asSeconds();
    if(tempo >= 60){
        criaInimigos();
        Cronometro_De_Atualizacao.restart();
    }
}

void states::Fases::Fase::iniciarEstado(){
    observar(pEventos);
    forcarAtualizacao = true;
}

void states::Fases::Fase::tratarSelecao(){
    if(pEventos->verificaClickTecla(sf::Keyboard::P)){
        pEstados->trocarEstado(PAUSA);
    }
    else if(jogador->verificaMorte()){
        pEstados->trocarEstado(GAMEOVER);
    }
}

void states::Fases::Fase::resized(){

}

void states::Fases::Fase::execute(){   
    listaEntidades.executarEntidades();

    bool animou = animaCarga.anima(&utilits["BARRA DE CARGA"].second, (double)jogador->getCarga());
    pColisao->executeColisoes(listaEntidades.getMapEntidade());
    atualizarVidaJogador();
    atualizarView();
    
    gerenAnimacao->atualizaLavas();
    desenhar();
    tratarSelecao();

    listaEntidades.mesclarListaTemporaria();
    listaEntidades.verificaLimites(limiteDaFase);
    verificaAtualizacao();
    atualizarPontos();
    listaEntidades.removerInativos();
 }


void states::Fases::Fase::setInimigos(){
    std::unordered_map<int, Entidade*> mapEntidade = *listaEntidades.getMapEntidade();
    for(auto it : mapEntidade){
        if(it.second != nullptr && it.second->getTipo(Type::Inimigo)){
            for(auto it2 : posInimigos){
                if(it2.second == -1){
                    posInimigos[it2.first] = it.second->getId();
                    break;
                }
            }
        }
    }
}

void states::Fases::Fase::salvarFase(){
    FaseSaver salvamento;
    salvamento.salvarEntidades(*listaEntidades.getMapEntidade(), numeroDeFase());
}