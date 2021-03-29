/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** PacmanMap.hpp.h
*/

#ifndef PACMANMAP_HPP_
#define PACMANMAP_HPP_

#include <deque>
#include <unordered_map>
#include "../../GameMap/GameMap.hpp"
#include "../../GameObject/GameObject.hpp"

namespace Game
{
    #define MAP_SIZE Vector(21, 21)
    #define INIT_PLAYER_COORD Vector(10,15)
    #define GUM_SCORE_INC 10
    #define SGUM_SCORE_INC 20


    class PacmanMap : public GameMap {
      private:
        std::deque<GameObject *> _pacgums;
        std::deque<GameObject *> _superPacgums;

      public:
        PacmanMap();
        virtual ~PacmanMap();

        void reset();
        size_t processCoinCollision(GameObject &player);

      protected:
        void draw(arcade::IDisplayModule &mod) override;

        void loadMap(Vector const &size, std::deque<Color> const &fill);

    };
} // namespace Game

#endif // PACMANMAP_HPP_
