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
                static void setCacando(bool hunter) { CACANDO = hunter; }
                void execute();

        };
    };
}