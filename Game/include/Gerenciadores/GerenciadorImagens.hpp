#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace GR{
    class GerenciadorImagens{
        private:
            std::map<std::string, sf::Texture> mapTexturas;
            static GerenciadorImagens* instancia;
            GerenciadorImagens();
            void criaTexturas();

        public:
            ~GerenciadorImagens();
            static GerenciadorImagens* getInstancia();
            void setTextura(std::string key, std::string file, bool repeated=false, bool smooth=false);
            sf::Texture* getTextura(std::string key);
    };
}