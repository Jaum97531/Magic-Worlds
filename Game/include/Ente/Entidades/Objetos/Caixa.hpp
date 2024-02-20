#pragma once
#include "Objeto.hpp"

namespace Entidades{
    namespace Objetos{
        class Caixa : public Objeto{
            private:
                friend class EntidadeSaver;

            public:
                Caixa();
                ~Caixa();

                void tratarColisao(Objeto* obj, std::string direcao);
                void execute();
                virtual Type tipoMaisAbstrato() { return Type::Caixa; }
        };
    };
}