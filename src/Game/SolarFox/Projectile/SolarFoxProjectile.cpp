/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SolarFoxProjectile.cpp.cc
*/

#include "SolarFoxProjectile.hpp"

using namespace Game;

static const double DEF_SPEED = 1;

SolarFoxProjectile::SolarFoxProjectile(const Vector &mapSize, const Vector &originPos,
const Direction &originDir, const double &lifeTime)
    : GameObject(Color::BLACK, mapSize), _movment(originDir),
      _speed(DEF_SPEED), _originPos(originPos), _lifeTime(lifeTime)
{
    this->resetPosition(originPos);
}

SolarFoxProjectile::~SolarFoxProjectile() {}

void SolarFoxProjectile::move()
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

void SolarFoxProjectile::reset()
{
    this->_speed = DEF_SPEED;
    this->resetPosition(_originPos);
}

/** Private **/

void SolarFoxProjectile::resetPosition(const Vector &originPos)
{
    try {
        this->_positions.clear();
        this->_positions.push_back(originPos);
    } catch (BaseException const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

bool SolarFoxProjectile::isAlive()
{
    double diffX = std::abs(_positions[0].x - _originPos.x);
    double diffY =  std::abs(_positions[0].y - _originPos.y);

    if (diffX != 0 && diffX >= _lifeTime)
        return false;
    if (diffY != 0 && diffY >= _lifeTime)
        return false;
    return true;
}