#pragma once
#include "Gerenciadores/GerenciadorEstados.hpp"
#include "Gerenciadores/GerenciadorEventos.hpp"
#include "Gerenciadores/GerenciadorGrafico.hpp"
#include "Gerenciadores/GerenciadorImagens.hpp"

class Game{
private:
    GR::GerenciadorEstados* pEstados;
    GR::GerenciadorGrafico* pGrafico;
    GR::GerenciadorEventos* pEventos;
    GR::GerenciadorImagens* pImagens;

public:
    Game();
    ~Game();

    void execute();
};