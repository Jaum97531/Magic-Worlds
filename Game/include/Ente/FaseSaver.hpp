#pragma once
#include "nlohmann/json.hpp"
#include "Entidades/Projetil.hpp"
#include "Entidades/Personagens/Jogador.hpp"
#include "Entidades/Personagens/Inimigos/Esqueleto.hpp"
#include "Entidades/Personagens/Inimigos/Fantasma.hpp"
#include "Entidades/Personagens/Inimigos/Zumbi.hpp"
#include "Entidades/Objetos/Lava.hpp"
#include "Entidades/Objetos/Caixa.hpp"
#include "../Gerenciadores/Algoritimos.hpp"
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace Entidades;

namespace states{
    namespace Fases{
        class Fase;
    };
}

class FaseSaver{
    private:
        nlohmann::json dados;
        std::unordered_map<Type, std::function<nlohmann::json(Entidade*)>> geradores;
        std::unordered_map<std::string, std::function<Entidade*(nlohmann::json)>> criadores;

        std::unordered_map<int, Entidade*> mapEntidades;

    public:
        FaseSaver();
        ~FaseSaver();

        nlohmann::json determinarQualDadoGerar(Entidade* ent, Type tipo);
        Type tipoMaisAbstrato(Entidade* ent);

        nlohmann::json gerarDados(Personagens::Jogador* jogogador);
        nlohmann::json gerarDados(Personagens::Zumbi* zumbi);
        nlohmann::json gerarDados(Personagens::Esqueleto* esqueleto);
        nlohmann::json gerarDados(Personagens::Fantasma* fantasma);
        nlohmann::json gerarDados(Projetil* projetil);
        nlohmann::json gerarDados(Objetos::Caixa* caixa);

        nlohmann::json dadosPadraoEntidades(Entidade* ent);
        nlohmann::json dadosPadraoPersonagens(Personagens::Personagem* personagem);
        nlohmann::json dadosPadraoObjetos(Objetos::Objeto* objeto);
        nlohmann::json dadosPadraoInimigos(Personagens::Inimigo* inimigo);

        void salvarEntidades(std::unordered_map<int, Entidade*> mapEntidade, int fase);
        states::Fases::Fase* loadEntidades(); 

        Personagens::Jogador* criarJogador(nlohmann::json jogSaver);
        Personagens::Zumbi* criarZumbi(nlohmann::json zumbiSaver);
        Personagens::Fantasma* criarFantasma(nlohmann::json fantasmaSaver);
        Personagens::Esqueleto* criarEsqueleto(nlohmann::json esqueletoSaver);
        Objetos::Caixa* criarCaixa(nlohmann::json caixaSaver);

        void criarPersonagem(Personagens::Personagem* personagem, nlohmann::json persoSaver);
        void criarInimigo(Personagens::Inimigo* inimigo, nlohmann::json inimigoSaver);
        void criarEntidade(Entidade* ent, nlohmann::json entSaver);
        
        Entidade* criarEntidade(nlohmann::json entSaver);
        Projetil* criarProjetil(nlohmann::json projetilSaver);

        bool vazio();

        

};