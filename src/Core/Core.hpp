/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Core.hpp
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "../MainMenu/MainMenu.hpp"
#include "../CoreConfig/CoreConfig.hpp"
#include "../Timer/Timer.hpp"

#include <string>

namespace arcade
{
    typedef IDisplayModule::KeyList Key;

    class Core {
      public:
        Core(std::string const &defGraphicFile);
        virtual ~Core();

        void loop();
        void eventManager();
        CoreConfig &getConfig();

      protected:
      private:
        CoreConfig _config;
        MainMenu _mainMenu;
    };
} // namespace arcade

#endif // ARCADE_HPP_
