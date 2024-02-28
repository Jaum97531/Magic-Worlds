#include "../include/Gerenciadores/ListaEntidades.hpp"
#include "../include/Gerenciadores/GerenciadorGrafico.hpp"

ListaEntidades::ListaEntidades(){
    colisor = GR::GerenciadorColisao::getInsatancia(GR::GerenciadorGrafico::getInstancia()->getCamera());
}

ListaEntidades::~ListaEntidades(){

}

void ListaEntidades::clear(){
    Personagens::Jogador* jog = Personagens::Jogador::getInstancia();
    for(auto ent : mapEntidade){
        if(ent.second != jog && ent.second != jog->getArea()){ delete ent.second; ent.second = nullptr; }
    }
    for(auto* ent : listaTemporaria){
        if(ent != jog && ent != jog->getArea()){ delete ent;}
    }

    mapEntidade.clear();
    listaTemporaria.clear();

}

void ListaEntidades::push_back(Entidade* ent){
    mapEntidade.insert(std::make_pair(ent->getId(), ent));
}

Entidade* ListaEntidades::returnEntidade(int id){
    return (mapEntidade.find(id) == mapEntidade.end())? nullptr : mapEntidade[id];
}

void ListaEntidades::executarEntidades(){
    for(auto ent : mapEntidade){
        if(ent.second->getAtivo() && (ent.second->getTipo(Type::Projetil) || colisor->verificaEntidadeDentroDaTela(ent.second))){ 
            ent.second->execute();

            if(!ent.second->getEstatico()) { ent.second->acelerarGravidade(); } 
        }
    }
}

std::unordered_map<int, Entidade*>* ListaEntidades::getMapEntidade(){
    return &mapEntidade;
}

std::vector<Entidade*>* ListaEntidades::getListaTemporaria(){
    return &listaTemporaria;
}

void ListaEntidades::push_back_temporaria(Entidade* ent){
    listaTemporaria.push_back(ent);
}

void ListaEntidades::desenharEntidades(){
    Personagens::Jogador* jogador = Personagens::Jogador::getInstancia();
    for(auto ent : mapEntidade){
        if(ent.second->getAtivo() && colisor->verificaEntidadeDentroDaTela(ent.second) && jogador != ent.second){ ent.second->desenhar(); }
    }

    if(jogador->getAtivo() &&  colisor->verificaEntidadeDentroDaTela(jogador)){
        jogador->desenhar();
    }
}
    
void ListaEntidades::mesclarListaTemporaria(){
    for(auto* it : listaTemporaria){
        mapEntidade[it->getId()] = it;
    }
    listaTemporaria.clear();
}

void ListaEntidades::removerInativos(){
    Personagens::Jogador* jog = Personagens::Jogador::getInstancia();
    for(auto ent : mapEntidade){
        if(!ent.second->getAtivo() && ent.second != jog && ent.second != jog->getArea()){
            removerEntidade(ent.second);
        }
    }
}

void ListaEntidades::verificaLimites(sf::FloatRect limites){
    for(auto it : mapEntidade){
        if(it.second->getTipo(Type::Personagem)){
            if(!limites.intersects(it.second->getGlobalBounds())){
                it.second->foraDosLimites();
            }
        }
    }
}

void ListaEntidades::removerEntidade(Entidade* ent){
    if(ent == nullptr){ return; }
    
    if(ent->getTipo(Type::Inimigo)){
        Personagens::Inimigo* inimigo = dynamic_cast<Personagens::Inimigo*>(ent);
        
        mapEntidade.erase(ent->getId());
        mapEntidade.erase(inimigo->getArea()->getId());
    }
    else {
        mapEntidade.erase(ent->getId());
    }

    delete ent; 
    ent = nullptr;
}