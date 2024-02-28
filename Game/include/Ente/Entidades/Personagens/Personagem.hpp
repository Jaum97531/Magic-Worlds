#pragma once
#include "../Entidade.hpp"

#define NORMAL 0
#define QUEIMANDO 1
#define CONGELADO 2
#define TONTO 3
#define QUEBRADO 4
#define INTANGIVEL 5
#define ENVENENADO 6

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

                std::unordered_map<int, bool> resistencias;

            public:
                Personagem();
                ~Personagem();

                const int getDano() const { return dano; }
                virtual void move() = 0;
                virtual void execute();
                virtual bool verificaMorte();
                void setFalseResistencias();
                
                virtual void foraDosLimites() { vida = 0; }
                void diminuiVida() { if(vida > 0) vida--; }
                void diminuiVida(int hp) { if(vida > 0) vida -= hp; }

                const int getVida() { return vida; }
                void setVida(int hp) { vida = hp; }
                bool getDirecao(){ return direcao; }

                virtual void tratarColisao(Projetil* projetil, std::string direcao);
                virtual void tratarColisao(AreaDeEfeito* area, std::string direcao);
                virtual void tratarColisao(Objetos::Objeto* obj, std::string direcao);
                void setEstadoFisico(const int estadoF);
                void aplicarEstadoFisico();
                const int getEstadoFisico() { return estadoFisico; }
                void setDirecao(bool dir) { direcao = dir; }
                virtual AreaDeEfeito* getArea() = 0;
                void encerrarEstadoFisico();
        };
    };
}