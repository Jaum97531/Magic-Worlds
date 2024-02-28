#pragma once
#include "../Entidade.hpp"

namespace Entidades{
    namespace Objetos{
        class Objeto : public Entidade{
            protected:
                bool especial;

            public:
                Objeto();
                ~Objeto();

                bool getEspecial() const;
                virtual void execute();
                const Type getType() const;
        };
    };
}