/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** PacmanDriver.hpp.h
*/

#ifndef PACMANDRIVER_HPP_
#define PACMANDRIVER_HPP_

#include <cmath>
#include "../PacmanMap/PacmanMap.hpp"
#include "Vector.hpp"

namespace Game
{
    typedef arcade::Vector Vector;

    class PacmanDriver {
      public:
        enum class Direction { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, IDLE = 4 };

        PacmanDriver();
        ~PacmanDriver() = default;

        arcade::Vector getStepTowardTarget(arcade::Vector target,
            arcade::Vector position, double speed, PacmanMap const &map);

        arcade::Vector getStepAgainstTarget(arcade::Vector target,
            arcade::Vector position, double speed, PacmanMap const &map);

      private:
        arcade::Vector getPosition(
            arcade::Vector src, double speed, int x, int y);

        bool isPositionAvailable(
            Vector position, Vector init, const PacmanMap &map);

        double getDistance(arcade::Vector a, arcade::Vector b);

        Direction processDirection(Vector &init, Vector &result);

        Direction _dir;
    };
} // namespace Game

#endif // PACMANDRIVER_HPP_
