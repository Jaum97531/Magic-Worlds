#pragma once
#include "../Personagem.hpp"
#include "../../../../Gerenciadores/Animacao.hpp"
#include "../Jogador.hpp"

#define PERSEGUINDO 1
#define DEBOA 2

namespace Entidades{
    namespace Personagens{
        class Inimigo : public Personagem{
            protected:
                Animacao animaAndando;
                Animacao animaMorrendo;

                sf::Clock cronometroDePerseguicao;

                static Jogador* jogador;
                int estado;

                AreaDeEfeito area;
                bool vendo;
                bool caminhar;

                int nvlMaldade;

            public:
                Inimigo();
                ~Inimigo();
        
                static void setJogador(Jogador* jog) { jogador = jog; }
                virtual void tratarColisaoDaArea(std::string direcao, Type classe);
                AreaDeEfeito* getArea() { return &area; }
                virtual void determinaDirecao();
                virtual void execute();
                virtual void move();
                bool verificaMorte();
                
                int getEstado() { return estado; }
                void setEstado(int state) { estado = state; }
                bool getCaminhar() { return caminhar; }
                void setCaminhar(bool walk) { caminhar = walk; }
                bool getVendo() { return vendo; }
                void setVendo(bool see) { vendo = see; }
                void setNvlMaldade(int nvl) { nvlMaldade = nvl; }
                int getNvlDeMaldade() { return nvlMaldade; }
        };
    };
}