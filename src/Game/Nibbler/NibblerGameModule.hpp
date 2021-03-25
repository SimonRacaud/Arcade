/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** NibblerGameModule.hpp.h
*/

#ifndef NIBBLERGAMEMODULE_HPP_
#define NIBBLERGAMEMODULE_HPP_

#include "../AbstractGameModule/AbstractGameModule.hpp"
#include "../GameMap/GameMap.hpp"
#include "../GameObject/GameObject.hpp"
#include "IDisplayModule.hpp"
#include "./Player/NibblerPlayer.hpp"
#include "Vector.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "../../Timer/Timer.hpp"

namespace Game
{
    typedef arcade::IDisplayModule::Color Color;
    #define MAP_SIZE Vector(40, 40)

    class NibblerGameModule : public AbstractGameModule {
      private:
        NibblerPlayer _player;
        Timer _coinGenTimer;
        std::deque<GameObject *> _coins;

      public:
        NibblerGameModule();
        ~NibblerGameModule() override;
        void reset();

      protected:
        void refreshGame();
        void generateCoin();
        void eventManager(arcade::IDisplayModule &displayModule);

    };
}

#endif // NIBBLERGAMEMODULE_HPP_
