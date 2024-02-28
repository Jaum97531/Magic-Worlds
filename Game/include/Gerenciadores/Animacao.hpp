#pragma once
#include "GerenciadorImagens.hpp"
#include <vector>
#include <map>
#include <string>

class Animacao{
    private:
        GR::GerenciadorImagens* pTexturas;
        sf::Image imagem;
        std::vector<sf::IntRect> listFrames;
        sf::Texture frame; 
        int frameAtual;
        int numFrames;
        bool temAnimacao;
        sf::Clock controlaTempo;
        bool controla;

    public:
        Animacao();
        ~Animacao();

        void criaFrames(std::string key, int numFrames, bool controlTemp);
        bool anima(sf::RectangleShape* shape, bool direcao, bool forcarAnima);
        bool anima(sf::RectangleShape* shape, bool forcarAnima);
        bool anima(sf::RectangleShape* shape, double frame);
        std::pair<sf::Texture*, sf::IntRect> anima();
        void cortaFrame(int index);
        void atualizaFrameAtual();
        bool TemAnimacao() const { return temAnimacao; }
        void resetaAnimacao();
        int getNumFrames() const { return numFrames; }
        int getFrameAtual() const { return frameAtual; }
        void trocarImagem(std::string key, int resetar);
};