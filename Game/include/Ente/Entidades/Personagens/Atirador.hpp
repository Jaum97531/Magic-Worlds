#pragma once
#include "../Entidade.hpp"
#include <vector>

namespace Classes{
    class Atirador {
        protected:
            std::vector<Entidades::Entidade*>* listaEntidades;
            sf::String elementoProjeteis;

        public:
            Atirador();
            ~Atirador();

            void setListaEntidades(std::vector<Entidades::Entidade*>* list) { listaEntidades = list; }
            void criarProjetil(bool direcao, sf::RectangleShape corpo);
            virtual void atirar(bool direcao, sf::RectangleShape corpo);

    };
}