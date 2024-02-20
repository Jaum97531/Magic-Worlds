#pragma once
#include "Objeto.hpp"
#include "../../Estados/Fases/Fase.hpp"

namespace Entidades{
    namespace Objetos{
        class Porta : public Objeto{
            private:
                friend class EntidadeSaver;
                states::Fases::Fase* pFase;

            public:
                Porta(states::Fases::Fase* fase);
                ~Porta();

                void execute();
                void tratarColisao(Personagens::Personagem* perso, std::string direcao);
                virtual Type tipoMaisAbstrato() { return Type::Porta; }
        };
    };
}