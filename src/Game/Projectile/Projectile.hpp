/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Projectile.hpp.h
*/

#ifndef PROJECTILE_HPP_
#define PROJECTILE_HPP_

#include "Game/GameObject/GameObject.hpp"
#include <ctime>
#include <time.h>

namespace Game
{
    #define GAME_PROJECTILE_SPEED 1

    class Projectile : public GameObject {
      public:
        enum class Direction { UP, DOWN };

        Projectile(Color color, Vector const &mapSize, Vector const &initPos,
            Projectile::Direction dir);
        virtual ~Projectile() = default;

        void move(void);
      private:
        Direction _direction;
        size_t _time;
        size_t _speed;

      public:
        void setSpeed(size_t speed);
    };
} // namespace Game

#endif // PROJECTILE_HPP_
