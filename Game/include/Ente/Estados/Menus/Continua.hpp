#pragma once
#include "Menu.hpp"

namespace states{
    class Continua : public Menu{
        public:
            Continua(){ animacao.criaFrames("FASE LAVA", 8, false); iniciarTextos(); }
            ~Continua(){

            }

            void iniciarTextos(){
                int JANELAX = pGrafico->get_JANELAX();
                int JANELAY = pGrafico->get_JANELAY();
                
                sf::Text bglobby = criarTexto("LOBBY", 60, sf::Vector2f(JANELAX/2 - 5*14, JANELAY - 100), sf::Color::Black);
                titulos.push_back(bglobby);
                
                sf::Text lobby = criarTexto("LOBBY", 60, sf::Vector2f(JANELAX/2 - 5*14 + 5, JANELAY - 100), AZULVERDE);
                textos.push_back(lobby);               

                sf::Text mensagem = criarTexto("TALVEZ CONTINUA...", 60,  sf::Vector2f(JANELAX/2 - 250, 90), AZULVERDE);
                titulos.push_back(mensagem);

                sf::Text bgmensagem = criarTexto("TALVEZ CONTINUA...", 60,  sf::Vector2f(JANELAX/2 - 250 - 5, 90), sf::Color::Black);
                titulos.push_back(bgmensagem);

                sf::Text continuarFase = criarTexto("CONTINUAR FASE", 60, sf::Vector2f(JANELAX/2 - 200, JANELAY/2 - 30), AZULVERDE);
                textos.push_back(continuarFase);

                sf::Text bgcontinuarFase = criarTexto("CONTINUAR FASE", 60, sf::Vector2f(JANELAX/2 - 200 - 5, JANELAY/2 - 30), sf::Color::Black);
                titulos.push_back(bgcontinuarFase);
            }

            void tratarSelecao(sf::String selecao){
                if(selecao == "LOBBY") { pEstados->trocarEstado(LOBBY); }
                else if(selecao == "CONTINUAR FASE") { pEstados->trocarEstado(FASE2); }
            }
    };
};