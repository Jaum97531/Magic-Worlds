#include "../include/Ente/Ente.hpp"

Ente::Ente(){
    pGrafico = GR::GerenciadorGrafico::getInstancia();
    pEventos = GR::GerenciadorEventos::getInstancia();
    ativo = true;
}

