#pragma once
#include "../Ente/Entidades/Entidade.hpp"
#include "Algoritimos.hpp"
#include <unordered_map>
#include <functional>
using namespace Entidades;

namespace GR{
    
    class GerenciadorColisao{
        private:
            std::unordered_map<std::pair<Type, Type>, std::function<void(Entidade*, Entidade*, sf::FloatRect)>> colisaoMap;
            static GerenciadorColisao* instancia;
            sf::View* view;

            GerenciadorColisao(sf::View* pView);
        public:
            static GerenciadorColisao* getInsatancia(sf::View* pView);

            ~GerenciadorColisao();
            void clear();

            void colideEntidades(Entidade* ent1, Entidade* ent2);
            bool colideRect(sf::FloatRect shape1, sf::FloatRect shape2); 
            bool verificaEntidadeDentroDaTela(Entidade* ent);

            std::pair<std::pair<std::string, std::string>, sf::Vector2f> colisaoPadrao(Entidade* ent1, Entidade* ent2, sf::FloatRect intercesao);
            
            void colisaoPersoPerso(Entidade* perso1, Entidade* perso2, sf::FloatRect intersecao);
            void colisaoPersoObjeto(Entidade* perso, Entidade* obj, sf::FloatRect intercesao);
            void colisaoPersoProjetil(Entidade* perso, Entidade* projetil, sf::FloatRect intercesao);
            void colisaoProjetilProjetil(Entidade* projetil1, Entidade* projetil2, sf::FloatRect intersecao);
            void colisaoObjetoObjeto(Entidade* objeto1, Entidade* objeto2, sf::FloatRect intercesao);
            void colisaoProjetilObjeto(Entidade* projetil, Entidade* objeto, sf::FloatRect intercesao);
            void colisaoAreaPersonagem(Entidade* area, Entidade* personagem, sf::FloatRect intercesao);
            void colisaoAreaProjetil(Entidade* area, Entidade* projetil, sf::FloatRect intercesao);
            void colisaoAreaObjeto(Entidade* area, Entidade* objeto, sf::FloatRect intercesao);
            
            void executeColisoes(std::vector<Entidade*>* listaEntidades);
            void criarColisaoMap();
    };
}