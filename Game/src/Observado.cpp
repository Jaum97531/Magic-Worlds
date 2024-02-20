#include "../include/Gerenciadores/Observer/Observador.hpp"
#include "../include/Gerenciadores/Observer/Observado.hpp"

Observado::Observado(){

}

Observado::~Observado(){
    
}

void Observado::addObservador(Observador* ob) {  observadores.push_back(ob); }

void Observado::removerObservador(Observador* ob) {
    auto it = std::remove(observadores.begin(), observadores.end(), ob);
    observadores.erase(it, observadores.end());  
}

void Observado::notificaObservadores(int tipo) {
    for(auto* observador : observadores){  
        observador->notifica(tipo); 
    }
}