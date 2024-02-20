#pragma once
#include "Menu.hpp"

namespace states{
        class GameOver : public Menu{
            private:
                int ptsJogador;

            public:
                GameOver();
                ~GameOver();

                void iniciarTextos() override;
                void setAnimacao(int fase);
                void setPtsJogador(int pts) { ptsJogador = pts; }
                void iniciarEstado();
                void tratarSelecao(sf::String selecao);
        };
}