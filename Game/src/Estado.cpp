#include "../include/Ente/Estados/Estado.hpp"

states::Estado::Estado() {
    pEstados = GR::GerenciadorEstados::getInstancia();
    pColisao = GR::GerenciadorColisao::getInsatancia(pGrafico->getCamera());

    background.setSize(sf::Vector2f(pGrafico->get_JANELAX(), pGrafico->get_JANELAY()));
    background.setPosition(sf::Vector2f(0, 0));
    
    pView = pGrafico->getCamera();
}
 
states::Estado::~Estado(){

}

sf::Text states::Estado::criarTexto(std::string texto, int size, sf::Vector2f posicao, sf::Color cor=sf::Color::White){
    sf::Text newText(texto, *pGrafico->getFont(), size);
    newText.setPosition(posicao); 
    newText.setFillColor(cor);
    return newText;
}

void states::Estado::desenharTexto(){
    for(auto titulo : titulos){ pGrafico->draw(titulo); }
    for(auto texto : textos){ pGrafico->draw(texto); }
}

void states::Estado::desenharUtilits(){
    for(auto shape : utilits) { pGrafico->draw(shape.second.second); }
}


void states::Estado::selecionar(){
    mouse.setPosition(sf::Vector2f(sf::Mouse::getPosition(*pGrafico->getJanela())));

    for(auto& texto : textos){
        if (pColisao->colideRect(mouse.getGlobalBounds(), texto.getGlobalBounds())){
            texto.setFillColor(CYANOCLARO);
            if (pEventos->verificaClickMouse()) { 
                tratarSelecao(texto.getString());
            }
        } else{
            texto.setFillColor(AZULVERDE);
        }
    }
}


void states::Estado::desenhar(){
    if(animacao.TemAnimacao()) bool animou = animacao.anima(&background);
    pGrafico->draw(background);
    if(!utilits.empty())desenharUtilits();
    desenharTexto();
}

void states::Estado::iniciarEstado(){
    observar(pEventos);
}

void states::Estado::encerrarEstado(){
    pararDeObservar(pEventos);
}

void states::Estado::notifica(int tipo){
    if(tipo == MOUSE) selecionar();
}

sf::RectangleShape states::Estado::criarShapeTextura(std::string textura, sf::Vector2f size, sf::Vector2f posicao, bool repeated) {
    sf::RectangleShape shape(size);
    shape.setPosition(posicao);

    sf::Texture* texture = pGrafico->getPimagens()->getTextura(textura);
    if (texture) {
        shape.setTexture(texture);

        if(repeated){
            texture->setRepeated(true);
            shape.setTextureRect(sf::IntRect(0, 0, size.x, texture->getSize().y));
        }
    }

    return shape;
}