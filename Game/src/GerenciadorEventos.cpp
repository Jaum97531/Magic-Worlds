#include "../include/Gerenciadores/GerenciadorEventos.hpp"

GR::GerenciadorEventos* GR::GerenciadorEventos::instancia = nullptr;

GR::GerenciadorEventos::GerenciadorEventos(){
    pGrafico = GR::GerenciadorGrafico::getInstancia();
    countdownClick.restart();
}
GR::GerenciadorEventos::~GerenciadorEventos(){

}

GR::GerenciadorEventos* GR::GerenciadorEventos::getInstancia(){
    if(instancia == nullptr) 
        instancia = new GerenciadorEventos();

    return instancia;
}

bool GR::GerenciadorEventos::verificaClickMouse(){
    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

bool GR::GerenciadorEventos::verificaClickTecla(sf::Keyboard::Key tecla){
    return sf::Keyboard::isKeyPressed(tecla);
}

void GR::GerenciadorEventos::execute(){
    while (pGrafico->getJanela()->pollEvent(evento)){
        switch (evento.type){
            case sf::Event::Closed :
                pGrafico->fecharJanela();
                break;
            case sf::Event::Resized :
                notificaObservadores(RESIZED);
                break;
            case sf::Event::MouseMoved:
                notificaObservadores(MOUSE);
                break;
            case sf::Event::MouseButtonPressed :
                if(countdownClick.getElapsedTime().asMilliseconds() > 300){
                    notificaObservadores(MOUSE);
                    countdownClick.restart();
                }             
                break;
            case sf::Event::TextEntered :
                notificaObservadores(KEYBOARD);
                break;
        }
    }
}