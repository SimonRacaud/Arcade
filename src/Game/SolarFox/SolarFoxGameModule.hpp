/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SolarFoxGameModule.hpp
*/

#ifndef NIBBLERGAMEMODULE_HPP_
#define NIBBLERGAMEMODULE_HPP_

#include "../AbstractGameModule/AbstractGameModule.hpp"
#include "../GameMap/GameMap.hpp"
#include "../GameObject/GameObject.hpp"
#include "IDisplayModule.hpp"
#include "./Player/SolarFoxPlayer.hpp"
#include "./Enemy/SolarFoxEnemy.hpp"
#include "Vector.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "../../Timer/Timer.hpp"

namespace Game
{
    typedef arcade::IDisplayModule::Color Color;
    #define MAP_SIZE Vector(40, 40)

    class SolarFoxGameModule : public AbstractGameModule
    {
      public :
          SolarFoxGameModule();
          ~SolarFoxGameModule() override;

          void reset();

          enum class Difficulty { EASY = 0, MEDIUM = 1, HARD = 2};

      protected :
          void refreshGame();
          void generateCoin();
          void eventManager(arcade::IDisplayModule &displayModule);
          void updateDifficulty();
          void generateEnemies();

      private :
          SolarFoxPlayer _player;
          std::deque<GameObject *> _coins;
          std::deque<SolarFoxEnemy *> _enemies;
          Difficulty _difficulty;

    };
}

#endif // NIBBLERGAMEMODULE_HPP_
