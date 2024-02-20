#pragma once
#include "../Entidade.hpp"

#define NORMAL 0
#define QUEIMANDO 1
#define CONGELADO 2
#define TONTO 3
#define QUEBRADO 4
#define INTANGIVEL 5

namespace Entidades{
    namespace Personagens{
        class Personagem : public Entidade{
            protected:
                bool moveu;
                bool direcao; //esquerda - false, direita - true;
                sf::Vector2f velocidade;
                int vida;

                sf::Clock tempoEstado;
                int estadoFisico;

                int dano;

            public:
                Personagem();
                ~Personagem();

                const int getDano() const { return dano; }
                virtual void move() = 0;
                virtual void execute();
                virtual bool verificaMorte();

                virtual void foraDosLimites() { diminuiVida(); }
                void diminuiVida() { if(vida > 0) vida--; }
                const int getVida() { return vida; }
                void setVida(int hp) { vida = hp; }
                const Type getType() const { return Type::Personagem; }
                bool getDirecao(){ return direcao; }

                virtual void tratarColisao(Projetil* projetil, std::string direcao);
                virtual void tratarColisao(AreaDeEfeito* area, std::string direcao);
                virtual void tratarColisao(Objetos::Objeto* obj, std::string direcao);
                void setEstadoFisico(const int estadoF) { estadoFisico = estadoF; tempoEstado.restart(); }
                void aplicarEstadoFisico();
                const int getEstadoFisico() { return estadoFisico; }
                void setDirecao(bool dir) { direcao = dir; }
                virtual AreaDeEfeito* getArea() = 0;
        };
    };
}