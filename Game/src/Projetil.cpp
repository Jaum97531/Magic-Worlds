#include "../include/Ente/Entidades/Projetil.hpp"
#include "../include/Ente/Entidades/Personagens/Personagem.hpp"
#include <locale>
#include <codecvt>

Entidades::Projetil::Projetil(Classes::Atirador* atirador, sf::String element, bool _direcao) : 
id_atirador(dynamic_cast<Entidade*>(atirador)->getId()){
    relogio.restart();
    tempo = 1;
    direcao = _direcao;
    pAtirador = atirador;
    explodindo = false;
    setElemento(element);
    tipos[Type::Projetil] = true;
    Tipocolision = Type::Projetil;
}


Entidades::Projetil::Projetil(int idAtirador) : id_atirador(idAtirador) { 
    pAtirador = nullptr; 
    relogio.restart(); 
    tipos[Type::Projetil] = true; 
    Tipocolision = Type::Projetil;
}

Entidades::Projetil::~Projetil(){

}

void Entidades::Projetil::configurarCorpoExplosao(){
    if(direcao)
        corpo.setPosition(sf::Vector2f(corpo.getPosition().x - 10, corpo.getPosition().y - 40));
    else 
        corpo.setPosition(sf::Vector2f(corpo.getPosition().x + 10, corpo.getPosition().y - 40));

    corpo.setSize(sf::Vector2f(100, 100));
}

void Entidades::Projetil::verificaFimTempo(){
    if(relogio.getElapsedTime().asSeconds() >= tempo){
        explodindo = true;
        configurarCorpoExplosao();
        explodir();
    }
}

void Entidades::Projetil::explodir(){
    if(explosao.getFrameAtual() >= explosao.getNumFrames() - 1){
        ativo = false;
    }
    bool anima = explosao.anima(&corpo, false);
}

void Entidades::Projetil::execute(){
    if(!explodindo) { move(); verificaFimTempo();}
    else explodir();
}

void Entidades::Projetil::move(){
    if(direcao)corpo.move(velocidade);
    else corpo.move(-velocidade);
}

void Entidades::Projetil::tratarColisao(Objetos::Objeto* obj, std::string direcao){
    if(!explodindo){
        explodindo = true;
        configurarCorpoExplosao();
        explodir();
    }
}

void Entidades::Projetil::tratarColisao(Personagens::Personagem* perso, std::string direcao){
    if(!explodindo){
        explodindo = true;
        configurarCorpoExplosao();
        explodir();
    }
}

void Entidades::Projetil::tratarColisao(Projetil* projetil, std::string direcao){
   
}

void Entidades::Projetil::setElemento(sf::String ele) { 
    elemento = ele;
    if(elemento == "FOGO") {
        corpo.setSize(sf::Vector2f(45, 20));
        velocidade = sf::Vector2f(15, 0);
        setTextura(*pGrafico->getPimagens()->getTextura("BOLA DE FOGO"));
        if(!explosao.TemAnimacao()){ explosao.criaFrames("EXPLOSAO FOGO", 23, false); }
        tempo = 2;
        dano = 20;
    }
    else if(elemento == "AGUA"){
        corpo.setSize(sf::Vector2f(45, 20));
        velocidade = sf::Vector2f(18, 0);
        setTextura(*pGrafico->getPimagens()->getTextura("BOLA DE AGUA"));
        if(!explosao.TemAnimacao()){ explosao.criaFrames("EXPLOSAO AGUA", 23, false); }
        tempo = 2;
        dano = 13;
    }
    else if (elemento == "VENTO"){
        corpo.setSize(sf::Vector2f(30, 30));
        velocidade = sf::Vector2f(13, 0);
        setTextura(*pGrafico->getPimagens()->getTextura("FURACAO"));
        if(!explosao.TemAnimacao()){ explosao.criaFrames("EXPLOSAO VENTO", 23, false); }
        tempo = 3;
        dano = 10;
    }
    else if (elemento == "TERRA"){
        corpo.setSize(sf::Vector2f(20, 20));
        velocidade = sf::Vector2f(18, 0);
        setTextura(*pGrafico->getPimagens()->getTextura("PEDRA"));
        if(!explosao.TemAnimacao()){ explosao.criaFrames("EXPLOSAO TERRA", 23, false); }
        tempo = 2;
        dano = 23;
    }
}

const int Entidades::Projetil::getDano() const { 
    return dano; 
}

void Entidades::Projetil::setTextura(sf::Texture texture) { 
    textura = texture;
    
    if(!direcao){
        sf::Image imagem = textura.copyToImage();
        imagem.flipHorizontally();
        textura.loadFromImage(imagem, sf::IntRect(0, 0,  imagem.getSize().x, imagem.getSize().y));
    }

    corpo.setTexture(&textura);
    corpo.setTextureRect(sf::IntRect(0, 0, textura.getSize().x, textura.getSize().y)); 
}

std::string Entidades::Projetil::getElemento(){
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(elemento.toWideString());
}

Entidades::Personagens::Personagem* Entidades::Projetil::getAtirador() const{
    return dynamic_cast<Entidades::Personagens::Personagem*>(pAtirador); 
}

void Entidades::Projetil::setTempo(float timeMax) {
    tempo = timeMax;
}

void Entidades::Projetil::setVelocidade(sf::Vector2f veloc) { 
    velocidade = veloc; 
}
