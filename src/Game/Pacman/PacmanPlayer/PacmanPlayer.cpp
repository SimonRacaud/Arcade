/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** PacmanPlayer.cpp.cc
*/

#include "PacmanPlayer.hpp"

using namespace Game;

static const double DEF_SPEED = 0.5;

extern const Vector INIT_PLAYER_COORD;

PacmanPlayer::PacmanPlayer()
    : GameObject(Color::CYAN, MAP_SIZE), _dir(Direction::IDLE), _map(nullptr),
      _speed(DEF_SPEED), _speedCoef(nullptr)
{
    this->setPosition(INIT_PLAYER_COORD);
}

PacmanPlayer::~PacmanPlayer()
{
}

void PacmanPlayer::move()
{
    Vector offset(0, 0);
    double speedCoef = (this->_speedCoef) ? *_speedCoef : 0;

    if (_dir == Direction::IDLE) {
        return;
    }
    if (_dir == Direction::UP) {
        offset.y = -_speed * speedCoef;
    } else if (_dir == Direction::DOWN) {
        offset.y = _speed * speedCoef;
    } else if (_dir == Direction::LEFT) {
        offset.x = -_speed * speedCoef;
    } else if (_dir == Direction::RIGHT) {
        offset.x = _speed * speedCoef;
    }
    try {
        if (this->isCollideWithMap(offset)) {
            return;
        }
        GameObject::move(offset.x, offset.y);
    } catch (OutOfBoundException const &e) {
        if (_map) {
            Vector mapSize = this->_map->getSize();

            if (std::ceil(_positions[0].x) == mapSize.x - 1) {
                GameObject::move(-mapSize.x + 1, 0);
            } else if (std::floor(_positions[0].x) == 0) {
                GameObject::move(mapSize.x - 1, 0);
            }
        }
    }
}

void PacmanPlayer::reset()
{
    this->setPosition(INIT_PLAYER_COORD);
}

void PacmanPlayer::setDirection(PacmanPlayer::Direction dir)
{
    if (_map) {
        Vector currentPos = _positions[0];
        if (dir == Direction::UP) {
            currentPos.y += -1;
        } else if (dir == Direction::DOWN) {
            currentPos.y += 1;
        } else if (dir == Direction::LEFT) {
            currentPos.x += -1;
        } else if (dir == Direction::RIGHT) {
            currentPos.x += 1;
        }
        if (_map->isCollideToCoord(currentPos.x, currentPos.y)) {
            return;
        }
        _dir = dir;
    }
}

void PacmanPlayer::setSpeedCoef(double &speedCoef)
{
    _speedCoef = &speedCoef;
}

void PacmanPlayer::setMap(PacmanMap &map)
{
    this->_map = &map;
}

/** Private **/

bool PacmanPlayer::isCollideWithMap(const Vector &offset)
{
    if (_map == nullptr)
        return false;
    if (_map->isCollideToCoord(std::floor(_positions[0].x + offset.x),
                             std::floor(_positions[0].y + offset.y))) {
        return true;
    }
    if (_map->isCollideToCoord(std::ceil(_positions[0].x + offset.x),
                             std::ceil(_positions[0].y + offset.y))) {
        return true;
    }
    if (_map->isCollideToCoord(std::floor(_positions[0].x + offset.x),
                              std::ceil(_positions[0].y + offset.y))) {
        return true;
    }
    if (_map->isCollideToCoord(std::ceil(_positions[0].x + offset.x),
                              std::floor(_positions[0].y + offset.y))) {
        return true;
    }
    return false;
}
