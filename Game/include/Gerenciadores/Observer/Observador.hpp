#pragma once
#include <vector>

class Observado;

class Observador{
    protected:
        Observado* observado;

    public:
        Observador(){ observado = nullptr; }
        ~Observador(){ observado = nullptr; }

        virtual void notifica(int tipo) = 0;
        void observar(Observado* observado);
        void pararDeObservar(Observado* observado);
};
