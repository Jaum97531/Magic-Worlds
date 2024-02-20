#pragma once
#include <SFML/Graphics.hpp>
#include "GerenciadorGrafico.hpp"
#include "GerenciadorEstados.hpp"
#include "Observer/Observado.hpp"

namespace GR{
    class GerenciadorEventos : public Observado{
        private:
            GerenciadorGrafico* pGrafico; 
            
            static GerenciadorEventos* instancia;
            sf::Clock countdownClick;

            sf::Event evento;

            GerenciadorEventos();
        public:
            ~GerenciadorEventos();
            static GerenciadorEventos* getInstancia();

            bool verificaClickMouse();
            bool verificaClickTecla(sf::Keyboard::Key tecla);
            void execute();
            sf::Event* getEvento() { return &evento; }
    };
}