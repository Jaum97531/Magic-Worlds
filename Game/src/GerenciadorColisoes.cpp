#include "../include/Gerenciadores/GerenciadorColisoes.hpp"
#include <iostream>
#include "../include/Ente/Entidades/Projetil.hpp"
#include "../include/Ente/Entidades/Personagens/Jogador.hpp"
#include "../include/Ente/Entidades/Objetos/Objeto.hpp"
#include "../include/Ente/Entidades/AreaDeEfeito.hpp"
#include "../include/Gerenciadores/GerenciadorGrafico.hpp"
#include "GerenciadorColisoes.hpp"

GR::GerenciadorColisao* GR::GerenciadorColisao::instancia = nullptr;
GR::GerenciadorColisao::GerenciadorColisao(sf::View* pView){
    criarColisaoMap();
    view = pView;
}
            
GR::GerenciadorColisao::~GerenciadorColisao(){
    clear();
}

GR::GerenciadorColisao* GR::GerenciadorColisao::getInsatancia(sf::View* pView){
    if(instancia == NULL) instancia = new GerenciadorColisao(pView);
    return instancia;
}

void GR::GerenciadorColisao::criarColisaoMap(){
    colisaoMap[{Type::Personagem, Type::Personagem}] = [this](Entidade* perso1, Entidade* perso2, sf::FloatRect intersecao) {
        this->colisaoPersoPerso(perso1, perso2, intersecao);
    };

    colisaoMap[{Type::Personagem, Type::Objeto}] = [this](Entidade* perso, Entidade* obj, sf::FloatRect intersecao){
        this->colisaoPersoObjeto(perso, obj, intersecao);
    };

    colisaoMap[{Type::Objeto, Type::Personagem}] = [this](Entidade* obj, Entidade* perso, sf::FloatRect intersecao){
        this->colisaoPersoObjeto(perso, obj, intersecao);
    };

    colisaoMap[{Type::Objeto, Type::Objeto}] = [this](Entidade* obj1, Entidade* obj2, sf::FloatRect intersecao){
        this->colisaoObjetoObjeto(obj1, obj2, intersecao);
    };

    colisaoMap[{Type::Personagem, Type::Projetil}] = [this](Entidade* perso, Entidade* projetil, sf::FloatRect intersecao){
        this->colisaoPersoProjetil(perso, projetil, intersecao);
    };

    colisaoMap[{Type::Projetil, Type::Personagem}] = [this](Entidade* projetil, Entidade* perso, sf::FloatRect intersecao){
        this->colisaoPersoProjetil(perso, projetil, intersecao);
    };

    colisaoMap[{Type::Projetil, Type::Projetil}] = [this](Entidade* projetil1, Entidade* projetil2, sf::FloatRect intersecao){
        this->colisaoProjetilProjetil(projetil1, projetil2, intersecao);
    };

    colisaoMap[{Type::Projetil, Type::Objeto}] = [this](Entidade* projetil, Entidade* objeto, sf::FloatRect intersecao){
        this->colisaoProjetilObjeto(projetil, objeto, intersecao);
    };

    colisaoMap[{Type::Objeto, Type::Projetil}] = [this](Entidade* objeto, Entidade* projetil, sf::FloatRect intersecao){
        this->colisaoProjetilObjeto(projetil, objeto, intersecao);
    };

    colisaoMap[{Type::Area, Type::Personagem}] = [this](Entidade* area, Entidade* personagem, sf::FloatRect intersecao){
        this->colisaoAreaPersonagem(area, personagem, intersecao);
    };

    colisaoMap[{Type::Personagem, Type::Area}] = [this](Entidade* personagem, Entidade* area, sf::FloatRect intersecao){
        this->colisaoAreaPersonagem(area, personagem, intersecao);
    };

    colisaoMap[{Type::Area, Type::Projetil}] = [this](Entidade* area, Entidade* projetil, sf::FloatRect intersecao){
        this->colisaoAreaProjetil(area, projetil, intersecao);
    };

    colisaoMap[{Type::Projetil, Type::Area}] = [this](Entidade* projetil, Entidade* area, sf::FloatRect intersecao){
        this->colisaoAreaProjetil(area, projetil, intersecao);
    };

    colisaoMap[{Type::Area, Type::Objeto}] = [this](Entidade* area, Entidade* objeto, sf::FloatRect intersecao){
        this->colisaoAreaObjeto(area, objeto, intersecao);
    };

    colisaoMap[{Type::Objeto, Type::Area}] = [this](Entidade* objeto, Entidade* area, sf::FloatRect intersecao){
        this->colisaoAreaObjeto(area, objeto, intersecao);
    };
}

void GR::GerenciadorColisao::clear(){
    colisaoMap.clear();
}

void GR::GerenciadorColisao::colideEntidades(Entidade* ent1, Entidade* ent2){
    sf::FloatRect rect1 = ent1->getShape()->getGlobalBounds();
    sf::FloatRect rect2 = ent2->getShape()->getGlobalBounds();
    sf::FloatRect intersecao;

    if (rect1.intersects(rect2, intersecao)){
        std::pair<Type, Type> key = std::pair<Type, Type>(ent1->getTipoColision(), ent2->getTipoColision());

        if(colisaoMap.count(key) > 0){
            auto colisaoFuncao = colisaoMap[key];
            colisaoFuncao(ent1, ent2, intersecao);
        }
    }
}


void GR::GerenciadorColisao::colisaoAreaObjeto(Entidade* area, Entidade* objeto, sf::FloatRect intercesao){
    AreaDeEfeito* pArea = static_cast<AreaDeEfeito*>(area);
    if(pArea->getColideObjeto() && pArea->getAtivado()){
        Objetos::Objeto* obj = static_cast<Objetos::Objeto*>(objeto);

        std::pair<std::pair<std::string, std::string>, sf::Vector2f> output = colisaoPadrao(pArea, objeto, intercesao);
        std::string direcao = output.first.first;

        pArea->tratarColisao(obj, direcao);
    }
}


std::pair<std::pair<std::string, std::string>, sf::Vector2f> GR::GerenciadorColisao::colisaoPadrao(Entidade* ent1, Entidade* ent2, sf::FloatRect intersecao){
    sf::Vector2f deslocamento(0, 0);
    sf::Vector2f pos1 = ent1->getShape()->getPosition();
    sf::Vector2f pos2 = ent2->getShape()->getPosition();
    std::string direcao1 = "";
    std::string direcao2 = "";

    if (intersecao.width < intersecao.height) {
        if (pos1.x < pos2.x) { 
            deslocamento.x = -intersecao.width; 
            direcao1 = "DIREITA";
            direcao2 = "ESQUERDA";
        } 
        else { 
            deslocamento.x = intersecao.width; 
            direcao1 = "ESQUERDA";
            direcao2 = "DIREITA";
        }
    } 
    else {
        if (pos1.y < pos2.y) { 
            deslocamento.y = -intersecao.height; 
            direcao1 = "BAIXO";
            direcao2 = "CIMA";
        } 
        else { 
            deslocamento.y = intersecao.height; 
            direcao1 = "CIMA";
            direcao2 = "BAIXO";
        }
    }

    std::pair<std::string, std::string> direcoes;
    direcoes.first = direcao1;
    direcoes.second = direcao2;
    
    std::pair<std::pair<std::string, std::string>, sf::Vector2f> output;
    output.first = direcoes;
    output.second = deslocamento;
    return output;

}


void GR::GerenciadorColisao::colisaoProjetilObjeto(Entidade* projetil, Entidade* objeto, sf::FloatRect intersecao){
    Projetil* proje = static_cast<Projetil*>(projetil);
    Objetos::Objeto* obj = static_cast<Objetos::Objeto*>(objeto);

    if(!proje->getExplodindo()){
        proje->tratarColisao(obj, "");
        obj->tratarColisao(proje, "");
    }
}


void GR::GerenciadorColisao::colisaoAreaPersonagem(Entidade* area, Entidade* perso, sf::FloatRect intersecao){
    AreaDeEfeito* pArea = static_cast<AreaDeEfeito*>(area);
    
    if(pArea->getDono() != perso && pArea->getAtivado()){
        Personagens::Personagem* personagem = static_cast<Personagens::Personagem*>(perso);
        std::pair<std::pair<std::string, std::string>, sf::Vector2f> output = colisaoPadrao(perso, area, intersecao);
        std::string dirArea = output.first.second;
        std::string dirPersogem = output.first.first;

        area->tratarColisao(personagem, dirArea); 
        personagem->tratarColisao(pArea, dirPersogem);   
    }
}


void GR::GerenciadorColisao::colisaoAreaProjetil(Entidade* area, Entidade* personagem, sf::FloatRect intersecao){
    
}


void GR::GerenciadorColisao::colisaoPersoProjetil(Entidade* perso, Entidade* proje, sf::FloatRect intersecao){
    Personagens::Personagem* personagem = static_cast<Personagens::Personagem*>(perso);
    Projetil* projetil = static_cast<Projetil*>(proje);

    if(personagem->getId() != projetil->getID_Atirador() && personagem->getEstadoFisico() != INTANGIVEL && !projetil->getExplodindo()){
        std::pair<std::pair<std::string, std::string>, sf::Vector2f> output = colisaoPadrao(perso, projetil, intersecao);
        std::string dirPerso = output.first.first;
        std::string dirProje = output.first.second;
        sf::Vector2f deslocamento = output.second;

        personagem->tratarColisao(projetil, dirPerso);
        projetil->tratarColisao(personagem, dirProje);
        personagem->getShape()->move(sf::Vector2f(deslocamento.x, 0));
    }
}

void GR::GerenciadorColisao::colisaoProjetilProjetil(Entidade* projetil1, Entidade* projetil2, sf::FloatRect intersecao){
    Projetil* projetil_1 = static_cast<Projetil*>(projetil1);
    Projetil* projetil_2 = static_cast<Projetil*>(projetil2);

    projetil_1->tratarColisao(projetil_2, "");
}

void GR::GerenciadorColisao::colisaoObjetoObjeto(Entidade* obj1, Entidade* obj2, sf::FloatRect intersecao){
    bool ob1Estatico = obj1->getEstatico();
    bool ob2Estatico = obj2->getEstatico();
    
    if(ob1Estatico && ob2Estatico){ return; }

    std::pair<std::pair<std::string, std::string>, sf::Vector2f> output = colisaoPadrao(obj1, obj2, intersecao);

    std::string direcao1 = output.first.first;
    std::string direcao2 = output.first.second;
    sf::Vector2f deslocamento = output.second;

    if(!ob1Estatico && !ob2Estatico){ 
        Objetos::Objeto* pObjeto2 = static_cast<Objetos::Objeto*>(obj2);
        Objetos::Objeto* pObjeto1 = static_cast<Objetos::Objeto*>(obj1);
        
        pObjeto1->tratarColisao(pObjeto2, direcao1);
        pObjeto2->tratarColisao(pObjeto1, direcao2);

        if(direcao1 == "BAIXO"){ obj1->deslocar(deslocamento); }
        else if(direcao2 == "BAIXO") { obj2->deslocar(deslocamento); }
        else {
            obj1->deslocar(sf::Vector2f(deslocamento.x/2, 0));
            obj2->deslocar(sf::Vector2f(-deslocamento.x/2, 0));
        }
    }
    else if(!ob1Estatico){ 
        Objetos::Objeto* pObjeto2 = static_cast<Objetos::Objeto*>(obj2); 
        obj1->deslocar(deslocamento); 
        obj1->tratarColisao(pObjeto2, direcao1);
    }
    else { 
        Objetos::Objeto* pObjeto1 = static_cast<Objetos::Objeto*>(obj1);
        obj2->deslocar(-deslocamento); 
        obj2->tratarColisao(pObjeto1, direcao2);
    }
}

void GR::GerenciadorColisao::colisaoPersoPerso(Entidade* perso1, Entidade* perso2, sf::FloatRect intersecao){
   
    std::pair<std::pair<std::string, std::string>, sf::Vector2f> output = colisaoPadrao(perso1, perso2, intersecao);
    std::string direcaoP1 = output.first.first;
    std::string direcaoP2 = output.first.second;
    sf::Vector2f deslocamento = output.second;

    if(perso1->getTipo(Type::Jogador) || perso2->getTipo(Type::Jogador)){
        perso1->deslocar(sf::Vector2f(deslocamento.x/2, 0));
        perso2->deslocar(sf::Vector2f(-deslocamento.x/2, 0));
    }


    if(perso1->getTipo(Type::Jogador)){
        perso1->tratarColisao(static_cast<Personagens::Personagem*>(perso2), direcaoP1);
        perso2->tratarColisao(dynamic_cast<Personagens::Jogador*>(perso1), direcaoP2);
    }
    else if(perso2->getTipo(Type::Jogador)){
        perso1->tratarColisao(static_cast<Personagens::Jogador*>(perso2), direcaoP1);
        perso2->tratarColisao(dynamic_cast<Personagens::Personagem*>(perso1), direcaoP2);
    }
    else {
        perso1->tratarColisao(static_cast<Personagens::Personagem*>(perso2), direcaoP1);
        perso2->tratarColisao(static_cast<Personagens::Personagem*>(perso1), direcaoP2);
    }

}

void GR::GerenciadorColisao::colisaoPersoObjeto(Entidade* perso, Entidade* obj, sf::FloatRect intersecao){
   Personagens::Personagem* personagem = static_cast<Personagens::Personagem*>(perso);
   Objetos::Objeto* objeto = static_cast<Objetos::Objeto*>(obj);
   
    std::pair<std::pair<std::string, std::string>, sf::Vector2f> output = colisaoPadrao(perso, obj, intersecao);

    std::string direcaoP = output.first.first;
    std::string direcaoO = output.first.second;
    sf::Vector2f deslocamento = output.second;

    if(personagem->getTipo(Type::Jogador) && objeto->getTipo(Type::Caixa)){
        personagem->deslocar(sf::Vector2f(deslocamento.x/2, deslocamento.y));
        objeto->deslocar(sf::Vector2f(-deslocamento.x/2, 0));   
    }
    else if(objeto->getTipo(Type::Porta)){
        objeto->tratarColisao(personagem, direcaoO);
        return;
    }
    else{
        if(personagem->getVelocidadeDeQueda() > objeto->getSize().y/2 && (direcaoO == "BAIXO" || direcaoO == "CIMA")){
            if(personagem->getPosAntiga().y < objeto->getPosition().y)
                personagem->setPosition(sf::Vector2f(personagem->getPosition().x, objeto->getPosition().y - personagem->getSize().y));
            else {
                personagem->setPosition(sf::Vector2f(personagem->getPosition().x, objeto->getPosition().y + personagem->getSize().y));
            }
        }else{
            personagem->deslocar(deslocamento);
        }
    }

    personagem->tratarColisao(objeto, direcaoP);
    objeto->tratarColisao(personagem, direcaoO);
}

bool GR::GerenciadorColisao::colideRect(sf::FloatRect shape1, sf::FloatRect shape2){
    return shape1.intersects(shape2);
} 


bool GR::GerenciadorColisao::verificaEntidadeDentroDaTela(Entidade* ent){
    sf::Vector2f posCentro = view->getCenter();
    sf::FloatRect rect = sf::FloatRect(posCentro.x - GerenciadorGrafico::getInstancia()->get_JANELAX()/2 - 100,
                                        posCentro.y - GerenciadorGrafico::getInstancia()->get_JANELAY()/2 - 100,
                                        GerenciadorGrafico::getInstancia()->get_JANELAX() + 100,
                                        GerenciadorGrafico::getInstancia()->get_JANELAY() + 100);

    return rect.intersects(ent->getShape()->getGlobalBounds());
}

void GR::GerenciadorColisao::executeColisoes(std::unordered_map<int, Entidade*>* mapEntidade){
    Entidade* ent1 = nullptr;
    Entidade* ent2 = nullptr;

    for(auto ent1 : *mapEntidade){
        if(ent1.second->getAtivo()){
            if(verificaEntidadeDentroDaTela(ent1.second) || ent1.second->getTipo(Type::Area)){
                for(auto ent2 : *mapEntidade){
                    if(ent2.second->getAtivo()){
                        if(ent1.first != ent2.first)
                            if(verificaEntidadeDentroDaTela(ent2.second) || ent2.second->getTipo(Type::Area)) 
                                colideEntidades(ent1.second, ent2.second); 
                    }
                }
            }
        }
    }
}