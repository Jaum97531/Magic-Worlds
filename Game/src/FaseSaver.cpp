#include "../include/Ente/FaseSaver.hpp"
#include "../include/Ente/Estados/Fases/Fase1.hpp"
#include <iostream>

FaseSaver::FaseSaver(){
    //CRIA UM MAPA QUE MAPEIA AS FUNCOES DE GERADORES DEPENDENDO DO TIPO RECEBIDO
    geradores[Type::Jogador] = [this](Entidade* ent) {
        return gerarDados(dynamic_cast<Personagens::Jogador*>(ent));
    };

    geradores[Type::Esqueleto] = [this](Entidade* ent) {
        return gerarDados(dynamic_cast<Personagens::Esqueleto*>(ent));
    };

    geradores[Type::Fantasma] = [this](Entidade* ent) {
        return gerarDados(dynamic_cast<Personagens::Fantasma*>(ent));
    };

    geradores[Type::Zumbi] = [this](Entidade* ent) {
        return gerarDados(dynamic_cast<Personagens::Zumbi*>(ent));
    };

    geradores[Type::Caixa] = [this](Entidade* ent) {
        return gerarDados(dynamic_cast<Objetos::Caixa*>(ent));
    };

    geradores[Type::Projetil] = [this](Entidade* ent) {
        return gerarDados(dynamic_cast<Projetil*>(ent));
    };


    //CRIA O MAPA DE CRIADORES
    criadores["Jogador"] = [this](nlohmann::json jogSaver) { return criarJogador(jogSaver); };
    criadores["Esqueleto"] = [this](nlohmann::json esqueletoSaver) { return criarEsqueleto(esqueletoSaver); };
    criadores["Fantasma"] = [this] (nlohmann::json fantasmaSaver) { return criarFantasma(fantasmaSaver); };
    criadores["Zumbi"] = [this](nlohmann::json zumbiSaver) { return criarZumbi(zumbiSaver); };
    criadores["Projetil"] = [this](nlohmann::json projetilSaver) { return criarProjetil(projetilSaver); };
    criadores["Caixa"] = [this](nlohmann::json caixaSaver) { return criarCaixa(caixaSaver); };
    
}

FaseSaver::~FaseSaver(){
    geradores.clear();
    criadores.clear();
}

nlohmann::json FaseSaver::gerarDados(Personagens::Jogador* jogador){
    nlohmann::json dadosJog = {
        {"Classe", "Jogador"},
        {"Elemento", jogador->getElementoo()},
        {"Pontos", jogador->getPontos()},
        {"Nome", jogador->getNome()},
    };
    dadosJog.update(dadosPadraoPersonagens(jogador), true);
    return dadosJog;
}

nlohmann::json FaseSaver::gerarDados(Personagens::Zumbi* zumbi){
    nlohmann::json dadosZumbi = {
        {"Classe", "Zumbi"},
        {"CACANDO", zumbi->getCacando()}
    };
    dadosZumbi.update(dadosPadraoInimigos(zumbi), true);
    return dadosZumbi;
}

nlohmann::json FaseSaver::gerarDados(Personagens::Fantasma* fantasma){
    nlohmann::json dadosFantasma = {
        {"Classe", "Fantasma"},
        {"Invisivel", fantasma->getInvisivel()},
        {"TempoMax", fantasma->getTempoMax()}
    };
    dadosFantasma.update(dadosPadraoInimigos(fantasma), true);
    return dadosFantasma;
}

nlohmann::json FaseSaver::gerarDados(Personagens::Esqueleto* esqueleto){
    nlohmann::json dadosEsq = { {"Classe", "Esqueleto"} };
    dadosEsq.update(dadosPadraoInimigos(esqueleto), true);
    return dadosEsq;
}

nlohmann::json FaseSaver::gerarDados(Projetil* projetil){
    nlohmann::json dadosProjetil = {
        {"Classe", "Projetil"},
        {"Elemento", projetil->getElemento()},
        {"ID EntidadeDona", projetil->getID_Atirador()},
        {"Direcao", projetil->getDirecao()},
        {"Explodindo", projetil->getExplodindo()}
    };
    dadosProjetil.update(dadosPadraoEntidades(projetil), true);
    return dadosProjetil;
}

nlohmann::json FaseSaver::gerarDados(Objetos::Caixa* caixa){
    //EXISTE A CAIXA MAS NAO ESTOU CRIANDO NA FASE INT NEM IMPLEMENTEI
}

nlohmann::json FaseSaver::dadosPadraoEntidades(Entidade* ent){
    nlohmann::json dadosEntidade = {
        {"ProxID", Entidades::Entidade::getProximoID()},
        {"ID", ent->getId()},
        {"Gravidade", ent->getVelocidadeDeQueda()},
        {"Posicao X", ent->getPosition().x},
        {"Posicao Y", ent->getPosition().y},
        {"Ativo", ent->getAtivo()}
    };
    return dadosEntidade;
}

nlohmann::json FaseSaver::dadosPadraoPersonagens(Personagens::Personagem* personagem){
    nlohmann::json dadosPersonagens = {
        {"Vida", personagem->getVida()},
        {"EstadoFisico", personagem->getEstadoFisico()},
        {"Direcao", personagem->getDirecao()}
    };
    dadosPersonagens.update(dadosPadraoEntidades(personagem), true);
    return dadosPersonagens;
}

nlohmann::json FaseSaver::dadosPadraoObjetos(Objetos::Objeto* objeto){
    //NAO ESTOU CRIANDO NENHUM OBJETO QUE PRECISA DE SALVAMENTO NA FASE
}

bool FaseSaver::vazio() { 
    std::ifstream arquivo("faseSalva.json");
    if(arquivo.is_open()){
        bool empty = false;
        if(arquivo.peek() == std::ifstream::traits_type::eof()){ empty = true; }
        arquivo.close();
        return empty;
    }
    return true;
}

nlohmann::json FaseSaver::dadosPadraoInimigos(Personagens::Inimigo* inimigo){
    nlohmann::json dadosInimigo = {
        {"Estado", inimigo->getEstado()},
        {"Vendo", inimigo->getVendo()},
        {"Caminhar", inimigo->getCaminhar()},
        {"Nivel de Maldade", inimigo->getNvlDeMaldade()}
    };
    dadosInimigo.update(dadosPadraoPersonagens(inimigo), true);
    return dadosInimigo;
}

nlohmann::json FaseSaver::determinarQualDadoGerar(Entidade* ent, Type tipo){
    return geradores[tipo](ent);
}

Type FaseSaver::tipoMaisAbstrato(Entidade* ent){
    if(ent->getTipo(Type::Jogador)){ 
        return Type::Jogador; 
    } else if (ent->getTipo(Type::Projetil)) { 
        return Type::Projetil;
    } else if (ent->getTipo(Type::Zumbi)) { 
        return Type::Zumbi; 
    } else if (ent->getTipo(Type::Caixa)) { 
        return Type::Caixa;
    } else if (ent->getTipo(Type::Esqueleto)) { 
        return Type::Esqueleto; 
    } else if (ent->getTipo(Type::Fantasma)) { 
        return Type::Fantasma; 
    }
}

void FaseSaver::salvarEntidades(std::unordered_map<int, Entidade*> mapEntidade, int fase){
    nlohmann::json faseSaver{ {"Fase", fase} };
    dados.push_back(faseSaver);

    for(auto it : mapEntidade){
        if(it.second->getAtivo()){
            Type tipo = tipoMaisAbstrato(it.second);
            auto gerador = geradores.find(tipo);
            
            if (gerador != geradores.end())
                dados.push_back(determinarQualDadoGerar(it.second, tipo));
        }
    }

    std::ofstream arquivo("faseSalva.json");
    if (arquivo.is_open()) {
        // Escrever o JSON no arquivo
        arquivo.clear();
        arquivo << std::setw(4) << dados; // A função std::setw(4) formata a saída com indentação de 4 espaços
        arquivo.close();
    }
}

Personagens::Jogador* FaseSaver::criarJogador(nlohmann::json jogSaver){
    Personagens::Jogador* jogador =  Personagens::Jogador::getInstancia();
    jogador->trocarElemento(jogSaver["Elemento"].get<std::string>());

    criarPersonagem(jogador, jogSaver);
    criarEntidade(jogador, jogSaver);

    jogador->setPontos(jogSaver["Pontos"].get<int>());
    jogador->setNome(jogSaver["Nome"].get<std::string>());
    Entidade::setProxId(jogSaver["ProxID"].get<int>());

    return jogador;
}

Personagens::Zumbi* FaseSaver::criarZumbi(nlohmann::json zumbiSaver){
    Personagens::Zumbi* zumbi = new Personagens::Zumbi();
    zumbi->setCacando(zumbiSaver["CACANDO"].get<bool>());
    criarEntidade(zumbi, zumbiSaver);
    criarPersonagem(zumbi, zumbiSaver);
    criarInimigo(zumbi, zumbiSaver);
    return zumbi;
}

Personagens::Fantasma* FaseSaver::criarFantasma(nlohmann::json fantasmaSaver){
    Personagens::Fantasma* fantasma = new Personagens::Fantasma();
    fantasma->setInvisivel(fantasmaSaver["Invisivel"].get<bool>());
    fantasma->setTempoMax(fantasmaSaver["TempoMax"].get<int>());

    criarEntidade(fantasma, fantasmaSaver);
    criarPersonagem(fantasma, fantasmaSaver);
    criarInimigo(fantasma, fantasmaSaver);

    return fantasma;
}

Personagens::Esqueleto* FaseSaver::criarEsqueleto(nlohmann::json esqueletoSaver){
    Personagens::Esqueleto* esqueleto = new Personagens::Esqueleto();
    criarInimigo(esqueleto, esqueletoSaver);
    criarPersonagem(esqueleto, esqueletoSaver);
    criarEntidade(esqueleto, esqueletoSaver);

    return esqueleto;
}

Objetos::Caixa* FaseSaver::criarCaixa(nlohmann::json caixaSaver){

}

Projetil* FaseSaver::criarProjetil(nlohmann::json projetilSaver){
    Projetil* projetil = new Projetil(projetilSaver["ID EntidadeDona"].get<const int>());
    projetil->setDirecao(projetilSaver["Direcao"].get<bool>());
    projetil->setElemento(sf::String(projetilSaver["Elemento"].get<std::string>()));
    projetil->setExplodindo(projetilSaver["Explodindo"].get<bool>());

    criarEntidade(projetil, projetilSaver);
    return projetil;
}

void FaseSaver::criarPersonagem(Personagens::Personagem* personagem, nlohmann::json persoSaver){
    personagem->setVida(persoSaver["Vida"].get<int>());
    personagem->setDirecao(persoSaver["Direcao"].get<bool>());
    personagem->setEstadoFisico(persoSaver["EstadoFisico"].get<int>());
    mapEntidades[personagem->getArea()->getId()] = (personagem->getArea());
}

void FaseSaver::criarInimigo(Personagens::Inimigo* inimigo, nlohmann::json inimigoSaver){
    inimigo->setVendo(inimigoSaver["Vendo"].get<bool>());
    inimigo->setCaminhar(inimigoSaver["Caminhar"].get<bool>());
    inimigo->setEstado(inimigoSaver["Estado"].get<int>());
    inimigo->setNvlMaldade(inimigoSaver["Nivel de Maldade"].get<int>());
}

void FaseSaver::criarEntidade(Entidade* ent, nlohmann::json entSaver){
    ent->setGravidade(entSaver["Gravidade"].get<float>());
    ent->setPosition(sf::Vector2f(entSaver["Posicao X"].get<float>(), entSaver["Posicao Y"].get<float>()));
    ent->setId(entSaver["ID"].get<int>());
    ent->setAtivo(entSaver["Ativo"].get<bool>());
    mapEntidades[ent->getId()] = ent;
}

Entidade* FaseSaver::criarEntidade(nlohmann::json entSaver){
    std::string classe = entSaver["Classe"].get<std::string>();
    return criadores[classe](entSaver);
}

states::Fases::Fase* FaseSaver::loadEntidades(){
    std::ifstream arquivo("faseSalva.json");
    
    if(arquivo.is_open()){
        nlohmann::json salve;
        arquivo >> salve;

        int fase = 0;
        for(auto it : salve){
            if(!fase) 
                fase = it["Fase"].get<int>(); 
            else {
                Entidade* ent = criarEntidade(it);
            }
        }
        
        switch(fase){
            case FASE1 :
                return new states::Fases::Fase1(mapEntidades);
            case FASE2 :
                break;
        } 
    } else {
        std::cerr<<"Erro ao carregar arquivo"<<std::endl;;
    }

}

