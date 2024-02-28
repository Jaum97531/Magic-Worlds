#include "../include/Ente/Entidades/Personagens/Jogador.hpp"
#include <locale>
#include <codecvt>

Entidades::Personagens::Jogador* Entidades::Personagens::Jogador::instancia = nullptr;
Entidades::Personagens::Jogador::Jogador() : animacoes(GR::GerenciadorAnimacao::getInstacia(this)), estado(PARADO),
carga(0), magia(0), efeito(false), pulo(false), contPulos(0), previusW(false), area(this, &efeito, 0, true), maxPulos(2),
pontos(0), pode_mover(true)
{   
    velocidade = sf::Vector2f(8, 0);
    tipos[Type::Jogador] = true;
    corpo.setSize(sf::Vector2f(70, 70));
    trocarElemento("VENTO");
}

Entidades::Personagens::Jogador* Entidades::Personagens::Jogador::getInstancia(){
    if(instancia == nullptr) { instancia = new Jogador(); }
    return instancia;
}

Entidades::Personagens::Jogador::~Jogador(){

}

void Entidades::Personagens::Jogador::jump(){
    movimento.y -= velocidade.y;
    movimento.y += gravidade;
}

void Entidades::Personagens::Jogador::move(){
    
    if(estado != ATACANDO && pode_mover){
        if(pEventos->verificaClickTecla(sf::Keyboard::D)){
            movimento.x += velocidade.x;
            estado = ANDANDO;
            direcao = true;

            if(pEventos->verificaClickTecla(sf::Keyboard::LShift)){
                movimento.x += velocidade.x;
                estado = CORRENDO;
            }
        }
        else if(pEventos->verificaClickTecla(sf::Keyboard::A)){
            movimento.x -= velocidade.x;
            estado = ANDANDO;
            direcao = false;
            if(pEventos->verificaClickTecla(sf::Keyboard::LShift)){
                movimento.x -= velocidade.x;
                estado = CORRENDO;
            }
        }
    }

    bool w = pEventos->verificaClickTecla(sf::Keyboard::W); 
    if(w && !previusW && pode_mover){
        if(!pulo && contPulos < maxPulos){
            pulo = true;
            contPulos++;
            velocidade.y = 26;
            gravidade = 0;
        }
        else if(contPulos < maxPulos){
            contPulos++;
            gravidade = 0;       
        }
    }

    previusW = w;
    
    if(pulo){ jump(); }
    else{ movimento.y += gravidade; }

}

void Entidades::Personagens::Jogador::trocarElemento(sf::String element) { 
    int n;

    animacoes->trocaAnimacaoJogador(element); 
    elemento = elementoProjeteis = element;
    setFalseResistencias();

    if(elemento == "VENTO"){
        velocidade.x = 10;
        maxPulos = 3;
        vida = maxVida = 6;

        area.setDano(3);
        area.setImpulso(sf::Vector2f(20, -5));
        area.setEfeito(NORMAL);
        area.setSize(sf::Vector2f(150, 150));
    }
    else if(elemento == "FOGO"){
        velocidade.x = 8;
        resistencias[QUEIMANDO] = true;
        maxPulos = 2;
        vida = maxVida = 6;
        area.setDano(10);
        area.setImpulso(sf::Vector2f(10, -3));
        area.setEfeito(QUEIMANDO);
        area.setSize(sf::Vector2f(100, 100));
    }
    else if(elemento == "AGUA"){
        resistencias[CONGELADO] = true;
        velocidade.x = 8;
        maxPulos = 2;
        vida = maxVida = 7;
        area.setDano(3);
        area.setImpulso(sf::Vector2f(3, -3));
        area.setEfeito(CONGELADO);
        area.setSize(sf::Vector2f(100, 100));
    }
    else if(elemento == "TERRA"){
        resistencias[QUEIMANDO] = true;
        velocidade.x = 6;
        maxPulos = 2;
        vida = maxVida = 8;
        area.setDano(3);
        area.setImpulso(sf::Vector2f(20, 0));
        area.setEfeito(NORMAL);
        area.setSize(sf::Vector2f(100, 110));
    }

}

void Entidades::Personagens::Jogador::atacar(){
    if(pEventos->verificaClickTecla(sf::Keyboard::Space)){
        estado = ATACANDO;
        carga++;
        magia = GOLPE;
        if(carga == 13) { efeito = true; }
    }
    else if(pEventos->verificaClickTecla(sf::Keyboard::H)){
        estado = ATACANDO;
        carga++;
        magia = PROJETIL;
        if(carga == 13) { 
            int n;
            atirar(direcao, corpo);
            animacoes->resetarAnimacaoJogador(ATACANDO); 
            carga = 0;
        }
    }
    else{
        carga = 0;
    }
}

std::string Entidades::Personagens::Jogador::getElementoo(){
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(elemento.toWideString());
}

void Entidades::Personagens::Jogador::gerenciarAnimacao(){
    if(efeito){ area.setColor(sf::Color::White); }
    else{
        area.atualizaPosicao(direcao);
        area.setColor(sf::Color::Transparent);
    }

    animacoes->atualizarJogador(estado);
}


void Entidades::Personagens::Jogador::tratarColisao(Objetos::Objeto* objeto, std::string direcao){
    if(direcao == "BAIXO"){
        gravidade = 0;
        pulo = false;
        contPulos = 0;
    }
    else if(direcao == "CIMA"){
        pulo = false;
    }
}

void Entidades::Personagens::Jogador::execute(){
    estado = PARADO;
    aplicarEstadoFisico();
    move();
    atacar();
    gerenciarAnimacao();
    corpo.move(movimento);
    movimento = sf::Vector2f(0, 0);
    posAntigaColision = corpo.getPosition();
}