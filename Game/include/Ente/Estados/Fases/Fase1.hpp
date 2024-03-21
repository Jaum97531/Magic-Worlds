#pragma once
#include "Fase.hpp"

namespace states{
    namespace Fases{
        class Fase1 : public Fase{
            private:

            public:
                Fase1();
                Fase1(std::unordered_map<int, Entidade*> map);
                ~Fase1();

                void criarFase();
                void carregarFase();
                void criaObstaculos();
                void tratarSelecao(sf::String selecao);
                void determinarPosicaoInimigos();
                const int numeroDeFase() { return FASE1; }
        };
    }
}