#include "../include/Ente/Estados/Menus/Menu.hpp"
#include <cmath>

states::Menu::Menu(){
    mouse.setRadius(5);
    mouse.setPosition(sf::Vector2f(0, 0));
}

states::Menu::~Menu(){

}

void states::Menu::iniciarEstado(){
    observar(pEventos);
    pView->setCenter(sf::Vector2f(pGrafico->get_JANELAX()/2, pGrafico->get_JANELAY()/2));
    pGrafico->getJanela()->setView(*pView);
}

void states::Menu::resized(){

}

void states::Menu::execute(){
    desenhar();
}