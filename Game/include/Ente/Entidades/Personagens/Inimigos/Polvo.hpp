#pragma once
#include "Inimigo.hpp"
#include "../Atirador.hpp"

namespace Entidades{
    namespace Personagens{
        class Polvo : public Inimigo, public Classes::Atirador{
            private:
                sf::Vector2f speed;
                sf::Clock clockDash;
                std::vector<float> estagiosDash;
                bool dash;

            public:
                Polvo();
                ~Polvo();

                void move();
                void execute();
                void determinaDirecao();
                void tratarColisaoDaArea(std::string direcao, Type classe);
                void tratarColisao(Jogador* jogador, std::string direcao);
        };
    };
}