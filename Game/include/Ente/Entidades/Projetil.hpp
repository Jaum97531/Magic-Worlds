#pragma once
#include "Entidade.hpp"
#include "Personagens/Atirador.hpp"
#include "../../Gerenciadores/Animacao.hpp"

namespace Entidades{
    class Projetil : public Entidade{
        private:
            Classes::Atirador* pAtirador;
            int id_atirador;
            sf::Vector2f velocidade;
            sf::Texture textura;
            sf::Clock relogio;
            float tempo;
            int dano;
            sf::String elemento;
            bool direcao;
            Animacao explosao;
            bool explodindo;

        public:
            Projetil(Classes::Atirador* atirador, sf::String elemen, bool _direcao);
            Projetil(int idAtirador);
            ~Projetil();

            void execute();
            void move();
            void verificaFimTempo();
            void setAtirador(Classes::Atirador* a) { pAtirador = a; }

            void setElemento(sf::String ele);
            std::string getElemento();
            const int getDano() const;
            void setDano(int d) { dano = d; }
            void setTextura(sf::Texture texture);
            Entidades::Personagens::Personagem* getAtirador() const;
            void setTempo(float timeMax);
            void setVelocidade(sf::Vector2f veloc);

            bool getDirecao() { return direcao; }
            void setDirecao(bool direction) { direcao = direction; }

            const int getID_Atirador() { return id_atirador; }
            void tratarColisao(Objetos::Objeto* obj, std::string direcao);
            void tratarColisao(Personagens::Personagem* perso, std::string direcao);
            void tratarColisao(Projetil* projetil, std::string direcao);
            
            
            void explodir();
            void configurarCorpoExplosao();
            bool getExplodindo() { return explodindo; }
            void setExplodindo(bool e) { explodindo = e; }
    };
}
