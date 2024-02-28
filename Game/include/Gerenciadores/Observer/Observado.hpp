#pragma once
#include <vector>
#include <algorithm>

class Observador;

#define KEYBOARD 1
#define MOUSE 2
#define RESIZED 3


class Observado{
    protected:
        std::vector<Observador*> observadores;

    public:
        Observado();
        ~Observado();

        void addObservador(Observador* ob);
        void removerObservador(Observador* ob);
        void notificaObservadores(int tipo);
};
