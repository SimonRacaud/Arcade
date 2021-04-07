/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SolarFoxProjectile.cpp.cc
*/

#include "SolarFoxProjectile.hpp"

using namespace Game;

static const double DEF_SPEED = 0.1;

static const clock_t PROJECTILE_MOVE_PERIOD = 0.3;

SolarFoxProjectile::SolarFoxProjectile(const Vector &mapSize, const Vector &originPos,
const Direction &originDir, const double &lifeTime)
    : GameObject(Color::BLACK, mapSize), _movment(originDir),
      _speed(DEF_SPEED), _originPos(originPos), _lifeTime(lifeTime), _timer(PROJECTILE_MOVE_PERIOD)
{
    this->resetPosition(originPos);
}

SolarFoxProjectile::~SolarFoxProjectile() {}

void SolarFoxProjectile::move()
{
    if (!(_timer.shouldRefresh()))
        return;
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

Vector SolarFoxProjectile::getPosition() const
{
    return _positions[0];
}

bool SolarFoxProjectile::isAlive() const
{
    double diffX = std::abs(_positions[0].x - _originPos.x);
    double diffY =  std::abs(_positions[0].y - _originPos.y);

    if (diffX != 0 && diffX >= _lifeTime)
        return false;
    if (diffY != 0 && diffY >= _lifeTime)
        return false;
    return true;
}

ssize_t SolarFoxProjectile::isCollideWith(const std::deque<GameObject *> &coins) const
{
    for (size_t i = 0; i < coins.size(); i++) {
        if (coins[i]->isCollideWith(*this)) {
            return (ssize_t) i;
        }
    }
    return -1;
}

bool SolarFoxProjectile::isCollideWith(const SolarFoxPlayer &player) const
{
    Vector playerPosition = player.getPosition();
    double diffX = std::abs(playerPosition.x - _positions[0].x);
    double diffY = std::abs(playerPosition.y - _positions[0].y);

    if (diffX < 1 && diffY < 1)
        return true;
    return false;
}

bool SolarFoxProjectile::isCollideWith(const SolarFoxProjectile &projectile) const
{
    Vector projectilePosition = projectile.getPosition();
    double diffX = std::abs(projectilePosition.x - _positions[0].x);
    double diffY = std::abs(projectilePosition.y - _positions[0].y);

    if (diffX < 1 && diffY < 1)
        return true;
    return false;
}

void SolarFoxProjectile::resetPosition(const Vector &originPos)
{
    try {
        this->_positions.clear();
        this->_positions.push_back(originPos);
    } catch (BaseException const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}