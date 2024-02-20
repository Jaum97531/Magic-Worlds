#pragma once
#include "Inimigo.hpp"

namespace Entidades{
    namespace Personagens{
        class Esqueleto : public Inimigo{
            private:


            public:
                Esqueleto();
                ~Esqueleto();
                virtual Type tipoMaisAbstrato() { return Type::Esqueleto; }

        };
    };
}