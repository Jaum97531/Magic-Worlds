#pragma once
#include "../Ente.hpp"
#include <unordered_map>

#define BLOCO 32
#define GRAVIDADE 4
#define VELOCIDADE_TERMINAL 60

#define FOGO 1
#define GELO 2
#define VENTO 3
#define TERRA 4
#define VENENO 5

namespace Entidades{
    class AreaDeEfeito;
    class Projetil;

    namespace Personagens{
        class Personagem;
        class Jogador;
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



// Defina a função hash para Type
namespace std {
    template <>
    struct hash<Type> {
        size_t operator()(const Type& valor) const {
            // Use a função hash padrão para enums
            return static_cast<size_t>(valor);
        }
    };
}

// Defina a função hash para std::pair<Type, Type>
namespace std {
    template <>
    struct hash<std::pair<Type, Type>> {
        size_t operator()(const std::pair<Type, Type>& p) const {
            // Combine hashes dos enums do par
            size_t hash1 = std::hash<Type>()(p.first);
            size_t hash2 = std::hash<Type>()(p.second);

            // Simples algoritmo de combinação de hash
            return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
        }
    };
}


namespace Entidades{
    class Entidade : public Ente{
        protected:
            static int proximoId; 
            int ID;
            bool estatico;
            float gravidade;
            sf::Vector2f movimento;
            std::unordered_map<Type, bool> tipos;
            Type Tipocolision;
            sf::Vector2f posAntigaColision;

            sf::RectangleShape corpo;
            
        public:
            Entidade();
            ~Entidade();
            
            const bool getTipo(Type type) { return tipos[type]; }
            Type getTipoColision() { return Tipocolision; }
            virtual void execute(){}
            
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
            virtual void tratarColisao(Personagens::Jogador* jogador, std::string direcao){}


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

            virtual void setSize(sf::Vector2f size){ corpo.setSize(size); }
    };
}