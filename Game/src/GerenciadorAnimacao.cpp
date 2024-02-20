#include "../include/Gerenciadores/GerenciadorAnimacao.hpp"
#include "../include/Ente/Entidades/Personagens/Jogador.hpp"

GR::GerenciadorAnimacao* GR::GerenciadorAnimacao::instancia = nullptr;
GR::GerenciadorAnimacao::GerenciadorAnimacao(Entidades::Personagens::Jogador* jog){
    jogador = jog;
    criarAnimacoesJogador();
    contEfeitoJogador = 0;
                        
}

GR::GerenciadorAnimacao::~GerenciadorAnimacao(){

}

GR::GerenciadorAnimacao* GR::GerenciadorAnimacao::getInstacia(Entidades::Personagens::Jogador* jog){
    if(instancia == nullptr){
        instancia = new GerenciadorAnimacao(jog);
    }
    return instancia;
}

void GR::GerenciadorAnimacao::animarEfeitoJogador(){
    animaEfeito.anima(jogador->getArea()->getArea());
}

void GR::GerenciadorAnimacao::morrendo(){

}

void GR::GerenciadorAnimacao::atualizaLavas(){
    std::pair<sf::Texture*, sf::IntRect> textura = animaLavas.anima();
    for(auto it : vetorDeLavas){
        it->setTexture(textura.first);
        it->setTextureRect(textura.second);
    }
}

void GR::GerenciadorAnimacao::trocaAnimacaoJogador(sf::String elemento){
    if(elemento == "AGUA"){
        animaAndando.trocarImagem("PERSONAGEM AZUL ANDANDO", 0);
        animaAtacando.trocarImagem("PERSONAGEM AZUL ATACANDO", 0);
        animaCorrendo.trocarImagem("PERSONAGEM AZUL CORRENDO", 0);
        animaMorrendo.trocarImagem("PERSONAGEM AZUL MORRENDO", 0);
        animaParado.trocarImagem("PERSONAGEM AZUL PARADO", 0);
        animaEfeito.trocarImagem("GELO", 7);
    }
    else if (elemento == "FOGO"){
        animaAndando.trocarImagem("PERSONAGEM VERMELHO ANDANDO", 0);
        animaAtacando.trocarImagem("PERSONAGEM VERMELHO ATACANDO", 0);
        animaCorrendo.trocarImagem("PERSONAGEM VERMELHO CORRENDO", 0);
        animaMorrendo.trocarImagem("PERSONAGEM VERMELHO MORRENDO", 0);
        animaParado.trocarImagem("PERSONAGEM VERMELHO PARADO", 0);
        animaEfeito.trocarImagem("EXPLOSAO", 5);
    }
    else if (elemento == "TERRA"){
        animaAndando.trocarImagem("PERSONAGEM VERDE ANDANDO", 0);
        animaAtacando.trocarImagem("PERSONAGEM VERDE ATACANDO", 0);
        animaCorrendo.trocarImagem("PERSONAGEM VERDE CORRENDO", 0);
        animaMorrendo.trocarImagem("PERSONAGEM VERDE MORRENDO", 0);
        animaParado.trocarImagem("PERSONAGEM VERDE PARADO", 0);
        animaEfeito.trocarImagem("METEORO", 8);
    }
    else if (elemento == "VENTO"){
        animaAndando.trocarImagem("PERSONAGEM BRANCO ANDANDO", 0);
        animaAtacando.trocarImagem("PERSONAGEM BRANCO ATACANDO", 0);
        animaCorrendo.trocarImagem("PERSONAGEM BRANCO CORRENDO", 0);
        animaMorrendo.trocarImagem("PERSONAGEM BRANCO MORRENDO", 0);
        animaParado.trocarImagem("PERSONAGEM BRANCO PARADO", 0);
        animaEfeito.trocarImagem("VENTANIA", 5);
    }  
}

void GR::GerenciadorAnimacao::criarAnimacoesJogador(){
    animaAndando.criaFrames("PERSONAGEM BRANCO ANDANDO", 8, false);
    animaAtacando.criaFrames("PERSONAGEM BRANCO ATACANDO", 24, false);
    animaCorrendo.criaFrames("PERSONAGEM BRANCO CORRENDO", 4, false);
    animaMorrendo.criaFrames("PERSONAGEM BRANCO MORRENDO", 14, true);
    animaParado.criaFrames("PERSONAGEM BRANCO PARADO", 5, false);
    animaEfeito.criaFrames("VENTANIA", 5, true);
}

void GR::GerenciadorAnimacao::resetarAnimacaoJogador(int estado){
    switch(estado){
        case ANDANDO:
            animaAndando.resetaAnimacao();
            break;
        case CORRENDO:
            animaCorrendo.resetaAnimacao();
            break;
        case ATACANDO:
            animaAtacando.resetaAnimacao();
            break;
        case PARADO:
            animaParado.resetaAnimacao();
            break;
    }
}

void GR::GerenciadorAnimacao::criarAnimacaoLava(){
    if(!animaLavas.TemAnimacao()) animaLavas.criaFrames("LAVA", 24, false);
}

void GR::GerenciadorAnimacao::atualizarJogador(int estado){
    bool animou = false;
    switch (estado){
        case ANDANDO:
            if(ultimaAnimacaoJogador != ANDANDO) animaAndando.resetaAnimacao();
            animou = animaAndando.anima(jogador->getShape(), jogador->getDirecao());
            ultimaAnimacaoJogador = ANDANDO;
            break;
        case CORRENDO:
            if(ultimaAnimacaoJogador != CORRENDO) animaCorrendo.resetaAnimacao();
            animou = animaCorrendo.anima(jogador->getShape(), jogador->getDirecao());
            ultimaAnimacaoJogador = CORRENDO;
            break;
        case ATACANDO:
            if(ultimaAnimacaoJogador != ATACANDO) animaAtacando.resetaAnimacao();
            animou = animaAtacando.anima(jogador->getShape(), jogador->getDirecao());
            ultimaAnimacaoJogador = ATACANDO;
            break;
        default:
            if(ultimaAnimacaoJogador != PARADO) animaParado.resetaAnimacao();
            animou = animaParado.anima(jogador->getShape(), jogador->getDirecao());
            ultimaAnimacaoJogador = PARADO;
            break;
    }

    if(jogador->getEfeito()){ 
        animou = animaEfeito.anima(jogador->getArea()->getArea());
        if(animou) contEfeitoJogador++;
        if(contEfeitoJogador == animaEfeito.getNumFrames()){
            contEfeitoJogador = 0;
            jogador->setEfeito(false);
            jogador->zeraCarga();
            animaEfeito.resetaAnimacao();
            animaAtacando.resetaAnimacao();
        }
    }

}