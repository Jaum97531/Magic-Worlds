#pragma once
#include "Entidade.hpp"
#include "Personagens/Atirador.hpp"

namespace Entidades{
    class Projetil : public Entidade{
        private:
            Classes::Atirador* pAtirador;
            const int id_atirador;
            sf::Vector2f velocidade;
            sf::Texture textura;
            sf::Clock relogio;
            float tempo;
            int dano;
            sf::String elemento;
            bool direcao;

        public:
            Projetil(Classes::Atirador* atirador, sf::String elemen, bool _direcao);
            Projetil(int idAtirador) : id_atirador(idAtirador) { pAtirador = nullptr; relogio.restart(); }
            ~Projetil();

            void execute();
            void move();
            void verificaFimTempo();

            void setElemento(sf::String ele);
            std::string getElemento();
            const int getDano() const;
            void setDano(int d) { dano = d; }
            void setTextura(sf::Texture texture);
            Entidades::Personagens::Personagem* getAtirador() const;
            void setTempo(float timeMax);
            void setVelocidade(sf::Vector2f veloc);
            const Type getType() const;
            bool getDirecao() { return direcao; }

            const int getID_Atirador() { return id_atirador; }
            void tratarColisao(Objetos::Objeto* obj, std::string direcao);
            void tratarColisao(Personagens::Personagem* perso, std::string direcao);
            void tratarColisao(Projetil* projetil, std::string direcao);
            virtual Type tipoMaisAbstrato() { return Type::Projetil; }
            void setDirecao(bool direction) { direcao = direction; }
    };
}
