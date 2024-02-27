#pragma once
#include "Fase.hpp"

namespace states{
    namespace Fases{
        class Fase1 : public Fase{
            private:

            public:
                Fase1();
                Fase1(std::vector<Entidade*> vetor);
                ~Fase1();

                void criarFase();
                void carregarFase();
                void criaObstaculos();
                void determinarPosicaoInimigos();
                void setInimigos();
                const int numeroDeFase() { return FASE1; }
        };
    }
}