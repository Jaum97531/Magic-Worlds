#include "../include/Gerenciadores/Animacao.hpp"
#include <iostream>

Animacao::Animacao(){
    pTexturas = GR::GerenciadorImagens::getInstancia();
    temAnimacao = false;
    frameAtual = 0;
    controlaTempo.restart();
    controla = true;

}

Animacao::~Animacao(){

}

void Animacao::criaFrames(std::string key, int num_frames, bool controlTemp){
    imagem =  pTexturas->getTextura(key)->copyToImage();
    listFrames.clear();

    int x = imagem.getSize().x/num_frames;
    int y = imagem.getSize().y;

    for(int i = 0; i < num_frames; i++){ listFrames.push_back(sf::IntRect(i*x, 0, x, y)); }

    temAnimacao = true;
    numFrames = num_frames; 
    frameAtual = 0;
    controla = controlTemp;
}

bool Animacao::anima(sf::RectangleShape* shape, bool direcao){
    if (!temAnimacao) {
        std::cerr << "Erro: Nenhuma animação criada." << std::endl;
        return false;
    }

    if(!controla || controlaTempo.getElapsedTime().asMilliseconds() >= 70){
        cortaFrame(frameAtual);

        if(!direcao) {
            sf::Image temp = frame.copyToImage();
            temp.flipHorizontally();
            frame.loadFromImage(temp);
        }
        
        sf::IntRect textureRect(0, 0, frame.getSize().x, frame.getSize().y);
        shape->setTexture(&frame);
        shape->setTextureRect(textureRect);
        atualizaFrameAtual();
        controlaTempo.restart();
        return true;
    }
    return false;
}

bool Animacao::anima(sf::RectangleShape* shape){
    if (!temAnimacao) {
        std::cerr << "Erro: Nenhuma animação criada." << std::endl;
        return false;
    }

    if(!controla || controlaTempo.getElapsedTime().asMilliseconds() >= 70){
        cortaFrame(frameAtual);
        sf::IntRect textureRect(0, 0, frame.getSize().x, frame.getSize().y);
        shape->setTexture(&frame);
        shape->setTextureRect(textureRect);
        atualizaFrameAtual();
        controlaTempo.restart();
        return true;
    }
    return false;
}

void Animacao::cortaFrame(int index){
   sf::IntRect rect = listFrames[index];
    frame.loadFromImage(imagem, rect);
    frame.setSmooth(true);
}

std::pair<sf::Texture*, sf::IntRect> Animacao::anima(){
     if (!temAnimacao) {
        std::cerr << "Erro: Nenhuma animação criada." << std::endl;
        return std::make_pair(nullptr, sf::IntRect());
    }

    cortaFrame(frameAtual);
    sf::IntRect textureRect(0, 0, frame.getSize().x, frame.getSize().y);
    std::pair<sf::Texture*, sf::IntRect> par;
    par.first = &frame;
    par.second = textureRect;
    atualizaFrameAtual();
    return par;
}

void Animacao::resetaAnimacao(){
    frameAtual = 0;
}

void Animacao::atualizaFrameAtual(){
    frameAtual = (frameAtual + 1) % numFrames;
}

void Animacao::trocarImagem(std::string key, int resetar){
    if(resetar > 0) { 
        criaFrames(key, resetar, controla);
    }
    else { 
        imagem = pTexturas->getTextura(key)->copyToImage();
        frameAtual = 0;
    }
}