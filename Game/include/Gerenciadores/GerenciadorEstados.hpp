#pragma once
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "Observer/Observador.hpp"

namespace states{
    class Estado;

    namespace Fases{
        class Fase;
    }
}

#define INICIAL 0
#define LOBBY 1
#define FASE1 2
#define PAUSA 3
#define RANK 4
#define GAMEOVER 5
#define WINS 6
#define NEWGAME 7
#define CONTINUE 8
#define FASE2 9
#define MENSAGEM 10
/*
        Estados: 
    0 - Menu inicial;
    1 - Selecionar Jogadores;
    2 - Selecionar fase;
    3 - Fase 1;
    4 - Fase 2;
    5 - Rank;
    6 - Pausa;
    7 - GameOver;
    8 - Wins;

*/

namespace GR{
    
    class GerenciadorEstados : public Observador{
        private:
            std::map<const int, states::Estado*> mapEstados;
            int estadoAtual;
            static GerenciadorEstados* instancia;
            
            GerenciadorEstados();
             
        public:
            ~GerenciadorEstados();

            static GerenciadorEstados* getInstancia();
            void trocarEstado(int estado);
            void criarEstados();

            states::Estado* getEstadoAtual() { return mapEstados[estadoAtual]; }
            states::Estado* getEstado(int estado) { return mapEstados[estado]; } 
            void notifica(int tipo);
            bool tratarTrocaEspecificas(int& estado);
            void deleteEstado(int estado);

            void execute();
    };
}