#include "../include/Gerenciadores/Observer/Observador.hpp"
#include "../include/Gerenciadores/Observer/Observado.hpp"

void Observador::observar(Observado* observado){
    observado->addObservador(this);
}

void Observador::pararDeObservar(Observado* observado){
    observado->removerObservador(this);
}