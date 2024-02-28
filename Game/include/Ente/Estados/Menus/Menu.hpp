#pragma once
#include "../Estado.hpp"

namespace states{
    class Menu : public Estado{
        protected:

        public:
            Menu();
            ~Menu();

            void execute();
            virtual void iniciarTextos(){}
            void iniciarEstado();
            virtual void resized();
    };
}