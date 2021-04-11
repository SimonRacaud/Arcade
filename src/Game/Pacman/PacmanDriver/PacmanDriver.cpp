/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** PacmanDriver.cpp.cc
*/

#include "PacmanDriver.hpp"

using namespace Game;

std::ostream& operator<<(std::ostream& out, const PacmanDriver::Direction value)
{
    if (value == PacmanDriver::Direction::RIGHT) {
        return out << "RIGHT";
    } else if (value == PacmanDriver::Direction::LEFT) {
        return out << "LEFT";
    } else if (value == PacmanDriver::Direction::UP) {
        return out << "UP";
    } else if (value == PacmanDriver::Direction::DOWN) {
        return out << "DOWN";
    } else if (value == PacmanDriver::Direction::IDLE) {
        return out << "IDLE";
    }
    return out;
}

PacmanDriver::PacmanDriver() : _dir(Direction::IDLE)
{
}

arcade::Vector PacmanDriver::getStepTowardTarget(arcade::Vector target,
    arcade::Vector position, double speed, const PacmanMap &map)
{
    arcade::Vector destination(position);
    double lowerDistance = 0;

    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            if (std::abs(x) != std::abs(y)) {
                arcade::Vector coord =
                    this->getPosition(position, speed, x, y);

                if (this->isPositionAvailable(coord, position, map)) {
                    double distance = this->getDistance(target, coord);

                    if (distance < lowerDistance || lowerDistance == 0) {
                        lowerDistance = distance;
                        destination = coord;
                    }
                }
            }
        }
    }
    this->_dir = this->processDirection(position, destination);
    return destination;
}

arcade::Vector PacmanDriver::getStepAgainstTarget(arcade::Vector target,
    arcade::Vector position, double speed, const PacmanMap &map)
{
    arcade::Vector destination(position);
    double higherDistance = 0;

    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            if (std::abs(x) != std::abs(y)) {
                arcade::Vector coord =
                    this->getPosition(position, speed, x, y);

                if (this->isPositionAvailable(coord, position, map)) {
                    double distance = this->getDistance(target, coord);

                    if (distance > higherDistance) {
                        higherDistance = distance;
                        destination = coord;
                    }
                }
            }
        }
    }
    this->_dir = this->processDirection(position, destination);
    return destination;
}

/* Private */

double PacmanDriver::getDistance(arcade::Vector a, arcade::Vector b)
{
    return std::sqrt((std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2)));
}

bool PacmanDriver::isPositionAvailable(
    arcade::Vector position, Vector init, const PacmanMap &map)
{
    Direction direction = this->processDirection(init, position);

    if (_dir == Direction::LEFT && direction == Direction::RIGHT) {
        return false;
    } else if (_dir == Direction::RIGHT && direction == Direction::LEFT) {
        return false;
    } else if (_dir == Direction::UP && direction == Direction::DOWN) {
        return false;
    } else if (_dir == Direction::DOWN && direction == Direction::UP) {
        return false;
    }
    try {
        return !map.isCollideToCase(position);
    } catch (OutOfBoundException const &e) {
        return false;
    }
}

arcade::Vector PacmanDriver::getPosition(
    arcade::Vector src, double speed, int x, int y)
{
    return (arcade::Vector){src.x + (x * speed), src.y + (y * speed)};
}

PacmanDriver::Direction PacmanDriver::processDirection(
    Vector &init, Vector &result)
{
    Vector delta = result - init;

    if (delta.x < 0) {
        return Direction::LEFT;
    } else if (delta.x > 0) {
        return Direction::RIGHT;
    } else if (delta.y > 0) {
        return Direction::DOWN;
    } else if (delta.y < 0) {
        return Direction::UP;
    }
    return Direction::IDLE;
}
