#include "../include/Ente/Entidades/EntidadeSaver.hpp"

EntidadeSaver::EntidadeSaver(){
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

    criadores["Jogador"] = [this](nlohmann::json jogSaver) { return criarJogador(jogSaver); };
    criadores["Esqueleto"] = [this](nlohmann::json esqueletoSaver) { return criarEsqueleto(esqueletoSaver); };
    criadores["Fantasma"] = [this] (nlohmann::json fantasmaSaver) { return criarFantasma(fantasmaSaver); };
    criadores["Zumbi"] = [this](nlohmann::json zumbiSaver) { return criarZumbi(zumbiSaver); };
    criadores["Projetil"] = [this](nlohmann::json projetilSaver) { return criarProjetil(projetilSaver); };
    criadores["Caixa"] = [this](nlohmann::json caixaSaver) { return criarCaixa(caixaSaver); };
    
}

EntidadeSaver::~EntidadeSaver(){

}

nlohmann::json EntidadeSaver::gerarDados(Personagens::Jogador* jogador){
    nlohmann::json dadosJog = {
        {"Classe", "Jogador"},
        {"Elemento", jogador->getElementoo()},
        {"Pontos", jogador->getPontos()},
        {"Nome", jogador->getNome()}
    };
    dadosJog.update(dadosPadraoPersonagens(jogador), true);
    return dadosJog;
}

nlohmann::json EntidadeSaver::gerarDados(Personagens::Zumbi* zumbi){
    nlohmann::json dadosZumbi = {
        {"Classe", "Zumbi"},
        {"CACANDO", zumbi->getCacando()}
    };
    dadosZumbi.update(dadosPadraoInimigos(zumbi), true);
    return dadosZumbi;
}

nlohmann::json EntidadeSaver::gerarDados(Personagens::Fantasma* fantasma){
    nlohmann::json dadosFantasma = {
        {"Classe", "Fantasma"},
        {"Invisivel", fantasma->getInvisivel()},
        {"TempoMax", fantasma->getTempoMax()}
    };
    dadosFantasma.update(dadosPadraoInimigos(fantasma), true);
    return dadosFantasma;
}

nlohmann::json EntidadeSaver::gerarDados(Personagens::Esqueleto* esqueleto){
    nlohmann::json dadosEsq = { {"Classe", "Esqueleto"} };
    dadosEsq.update(dadosPadraoInimigos(esqueleto), true);
    return dadosEsq;
}

nlohmann::json EntidadeSaver::gerarDados(Projetil* projetil){
    nlohmann::json dadosProjetil = {
        {"Classse", "Projetil"},
        {"Elemento", projetil->getElemento()},
        {"ID EntidadeDona", projetil->getID_Atirador()},
        {"Direcao", projetil->getDirecao()},
    };
    dadosProjetil.update(dadosPadraoEntidades(projetil), true);
    return dadosProjetil;
}

nlohmann::json EntidadeSaver::gerarDados(Objetos::Caixa* caixa){
    //n preciso por enquanto
}

nlohmann::json EntidadeSaver::dadosPadraoEntidades(Entidade* ent){
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

nlohmann::json EntidadeSaver::dadosPadraoPersonagens(Personagens::Personagem* personagem){
    nlohmann::json dadosPersonagens = {
        {"Vida", personagem->getVida()},
        {"EstadoFisico", personagem->getEstadoFisico()},
        {"Direcao", personagem->getDirecao()}
    };
    dadosPersonagens.update(dadosPadraoEntidades(personagem), true);
    return dadosPersonagens;
}

nlohmann::json EntidadeSaver::dadosPadraoObjetos(Objetos::Objeto* objeto){
 //nao preciso por enquanto
}

nlohmann::json EntidadeSaver::dadosPadraoInimigos(Personagens::Inimigo* inimigo){
    nlohmann::json dadosInimigo = {
        {"Estado", inimigo->getEstado()},
        {"Vendo", inimigo->getVendo()},
        {"Caminhar", inimigo->getCaminhar()},
        {"Nivel de Maldade", inimigo->getNvlDeMaldade()}
    };
    dadosInimigo.update(dadosPadraoPersonagens(inimigo), true);
    return dadosInimigo;
}

nlohmann::json EntidadeSaver::determinarQualDadoGerar(Entidade* ent){
    return geradores[ent->tipoMaisAbstrato()](ent);
}

void EntidadeSaver::salvarEntidades(std::vector<Entidade*> listaEntidades){
    for(auto* it : listaEntidades){
        auto gerador = geradores.find(it->tipoMaisAbstrato());
        if (gerador != geradores.end()) {
            dados.push_back(determinarQualDadoGerar(it));
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

Personagens::Jogador* EntidadeSaver::criarJogador(nlohmann::json jogSaver){
    Personagens::Jogador* jogador =  Personagens::Jogador::getInstancia();
    jogador->trocarElemento(jogSaver["Elemento"].get<std::string>());

    criarPersonagem(jogador, jogSaver);
    criarEntidade(jogador, jogSaver);

    jogador->setPontos(jogSaver["Pontos"].get<int>());
    jogador->setNome(jogSaver["Nome"].get<std::string>());
    Entidade::setProxId(jogSaver["ProxID"].get<int>());

    return jogador;
}

Personagens::Zumbi* EntidadeSaver::criarZumbi(nlohmann::json zumbiSaver){

}

Personagens::Fantasma* EntidadeSaver::criarFantasma(nlohmann::json fantasmaSaver){
    Personagens::Fantasma* fantasma = new Personagens::Fantasma();
    fantasma->setInvisivel(fantasmaSaver["Invisivel"].get<bool>());
    fantasma->setTempoMax(fantasmaSaver["TempoMax"].get<int>());

    criarEntidade(fantasma, fantasmaSaver);
    criarPersonagem(fantasma, fantasmaSaver);
    criarInimigo(fantasma, fantasmaSaver);

    return fantasma;
}

Personagens::Esqueleto* EntidadeSaver::criarEsqueleto(nlohmann::json esqueletoSaver){
    Personagens::Esqueleto* esqueleto = new Personagens::Esqueleto();
    criarInimigo(esqueleto, esqueletoSaver);
    criarPersonagem(esqueleto, esqueletoSaver);
    criarEntidade(esqueleto, esqueletoSaver);

    return esqueleto;
}

Objetos::Caixa* EntidadeSaver::criarCaixa(nlohmann::json caixaSaver){

}

Projetil* EntidadeSaver::criarProjetil(nlohmann::json projetilSaver){
    Projetil* projetil = new Projetil(projetilSaver["ID EntidadeDona"].get<int>());
    projetil->setElemento(std::string(projetilSaver["Elemento"].get<std::string>()));
    projetil->setDirecao(projetilSaver["Direcao"].get<bool>());
    criarEntidade(projetil, projetilSaver);

    return projetil;
}

void EntidadeSaver::criarPersonagem(Personagens::Personagem* personagem, nlohmann::json persoSaver){
    personagem->setVida(persoSaver["Vida"].get<int>());
    personagem->setDirecao(persoSaver["Direcao"].get<bool>());
    personagem->setEstadoFisico(persoSaver["EstadoFisico"].get<int>());
    listaEntidades.push_back(personagem->getArea());
}

void EntidadeSaver::criarInimigo(Personagens::Inimigo* inimigo, nlohmann::json inimigoSaver){
    inimigo->setVendo(inimigoSaver["Vendo"].get<bool>());
    inimigo->setCaminhar(inimigoSaver["Caminhar"].get<bool>());
    inimigo->setEstado(inimigoSaver["Estado"].get<int>());
    inimigo->setNvlMaldade(inimigoSaver["Nivel de Maldade"].get<int>());
}

void EntidadeSaver::criarEntidade(Entidade* ent, nlohmann::json entSaver){
    ent->setGravidade(entSaver["Gravidade"].get<float>());
    ent->setPosition(sf::Vector2f(entSaver["Posicao X"].get<float>(), entSaver["Posicao Y"].get<float>()));
    ent->setId(entSaver["ID"].get<int>());
    ent->setAtivo(entSaver["Ativo"].get<bool>());
}

Entidade* EntidadeSaver::criarEntidade(nlohmann::json entSaver){
    return criadores[entSaver["Classe"].get<std::string>()](entSaver);
}

std::vector<Entidade*> EntidadeSaver::loadEntidades(){
    std::ifstream arquivo("faseSalva.json");
    
    if(arquivo.is_open()){
        nlohmann::json salve;
        arquivo >> salve;
        for(auto it : salve){
            listaEntidades.push_back(criarEntidade(it));
        }
        return listaEntidades;
    }
    else {
        cerr<<"Erro ao carregar arquivo"<<endl;;
    }

}

