#pragma once
#include "Menu.hpp"

namespace states{
    class Pausa : public Menu{
    private:
        int faseAtual; 
    public:
        Pausa();
        ~Pausa();

        void iniciarTextos() override;
        void setFase(int idFase) { faseAtual = idFase; }
        const int getFase() const { return faseAtual; }
        void tratarSelecao(sf::String selecao);
        void setAnimacao(int fase);
    };
    
} 
