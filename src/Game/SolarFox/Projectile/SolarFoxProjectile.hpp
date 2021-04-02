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
#include "../../../Timer/Timer.hpp"
#include "../Player/SolarFoxPlayer.hpp"

namespace Game
{
    class SolarFoxPlayer;

    class SolarFoxProjectile : public GameObject
    {
        public:
            enum class Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

            SolarFoxProjectile(Vector const &mapSize, const Vector &originPos,
            const Direction &originDir, const double &lifeTime);
            virtual ~SolarFoxProjectile();

            void move();

            void reset();

            Vector getPosition() const;

            bool isAlive() const;
            ssize_t isCollideWith(std::deque<GameObject *> const &coins) const;
            bool isCollideWith(const SolarFoxPlayer &player) const;
            bool isCollideWith(const SolarFoxProjectile &projectile) const;

        private :
            void resetPosition(const Vector &originPos);

            Direction _movment;
            double _speed;
            const Vector &_originPos;
            const double _lifeTime;
            Timer _timer;
    };
} // namespace Game

#endif // NIBBLERPLAYER_HPP_
