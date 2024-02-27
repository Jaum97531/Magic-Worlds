#pragma once
#include "../Estado.hpp"
#include "../../Entidades/Personagens/Jogador.hpp"
#include "../../Entidades/Objetos/Plataforma.hpp"
#include "../../Entidades/Personagens/Inimigos/Inimigo.hpp"
#include "../../Entidades/EntidadeSaver.hpp"
#include <vector>
#include <map>
#include <thread>

using namespace Entidades;

namespace states{
    namespace Fases{
        class Fase : public Estado{
            protected:
                std::vector<Entidade*> listaEntidades;
                Personagens::Jogador* jogador;
                sf::Vector2f limiteDaFase;
                int valorTileMap;
                bool salvo;
                bool aleatoria;
                sf::RectangleShape plataformas;
                sf::Vector2f posJogAntiga;
                GR::GerenciadorAnimacao* gerenAnimacao;

                sf::Clock Cronometro_De_Atualizacao;
                std::map<sf::Vector2f*, Personagens::Inimigo*> posInimigos;
                bool forcarAtualizacao;
                sf::Thread* colisionExecute;

            public:
                Fase();
                ~Fase();

                void criarMapa(std::string plat, std::string fase);
                void criarPlataforma(sf::Vector2f pos, sf::Vector2f p);
                Personagens::Inimigo* criarZumbi(sf::Vector2f posicao);
                Personagens::Inimigo* criarEsqueleto(sf::Vector2f posicao);
                Personagens::Inimigo* criarFantasma(sf::Vector2f posicao);
                void criarCaixa(sf::Vector2f posicao);
                void criarLava(sf::Vector2f size, sf::Vector2f posicao);
                virtual void criaInimigos();

                virtual void criarFase() = 0;
                virtual void criaObstaculos() = 0; 
                virtual void determinarPosicaoInimigos() = 0;
                virtual const int numeroDeFase() = 0;
                void removerEntidade(Entidade* ent);

                void atualizarView();
                bool verificarLimites(Entidade* ent);
                void atualizarPosicaoDosUtilits();
                void iniciarEstado();

                void criarUtilits();
                void atualizarVidaJogador();
                
                void desenharEntidades();
                void executarEntidades();
                void desenhar();
                void execute();

                void setJogador(Personagens::Jogador* jog);
                void verificaAtualizacao();
                void salvarFase();
                void tratarSelecao(sf::String){}
        };
    };
}