/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SolarFoxPlayer.cpp.cc
*/

#include "SolarFoxPlayer.hpp"

using namespace Game;

static const double DEF_SPEED = 1;

SolarFoxPlayer::SolarFoxPlayer(const Vector &mapSize)
    : GameObject(Color::RED, mapSize), _movment(Direction::UP),
      _speed(DEF_SPEED)
{
    this->resetPosition();
}

SolarFoxPlayer::~SolarFoxPlayer() {}

void SolarFoxPlayer::move()
{
    if (_movment == Direction::UP) {
        GameObject::move(0, -_speed);
    } else if (_movment == Direction::DOWN) {
        GameObject::move(0, _speed);
    } else if (_movment == Direction::LEFT) {
        GameObject::move(-_speed, 0);
    } else if (_movment == Direction::RIGHT) {
        GameObject::move(_speed, 0);
    }
}

bool SolarFoxPlayer::isOutsideOfWalkableArea() const
{
    if (_positions[0].x < 3 || _positions[0].x >= _posMax.x - 3) {
        return true;
    }
    if (_positions[0].y < 3 || _positions[0].y >= _posMax.y - 3) {
        return true;
    }
    return false;
}

ssize_t SolarFoxPlayer::isCollideWith(const std::deque<GameObject *> &coins) const
{
    for (size_t i = 0; i < coins.size(); i++) {
        if (coins[i]->isCollideWith(*this)) {
            return (ssize_t) i;
        }
    }
    return -1;
}

void SolarFoxPlayer::reset()
{
    this->_speed = DEF_SPEED;
    this->resetPosition();
}

/** Private **/

void SolarFoxPlayer::resetPosition()
{
    Vector initPos(_posMax.x / 2, _posMax.y / 2);

    try {
        this->_positions.clear();
        this->_positions.push_back(initPos);
    } catch (BaseException const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void SolarFoxPlayer::setMovment(const SolarFoxPlayer::Direction &movment)
{
    if (_movment == Direction::UP && movment == Direction::DOWN)
        return;
    if (_movment == Direction::DOWN && movment == Direction::UP)
        return;
    if (_movment == Direction::RIGHT && movment == Direction::LEFT)
        return;
    if (_movment == Direction::LEFT && movment == Direction::RIGHT)
        return;
    _movment = movment;
}