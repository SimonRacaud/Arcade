/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SolarFoxPlayer.hpp
*/

#ifndef SOLARFOXPLAYER_HPP_
#define SOLARFOXPLAYER_HPP_

#include <deque>
#include <unordered_map>
#include <iostream>
#include "../../GameObject/GameObject.hpp"
#include "Vector.hpp"
#include "../../../Timer/Timer.hpp"
#include "../Projectile/SolarFoxProjectile.hpp"
#include "../Enemy/SolarFoxEnemy.hpp"

namespace Game
{
    class SolarFoxProjectile;

    class SolarFoxEnemy;

    class SolarFoxPlayer : public GameObject
    {
        public:
            enum class Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

            SolarFoxPlayer(Vector const &mapSize);
            virtual ~SolarFoxPlayer();

            void move();
            void display(arcade::IDisplayModule &mod);

            void reset();
            void shoot(const Vector &mapSize);
            void prepareShooting();

            void setMovment(const Direction &movment);
            void setMovePeriod(clock_t newPeriod);

            clock_t getMovePeriod() const;
            Vector getPosition() const;

            bool isInMovement();
            bool isOutsideOfWalkableArea() const;
            ssize_t isShootCollideWith(std::deque<GameObject *> const &coins) const;
            void isCollideWith(std::deque<SolarFoxEnemy *> const &enemies);

        private :
            void resetPosition();
            void handleProjectile();

            Direction _currentMovment;
            Direction _newMovment;
            double _speed;
            Timer _timer;
            int _nbOfMovement;
            std::deque<SolarFoxProjectile *> _projectile;
            size_t _shootCounter;
    };
} // namespace Game

#endif // NIBBLERPLAYER_HPP_
