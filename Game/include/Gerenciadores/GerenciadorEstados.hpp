#pragma once
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

namespace states{
    class Estado;

    namespace Fases{
        class Fase;
    }
}

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
    
    class GerenciadorEstados{
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
            bool tratarTrocaEspecificas(int& estado);
            void setEstador(states::Estado* estado) { }

            void execute();
    };
}