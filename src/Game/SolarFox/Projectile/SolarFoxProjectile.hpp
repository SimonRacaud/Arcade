/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SolarFoxProjectile.hpp
*/

#ifndef SOLARFOXPROJECTILE_HPP_
#define SOLARFOXPROJECTILE_HPP_

#include <deque>
#include <unordered_map>
#include <iostream>
#include "../../GameObject/GameObject.hpp"
#include "Vector.hpp"


namespace Game
{
    class SolarFoxProjectile : public GameObject
    {
      public:
        enum class Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

      private:
        Direction _movment;
        double _speed;
        const Vector &_originPos;
        const double _lifeTime;

        void resetPosition(const Vector &originPos);

      public:
        SolarFoxProjectile(Vector const &mapSize, const Vector &originPos,
        const Direction &originDir, const double &lifeTime);
        virtual ~SolarFoxProjectile();

        void move();
        void reset();

        bool isAlive();
    };
} // namespace Game

#endif // NIBBLERPLAYER_HPP_
