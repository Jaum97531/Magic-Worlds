#pragma once
#include "../Estado.hpp"
#include "../../Entidades/Personagens/Jogador.hpp"
#include "../../Entidades/Objetos/Plataforma.hpp"
#include "../../Entidades/Personagens/Inimigos/Inimigo.hpp"
#include "../../FaseSaver.hpp"
#include "../../../Gerenciadores/ListaEntidades.hpp"
#include <vector>
#include <unordered_map>
#include <thread>

// Defina a função hash para Type
namespace std {
    template <>
    struct hash<sf::Vector2f> {
        size_t operator()(const sf::Vector2f& valor) const {
           std::size_t hashX = std::hash<float>{}(valor.x);
            std::size_t hashY = std::hash<float>{}(valor.y);

            // Combinação das hashes usando uma operação XOR
            return hashX ^ (hashY + 0x9e3779b9 + (hashX << 6) + (hashX >> 2));
        }
    };
}


using namespace Entidades;

namespace states{
    namespace Fases{
        class Fase : public Estado{
            protected:
                ListaEntidades listaEntidades;
                Personagens::Jogador* jogador;
                sf::FloatRect limiteDaFase;
                int valorTileMap;
                bool salvo;
                bool aleatoria;
                sf::RectangleShape plataformas;
                sf::Vector2f posJogAntiga;
                GR::GerenciadorAnimacao* gerenAnimacao;

                sf::Clock Cronometro_De_Atualizacao;
                std::unordered_map<sf::Vector2f, int> posInimigos;
                bool forcarAtualizacao;
                sf::Thread* colisionExecute;
                
                Animacao animaCarga;

            public:
                Fase();
                Fase(std::unordered_map<int, Entidade*> map);
                ~Fase();

                void criarMapa(std::string plat, std::string fase);
                void criarPlataforma(sf::Vector2f pos, sf::Vector2f p);
                Personagens::Inimigo* criarZumbi(sf::Vector2f posicao);
                Personagens::Inimigo* criarEsqueleto(sf::Vector2f posicao);
                Personagens::Inimigo* criarFantasma(sf::Vector2f posicao);
                void criarCaixa(sf::Vector2f posicao);
                void criarLava(sf::Vector2f size, sf::Vector2f posicao);
                virtual void criaInimigos();

                virtual void criarFase(){}
                virtual void criaObstaculos(){} 
                virtual void determinarPosicaoInimigos(){}
                virtual void carregarFase(){}
                void setInimigos();
                
                virtual const int numeroDeFase() = 0;

                void atualizarView();
                void atualizarPosicaoDosUtilits();
                void iniciarEstado();

                void criarUtilits();
                void iniciarTextos();
                void atualizarPontos();

                void atualizarVidaJogador();
                
                void desenhar();
                void execute();

                void setJogador(Personagens::Jogador* jog);
                void verificaAtualizacao();
                void salvarFase();
                void tratarSelecao();
                void tratarSelecao(sf::String selecao){ if(selecao == "PROX FASE") { pEstados->trocarEstado(MENSAGEM); } }
                void resized();
        };
    };
}