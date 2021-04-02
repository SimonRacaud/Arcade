/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SolarFoxEnemy.hpp
*/

#ifndef SOLARFOXENEMY_HPP_
#define SOLARFOXENEMY_HPP_

#include <deque>
#include <unordered_map>
#include <iostream>
#include "../../GameObject/GameObject.hpp"
#include "Vector.hpp"
#include "../Projectile/SolarFoxProjectile.hpp"
#include "../../../Timer/Timer.hpp"
#include "../../../exception/includes/ShootException.hpp"

namespace Game
{
    class SolarFoxProjectile;

    class SolarFoxPlayer;
    
    class SolarFoxEnemy : public GameObject
    {
        public:
            enum class Direction {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3};

            SolarFoxEnemy(Vector const &mapSize, const Vector &originPos,
            const Direction &originDir);
            virtual ~SolarFoxEnemy();

            void move();
            void display(arcade::IDisplayModule &mod);

            void reset();
            void updateMovment();
            void shoot(const Vector &mapSize);

            bool isInMovement();
            void isShootCollideWith(const SolarFoxPlayer &player) const;
            bool isShootCollideWith(const SolarFoxProjectile &projectile);
        
        private :
            void resetPosition(const Vector &originPos);
            void handleProjectile();

            Direction _movment;
            double _speed;
            const Vector &_originPos;
            std::deque<SolarFoxProjectile *> _projectile;
            Timer _timer;
            int _nbOfMovement;
    };
} // namespace Game

#endif // NIBBLERPLAYER_HPP_
