#pragma once
#include "Inimigo.hpp"

namespace Entidades{
    namespace Personagens{
        class Zumbi : public Inimigo{
            private:
                static bool CACANDO;

            public: 
                Zumbi();
                ~Zumbi();

                static bool getCacando() { return CACANDO; }
                void execute();
                virtual Type tipoMaisAbstrato() { return Type::Zumbi; }

        };
    };
}