#include "../include/Ente/Estados/Menus/Rank.hpp"
#include "../include/Gerenciadores/Algoritimos.hpp"

states::Rank::Rank(){
    animacao.criaFrames("LOBBY BG", 6, false);
       
    const int JANELAX = pGrafico->get_JANELAX();
    const int JANELAY = pGrafico->get_JANELAY();

    placa.setSize(sf::Vector2f(800, 900));
    placa.setPosition(sf::Vector2f(JANELAX/2 - placa.getSize().x/2, JANELAY/2 - placa.getSize().y/2));
    placa.setTexture(pGrafico->getPimagens()->getTextura("PLACA"));

    placa2.setSize(sf::Vector2f(1100, 300));
    placa2.setPosition(sf::Vector2f(JANELAX/2 - placa2.getSize().x/2, 0));
    placa2.setTexture(pGrafico->getPimagens()->getTextura("PLACA 2"));
}

states::Rank::~Rank(){

}

void states::Rank::iniciarEstado(){
    textos.clear();
    titulos.clear();
    observar(pEventos);
    iniciarTextos();
}

void states::Rank::tratarSelecao(sf::String selecao){
    if(selecao == "VOLTAR"){ pEstados->trocarEstado(LOBBY); }
}

void states::Rank::desenhar(){
    if(animacao.TemAnimacao()) bool animou = animacao.anima(&background);
    pGrafico->draw(background);
    pGrafico->draw(placa);
    pGrafico->draw(placa2);
    desenharTexto();
}

std::vector<std::pair<std::string, std::string>> states::Rank::organizarPontos(std::vector<std::pair<std::string, std::string>> nome_pontos){
    std::vector<std::pair<std::string, int>> pontos;
    for(auto it : nome_pontos){
        pontos.push_back(std::pair<std::string, int>(it.first, std::stoi(it.second)));
    }

    Algoritimos::quicksort(pontos, 0, pontos.size() - 1);

    std::vector<std::pair<std::string, std::string>> resultado;
    for (const auto &ponto : pontos) {
        resultado.push_back(std::make_pair(ponto.first, std::to_string(ponto.second)));
    }

    return resultado;
}

void states::Rank::completarComPontos(int i){
    for(int k = i; k < 7; k++){
        int posY = pGrafico->get_JANELAY()/2 - 200 + k*75;
        std::string complet("...");
        sf::Text completar = criarTexto(complet , 65, sf::Vector2f(placa.getPosition().x + 80, posY), sf::Color::Black);
        titulos.push_back(completar);
    }
}

void states::Rank::reorganizarArquivoRank(std::vector<std::pair<std::string, std::string>> vetor_nomes_pontos){
    std::ofstream arquivo2("utilits/rank.txt", std::ios::trunc);
    
    for(auto it : vetor_nomes_pontos){
        arquivo2<<it.first<<" "<<it.second<<std::endl;
    }

    arquivo2.close();
}

void states::Rank::abrirArquivo(){
    const int JANELAX = pGrafico->get_JANELAX();
    const int JANELAY = pGrafico->get_JANELAY();

    std::ifstream arquivo("utilits/rank.txt");

    if(!arquivo.is_open()){
        sf::Text mensagemErro = criarTexto("N ABRIU ARQUIVO RANK", 60, sf::Vector2f(pGrafico->get_JANELAX()/2 - 300, pGrafico->get_JANELAY()/2), AZULVERDE);
        titulos.push_back(mensagemErro);
        return;
    }

    std::string linha;
    std::vector<std::pair<std::string, std::string>> vetor_nomes_pontos;
    
    while(std::getline(arquivo, linha)){
        int j = 0;
        while (linha[j] != ' '){ j++; }

        std::pair<std::string, std::string> nome_pontos;
        nome_pontos.first = linha.substr(0, j);
        nome_pontos.second = linha.substr(j+1);

        vetor_nomes_pontos.push_back(nome_pontos);
    }

    arquivo.close();
    
    vetor_nomes_pontos = organizarPontos(vetor_nomes_pontos);

    int i;
    for(i = 0; i < (int)vetor_nomes_pontos.size() && i < 7; i++){
        int posY = JANELAY/2 - 200 + i*75;
        sf::Text nome = criarTexto(vetor_nomes_pontos[i].first, 50, sf::Vector2f(placa.getPosition().x + 80, posY), sf::Color::Black);        
        sf::Text pontos = criarTexto(vetor_nomes_pontos[i].second, 50, sf::Vector2f(placa.getPosition().x + placa.getSize().x - 100 - vetor_nomes_pontos[i].second.length()*25, posY), sf::Color::Black);

        titulos.push_back(nome);
        titulos.push_back(pontos);
    }
    reorganizarArquivoRank(vetor_nomes_pontos);
    completarComPontos(i);
}

void states::Rank::iniciarTextos(){
    const int JANELAX = pGrafico->get_JANELAX();
    const int JANELAY = pGrafico->get_JANELAY();

    sf::Text voltar = criarTexto("VOLTAR", 60, sf::Vector2f(25, JANELAY - 80), AZULVERDE);
    textos.push_back(voltar);

    sf::Text rank = criarTexto("RANK", 120, sf::Vector2f(JANELAX/2-150, 100), sf::Color::Black);
    titulos.push_back(rank);

   abrirArquivo();
}