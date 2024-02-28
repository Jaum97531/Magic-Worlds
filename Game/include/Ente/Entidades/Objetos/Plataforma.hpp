#pragma once
#include "Objeto.hpp"

#define TIPO1 1
#define TIPO2 2

namespace Entidades{
    namespace Objetos{
        class Plataforma : public Objeto{
            private:
                int tipo;
                static int cor;

            public:
                Plataforma(int type);
                Plataforma(int type, sf::Vector2f size);
                Plataforma();
                ~Plataforma();

                void desenhar();
                void setTipe(int type);
                void atribuirTexture();
                virtual Type tipoMaisAbstrato() { return Type::Plataforma; }
        };
    };
}