#pragma once
#include "Objeto.hpp"

namespace Entidades{
    namespace Objetos{
        class Lava : public Objeto{
            private:
                friend class EntidadeSaver;
                sf::RectangleShape shapeAnimacao;

            public:
                Lava();
                ~Lava();

                void execute();
                void desenhar();
                void setSize(sf::Vector2f size);
                void setPosition(sf::Vector2f pos);
                void tratarColisao(Personagens::Personagem* personagem, std::string direcao);
                void queimarPersonagem(Personagens::Personagem* personagem);
                sf::RectangleShape* getShapeAnimacao() { return &shapeAnimacao; }
                virtual Type tipoMaisAbstrato() { return Type::Lava; }
        };
    };
}