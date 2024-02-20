#include "../include/Ente/Entidades/Projetil.hpp"
#include "../include/Ente/Entidades/Personagens/Personagem.hpp"
#include <locale>
#include <codecvt>

Entidades::Projetil::Projetil(Classes::Atirador* atirador, sf::String element, bool _direcao) : 
id_atirador(dynamic_cast<Entidade*>(atirador)->getId()){
    relogio.restart();
    tempo = 3;
    direcao = _direcao;
    pAtirador = atirador;
    setElemento(element);
}
Entidades::Projetil::~Projetil(){

}

void Entidades::Projetil::verificaFimTempo(){
    if(relogio.getElapsedTime().asSeconds() >= tempo){
        ativo = false;
        pAtirador->removeProjetil(this);
    }
}

void Entidades::Projetil::execute(){
    move();
    verificaFimTempo();
}

void Entidades::Projetil::move(){
    if(direcao)corpo.move(velocidade);
    else corpo.move(-velocidade);
}

void Entidades::Projetil::tratarColisao(Objetos::Objeto* obj, std::string direcao){
    ativo = false;
    if(pAtirador != nullptr) pAtirador->removeProjetil(this);
}

void Entidades::Projetil::tratarColisao(Personagens::Personagem* perso, std::string direcao){
    ativo = false;
    if(pAtirador != nullptr) pAtirador->removeProjetil(this);
}

void Entidades::Projetil::tratarColisao(Projetil* projetil, std::string direcao){
   
}

void Entidades::Projetil::setElemento(sf::String ele) { 
    elemento = ele;
    if(elemento == "FOGO") {
        corpo.setSize(sf::Vector2f(35, 20));
        velocidade = sf::Vector2f(23, 0);
        setTextura(*pGrafico->getPimagens()->getTextura("BOLA DE FOGO"));
        tempo = 2;
        dano = 20;
    }
    else if(elemento == "AGUA"){
        corpo.setSize(sf::Vector2f(35, 20));
        velocidade = sf::Vector2f(20, 0);
        setTextura(*pGrafico->getPimagens()->getTextura("BOLA DE AGUA"));
        tempo = 3;
        dano = 13;
    }
    else if (elemento == "VENTO"){
        corpo.setSize(sf::Vector2f(30, 30));
        velocidade = sf::Vector2f(13, 0);
        setTextura(*pGrafico->getPimagens()->getTextura("FURACAO"));
        tempo = 3;
        dano = 10;
    }
    else if (elemento == "TERRA"){
        corpo.setSize(sf::Vector2f(20, 20));
        velocidade = sf::Vector2f(18, 0);
        setTextura(*pGrafico->getPimagens()->getTextura("PEDRA"));
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

const Type Entidades::Projetil::getType() const { 
    return Type::Projetil; 
}
