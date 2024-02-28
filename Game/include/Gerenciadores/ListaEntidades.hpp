#pragma once 
#include <vector>
#include <map>
#include "../Ente/Entidades/Objetos/Objeto.hpp"
#include "../Ente/Entidades/Personagens/Jogador.hpp"
#include "../Ente/Entidades/Projetil.hpp"
#include "../Ente/Entidades/Personagens/Inimigos/Inimigo.hpp"
#include "GerenciadorColisoes.hpp"

using namespace Entidades;

class ListaEntidades{
    private:
        std::unordered_map<int, Entidade*> mapEntidade;
        std::vector<Entidade*> listaTemporaria;
        GR::GerenciadorColisao* colisor;


    public:
        ListaEntidades();
        ~ListaEntidades();

        void executarEntidades();
        void desenharEntidades();
        void mesclarListaTemporaria();
        void removerInativos();
        void clear();
        void push_back(Entidade* ent);
        Entidade* returnEntidade(int id);
        std::unordered_map<int, Entidade*>* getMapEntidade();
        std::vector<Entidade*>* getListaTemporaria();
        void push_back_temporaria(Entidade* ent);
        void removerEntidade(Entidade* ent);
        void setListaEntidades(std::unordered_map<int ,Entidade*> map){ mapEntidade = map; }
        void operator=(std::unordered_map<int ,Entidade*> map){  mapEntidade = map; }
        void verificaLimites(sf::FloatRect limites);
};