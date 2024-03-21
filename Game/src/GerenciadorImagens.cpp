#include "../include/Gerenciadores/GerenciadorImagens.hpp"
#include <iostream>

GR::GerenciadorImagens* GR::GerenciadorImagens::instancia = nullptr;
GR::GerenciadorImagens::GerenciadorImagens(){
    criaTexturas();
}

GR::GerenciadorImagens::~GerenciadorImagens(){
    mapTexturas.clear();
}

GR::GerenciadorImagens* GR::GerenciadorImagens::getInstancia(){
    if(instancia == nullptr){ instancia = new GerenciadorImagens(); }
    return instancia; 
}

void GR::GerenciadorImagens::criaTexturas(){
    setTextura("PERSONAGEM AZUL PARADO", "utilits/imagens/PERSONAGENS/PERSONAGEM AZUL/PERSONAGEM AZUL PARADO.png");
    setTextura("PERSONAGEM AZUL ANDANDO", "utilits/imagens/PERSONAGENS/PERSONAGEM AZUL/PERSONAGEM AZUL ANDANDO.png");
    setTextura("PERSONAGEM AZUL CORRENDO", "utilits/imagens/PERSONAGENS/PERSONAGEM AZUL/PERSONAGEM AZUL CORRENDO.png");
    setTextura("PERSONAGEM AZUL ATACANDO", "utilits/imagens/PERSONAGENS/PERSONAGEM AZUL/PERSONAGEM AZUL ATACANDO.png");
    setTextura("PERSONAGEM AZUL MORRENDO", "utilits/imagens/PERSONAGENS/PERSONAGEM AZUL/PERSONAGEM AZUL MORRENDO.png");

    setTextura("PERSONAGEM VERMELHO PARADO", "utilits/imagens/PERSONAGENS/PERSONAGEM VERMELHO/PERSONAGEM VERMELHO PARADO.png");
    setTextura("PERSONAGEM VERMELHO ANDANDO", "utilits/imagens/PERSONAGENS/PERSONAGEM VERMELHO/PERSONAGEM VERMELHO ANDANDO.png");
    setTextura("PERSONAGEM VERMELHO CORRENDO", "utilits/imagens/PERSONAGENS/PERSONAGEM VERMELHO/PERSONAGEM VERMELHO CORRENDO.png");
    setTextura("PERSONAGEM VERMELHO ATACANDO", "utilits/imagens/PERSONAGENS/PERSONAGEM VERMELHO/PERSONAGEM VERMELHO ATACANDO.png");
    setTextura("PERSONAGEM VERMELHO MORRENDO", "utilits/imagens/PERSONAGENS/PERSONAGEM VERMELHO/PERSONAGEM VERMELHO MORRENDO.png");

    setTextura("PERSONAGEM VERDE PARADO", "utilits/imagens/PERSONAGENS/PERSONAGEM VERDE/PERSONAGEM VERDE PARADO.png");
    setTextura("PERSONAGEM VERDE ANDANDO", "utilits/imagens/PERSONAGENS/PERSONAGEM VERDE/PERSONAGEM VERDE ANDANDO.png");
    setTextura("PERSONAGEM VERDE CORRENDO", "utilits/imagens/PERSONAGENS/PERSONAGEM VERDE/PERSONAGEM VERDE CORRENDO.png");
    setTextura("PERSONAGEM VERDE ATACANDO", "utilits/imagens/PERSONAGENS/PERSONAGEM VERDE/PERSONAGEM VERDE ATACANDO.png");
    setTextura("PERSONAGEM VERDE MORRENDO", "utilits/imagens/PERSONAGENS/PERSONAGEM VERDE/PERSONAGEM VERDE MORRENDO.png");

    setTextura("PERSONAGEM BRANCO PARADO", "utilits/imagens/PERSONAGENS/PERSONAGEM BRANCO/PERSONAGEM BRANCO PARADO.png");
    setTextura("PERSONAGEM BRANCO ANDANDO", "utilits/imagens/PERSONAGENS/PERSONAGEM BRANCO/PERSONAGEM BRANCO ANDANDO.png");
    setTextura("PERSONAGEM BRANCO CORRENDO", "utilits/imagens/PERSONAGENS/PERSONAGEM BRANCO/PERSONAGEM BRANCO CORRENDO.png");
    setTextura("PERSONAGEM BRANCO ATACANDO", "utilits/imagens/PERSONAGENS/PERSONAGEM BRANCO/PERSONAGEM BRANCO ATACANDO.png");
    setTextura("PERSONAGEM BRANCO MORRENDO", "utilits/imagens/PERSONAGENS/PERSONAGEM BRANCO/PERSONAGEM BRANCO MORRENDO.png");

    setTextura("BOLA DE FOGO", "utilits/imagens/EFEITOS/BOLA DE FOGO.png");
    setTextura("BOLA DE AGUA", "utilits/imagens/EFEITOS/BOLA DE AGUA.png");
    setTextura("EXPLOSAO", "utilits/imagens/EFEITOS/EXPLOSAO.png");
    setTextura("METEORO", "utilits/imagens/EFEITOS/METEORO.png");
    setTextura("PEDRA", "utilits/imagens/EFEITOS/PEDRA.png");
    setTextura("FURACAO", "utilits/imagens/EFEITOS/FURACAO.png");
    setTextura("GELO", "utilits/imagens/EFEITOS/GELO.png");
    setTextura("VENTANIA", "utilits/imagens/EFEITOS/VENTANIA.png");

    setTextura("MENU INICIAL", "utilits/imagens/BACKGROUNDS/menu inicial.png");
    setTextura("VULCAO", "utilits/imagens/BACKGROUNDS/vulcao.png");
    setTextura("FASE FOGO PLATAFORMAS", "utilits/imagens/PLATAFORMAS/FASE FOGO PLATAFORMAS.png");
    setTextura("FASE FOGO", "utilits/imagens/PLATAFORMAS/FASE FOGO.png");
    setTextura("FASE LAVA", "utilits/imagens/BACKGROUNDS/lava.png");
    setTextura("LOBBY BG", "utilits/imagens/BACKGROUNDS/lobby bg.png");
    setTextura("CAVERNA", "utilits/imagens/BACKGROUNDS/caverna.png");
    setTextura("LAVA", "utilits/imagens/LAVA.png");
    setTextura("FASE CAVERNA PLATAFORMAS", "utilits/imagens/PLATAFORMAS/FASE CAVERNA PLATAFORMAS.png");
    setTextura("FASE CAVERNA", "utilits/imagens/PLATAFORMAS/FASE CAVERNA.png");
    
    setTextura("CORACAO", "utilits/imagens/CORACAO.png", true);

    setTextura("LOGO FOGO", "utilits/imagens/LOGOS/LOGO FOGO.png");
    setTextura("LOGO AGUA", "utilits/imagens/LOGOS/LOGO AGUA.png");
    setTextura("LOGO VENTO", "utilits/imagens/LOGOS/LOGO VENTO.png");
    setTextura("LOGO TERRA", "utilits/imagens/LOGOS/LOGO TERRA.png");
    setTextura("PLACA", "utilits/imagens/LOGOS/PLACA.png");
    setTextura("PLACA 2", "utilits/imagens/LOGOS/PLACA 2.png");

    setTextura("CORACAO VAZIO", "utilits/imagens/CORACAO VAZIO.png", true);
    setTextura("CAIXA", "utilits/imagens/CAIXA.png");

    setTextura("ESQUELETO ANDANDO", "utilits/imagens/INIMIGOS/ESQUELETO ANDANDO.png");
    setTextura("ESQUELETO MORRENDO", "utilits/imagens/INIMIGOS/ESQUELETO MORRENDO.png");

    setTextura("ZUMBI MORRENDO", "utilits/imagens/INIMIGOS/ZUMBI MORRENDO.png");
    setTextura("ZUMBI ANDANDO", "utilits/imagens/INIMIGOS/ZUMBI ANDANDO.png");

    setTextura("FANTASMA ANDANDO", "utilits/imagens/INIMIGOS/FANTASMA ANDANDO.png");

    setTextura("PORTA FECHADA", "utilits/imagens/PORTA FECHADA.png");
    setTextura("PORTA ABERTA", "utilits/imagens/PORTA ABERTA.png");

    setTextura("PLATAFORMA 1", "utilits/imagens/PLATAFORMA 1.png");

    setTextura("EXPLOSAO FOGO", "utilits/imagens/EFEITOS/EXPLOSAO FOGO.png");
    setTextura("EXPLOSAO AGUA", "utilits/imagens/EFEITOS/EXPLOSAO AGUA.png");
    setTextura("EXPLOSAO TERRA", "utilits/imagens/EFEITOS/EXPLOSAO TERRA.png");
    setTextura("EXPLOSAO VENTO", "utilits/imagens/EFEITOS/EXPLOSAO VENTO.png");

    setTextura("ICON FOGO", "utilits/imagens/LOGOS/ICON FOGO.png");
    setTextura("ICON AGUA", "utilits/imagens/LOGOS/ICON AGUA.png");
    setTextura("ICON TERRA", "utilits/imagens/LOGOS/ICON TERRA.png");
    setTextura("ICON VENTO", "utilits/imagens/LOGOS/ICON VENTO.png");

    setTextura("BARRA FOGO", "utilits/imagens/BARRA FOGO.png");
    setTextura("BARRA VENTO", "utilits/imagens/BARRA VENTO.png");
    setTextura("BARRA AGUA", "utilits/imagens/BARRA AGUA.png");
    setTextura("BARRA TERRA", "utilits/imagens/BARRA TERRA.png");

}

void GR::GerenciadorImagens::setTextura(std::string key, std::string file, bool repeated, bool smooth){
    sf::Texture textura;
    if(textura.loadFromFile(file)){ 
        textura.setRepeated(repeated);
        textura.setSmooth(smooth);
        mapTexturas[key] = textura; 
    }
    else { 
        std::cout<<"Erro ao carregar a Imagen: "<<key<<". Provavelmente o caminho esta errado"<<std::endl;
    }
}

sf::Texture* GR::GerenciadorImagens::getTextura(std::string key){
    auto it = mapTexturas.find(key);  
    if (it != mapTexturas.end()) { return &it->second; } 
    else { 
        std::cerr << "textura não encontrada: " << key << std::endl;
        return nullptr;
    }
}