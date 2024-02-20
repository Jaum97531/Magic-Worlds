#pragma once
#include "Entidade.hpp"

namespace Entidades{
    class AreaDeEfeito : public Entidade{
        protected:
            Entidade* entidadeDona;
            bool* ativado;
            int dano;
            bool colideObjeto;
            sf::Vector2f impulso;
            int efeito;

        public:
            AreaDeEfeito(Entidade* dona, bool* ativado, int dano, bool colide);
            ~AreaDeEfeito(){}

            bool danosa() { return (dano > 0); }
            void tratarColisao(Objetos::Objeto* obj, std::string dir);
            void tratarColisao(Personagens::Personagem* perso, std::string dir);

            sf::RectangleShape* getArea() {  return &corpo; }
            Entidade* getDono() { return entidadeDona; }

            void setDano(int dan) { dano = dan; }
            const int getDano() const { return dano; }

            void atualizaPosicao(bool direcao);
            bool getColideObjeto() { return colideObjeto; }
            void setColideObjeto(bool colide) { colideObjeto = colide; }

            const Type getType() const { return Type::Area; }
            void setColor(sf::Color cor) { corpo.setFillColor(cor); }
            void setAtivado(bool* pEfeito) { ativado = pEfeito; }
            void setEfeito(int pEfeito) { efeito = pEfeito; }
            const bool getAtivado() const { return *ativado; }
            void setImpulso(sf::Vector2f impulsoo) { impulso = impulsoo; }
    };
}