#pragma once
#include "../../../Gerenciadores/GerenciadorAnimacao.hpp"
#include "Atirador.hpp"
#include "../AreaDeEfeito.hpp"
#include "Personagem.hpp"
#include <string>

#define PROJETIL 1
#define GOLPE 2

namespace Entidades{
    namespace Personagens{
        class Jogador : public Classes::Atirador, public Personagem{
            private:
                int estado;
                bool pulo;
                int contPulos;
                bool previusW;

                int magia;
                bool efeito;
                bool pode_mover;

                sf::String elemento;
                std::string nome;
                GR::GerenciadorAnimacao* animacoes;
                int maxVida;
                AreaDeEfeito area;

                int carga;
                int maxPulos;
                int pontos;
                
                Jogador();
                static Jogador* instancia;
            public:

                ~Jogador();
                static Jogador* getInstancia();

                std::string getElementoo();
                void setNome(std::string str) { nome = (str == "")? "SEMNOME" : str; }
                std::string getNome() const { return nome; }
                void aumentarPontos(int pts) { pontos += pts; }

                const sf::Vector2f getVelocidade() const { return velocidade; }
              
                void jump();
                void move();
                void atacar();
                void execute();
                void gerenciarAnimacao();
                void trocarElemento(sf::String element);
                int getMaxVida() { return maxVida; }
                
                void zeraCarga() { carga = 0; }
                int getCarga() const { return carga; }
                int getMagia() const { return magia; }
                bool getEfeito() const { return efeito; }
                void setEfeito(bool e) { efeito = e; }
                const int getEstado() const { return estado; }

                void revive() { ativo = true; vida = maxVida; estadoFisico = NORMAL; pontos = 0; }
                AreaDeEfeito* getArea() { return &area; }

                void tratarColisao(Objetos::Objeto* objeto, std::string direcao);
                const int getPontos() const { return pontos; }
                void setPontos(int pt) { pontos = pt; }
                void setPodeMover(bool pode) { pode_mover = pode; }
        };
    };
}