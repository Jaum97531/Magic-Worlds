#pragma once
#include "nlohmann/json.hpp"
#include "Projetil.hpp"
#include "Personagens/Jogador.hpp"
#include "Personagens/Inimigos/Esqueleto.hpp"
#include "Personagens/Inimigos/Fantasma.hpp"
#include "Personagens/Inimigos/Zumbi.hpp"
#include "Objetos/Lava.hpp"
#include "Objetos/Caixa.hpp"
#include "../../Gerenciadores/Algoritimos.hpp"
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace Entidades;

class EntidadeSaver{
    private:
        nlohmann::json dados;
        std::unordered_map<Type, std::function<nlohmann::json(Entidade*)>> geradores;
        std::unordered_map<std::string, std::function<Entidade*(nlohmann::json)>> criadores;

        std::vector<Entidade*> listaEntidades;

        
    public:
        EntidadeSaver();
        ~EntidadeSaver();

        nlohmann::json determinarQualDadoGerar(Entidade* ent);

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

        void salvarEntidades(std::vector<Entidade*> listaEntidades);
        std::vector<Entidade*> loadEntidades(); 

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

};