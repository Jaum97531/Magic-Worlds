#pragma once
#include "../Ente.hpp"
#include <iostream>
using namespace std;

#define BLOCO 32
#define GRAVIDADE 4
#define VELOCIDADE_TERMINAL 59

namespace Entidades{
    class AreaDeEfeito;
    class Projetil;

    namespace Personagens{
        class Personagem;
    };

    namespace Objetos{
        class Objeto;
    };
}


enum class Type{
    Objeto,
    Personagem,
    Projetil,
    Jogador,
    Inimigo,
    Plataforma,
    Lava,
    Caixa,
    Esqueleto, 
    Zumbi,
    Fantasma,
    Area,
    Porta, 
    Entidade
};

namespace Entidades{
    class Entidade : public Ente{
        protected:
            static int proximoId; 
            int ID;
            bool estatico;
            float gravidade;
            sf::Vector2f movimento;
            std::vector<Type> tiposSecundarios;
            sf::Vector2f posAntigaColision;

            sf::RectangleShape corpo;
            
        public:
            Entidade();
            ~Entidade();
            
            const bool getTipoSecundario(Type tipo);
            void addTipoSecundario(Type tipo) { tiposSecundarios.push_back(tipo); }
            virtual void execute(){}
            virtual const Type getType() const = 0;
            void zerarGravidade() { gravidade = 0; }

            virtual void setPosition(sf::Vector2f pos) { corpo.setPosition(pos); }
            void deslocar(sf::Vector2f deslocamento) { corpo.move(deslocamento); }
            virtual void desenhar() { pGrafico->draw(corpo); }
            void setColor(sf::Color cor) { corpo.setFillColor(cor); }
            sf::RectangleShape* getShape() { return &corpo; }
            bool getEstatico() const { return estatico; }
            virtual void foraDosLimites() { ativo = false; }

            sf::Vector2f getMovimento() const { return movimento; }
            virtual void acelerarGravidade();

            virtual void tratarColisao(Personagens::Personagem* personagem, std::string direcao){}
            virtual void tratarColisao(Projetil* projetil, std::string direcao){}
            virtual void tratarColisao(AreaDeEfeito* area, std::string direcao){}
            virtual void tratarColisao(Objetos::Objeto* objeto, std::string direcao){}
            sf::FloatRect getGlobalBounds() { return corpo.getGlobalBounds(); }
            sf::Vector2f getPosition() { return corpo.getPosition(); }
            float getVelocidadeDeQueda() { return gravidade; }
            void setGravidade(float gravity) { gravidade = gravity; }
            sf::Vector2f getSize() { return corpo.getSize(); }
            sf::Vector2f getPosAntiga() { return posAntigaColision; }
            
            bool operator==(Entidade* ent){ return ID == ent->getId(); }
            bool operator==(const int id) { return ID == id; }
            bool operator!=(Entidade* ent) { return ID != ent->getId(); }
            bool operator!=(const int id) { return ID != id; }
            const int getId() { return ID; }
            const int NovoId() { return proximoId++; }
            static int getProximoID() { return proximoId; }
            static void setProxId(int id) { proximoId = id; }
            void setId(const int id){ ID = id; }
            virtual Type tipoMaisAbstrato() { return Type::Entidade; }

            virtual void setSize(sf::Vector2f size){ corpo.setSize(size); }
    };
}