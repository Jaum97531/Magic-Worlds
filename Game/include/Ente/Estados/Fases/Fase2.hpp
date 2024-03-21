#pragma once
#include "Fase.hpp"

namespace states{
    namespace Fases{
        class Fase2 : public Fase{
            private:

            public:
                Fase2();
                Fase2(std::unordered_map<int, Entidade*> map);
                ~Fase2();

                void criarFase();
                void carregarFase();
                void criaObstaculos();
                void determinarPosicaoInimigos();
                void tratarSelecao(sf::String selecao);
                const int numeroDeFase() { return FASE2; }
        };
    }
}