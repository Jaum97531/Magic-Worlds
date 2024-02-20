#pragma once
#include "Inimigo.hpp"

namespace Entidades{
    namespace Personagens{
        class Fantasma : public Inimigo{
            private:
                sf::Clock relogioInivisibilidade;
                bool invisivel;
                int tempoMax;

            public:
                Fantasma();
                ~Fantasma();
        
                void move();
                void execute();
                bool getInvisivel() { return invisivel; }
                void setInvisivel(bool invi) { invisivel = invi; }
                int getTempoMax() { return tempoMax; }
                void setTempoMax(int tmp) { tempoMax = tmp; }
                void invisibilidade();
                virtual Type tipoMaisAbstrato() { return Type::Fantasma; }
        };
    };
}