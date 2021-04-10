/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SolarFoxGameModule.hpp
*/

#ifndef SOLAR_FOX_GAME_MODULE_HPP
#define SOLAR_FOX_GAME_MODULE_HPP

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

            enum class Difficulty {EASY = 0, MEDIUM = 1, HARD = 2};

            void reset();

            void eventManager(arcade::IDisplayModule &displayModule);

        private :
            void refreshGame(bool refreshActions);
            void updateDifficulty();
            void display();
            void handlePlayer();
            void handleCollisionWithCoin();

            void generateCoin();
            void generateEnemies();

            SolarFoxPlayer _player;
            std::deque<GameObject *> _goodCoins;
            std::deque<GameObject *> _badCoins;
            std::deque<SolarFoxEnemy *> _enemies;
            Difficulty _difficulty;
    };
}

#endif // SOLAR_FOX_GAME_MODULE_HPP
