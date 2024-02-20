#pragma once
#include "../Gerenciadores/GerenciadorGrafico.hpp"
#include "../Gerenciadores/GerenciadorEventos.hpp"


class Ente{
    protected:
        GR::GerenciadorGrafico* pGrafico;
        GR::GerenciadorEventos* pEventos;
        bool ativo;
       
    public:
        Ente();
        ~Ente(){}

        void setAtivo(bool at) { ativo = at; }
        bool getAtivo() const { return ativo; }
        GR::GerenciadorEventos* getEventos() { return pEventos; }
        
        virtual void execute() = 0;
        virtual void desenhar() = 0;
};