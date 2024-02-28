#pragma once
#include "Menu.hpp"

namespace states{
        class GameOver : public Menu{
            private:
                int ptsJogador;
                std::string nome;
                bool salvo;

            public:
                GameOver();
                ~GameOver();

                void iniciarTextos() override;
                void setAnimacao(int fase);
                void iniciarEstado();
                void tratarSelecao(sf::String selecao);
        };
}