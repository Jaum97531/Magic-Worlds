#pragma once
#include "Menu.hpp"

namespace states{
    class MenuInicial : public Menu{
        private:

        public:
            MenuInicial();
            ~MenuInicial();

            void iniciarTextos() override;
            void tratarSelecao(sf::String menu);
    };
}