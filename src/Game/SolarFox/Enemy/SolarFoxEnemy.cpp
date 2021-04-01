/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SolarFoxEnemy.cpp.cc
*/

#include "SolarFoxEnemy.hpp"

using namespace Game;

static const double DEF_SPEED = 1;

SolarFoxEnemy::SolarFoxEnemy(const Vector &mapSize, const Vector &originPos,
const Direction &originDir)
    : GameObject(Color::BLACK, mapSize), _movment(originDir),
      _speed(DEF_SPEED), _originPos(originPos)
{
    this->resetPosition(originPos);
}

SolarFoxEnemy::~SolarFoxEnemy() {}

void SolarFoxEnemy::move()
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
    for (size_t i = 0; i < _projectile.size(); i++) {
        _projectile[i]->move();
    }
}

void SolarFoxEnemy::reset()
{
    this->_speed = DEF_SPEED;
    this->resetPosition(_originPos);
}

/** Private **/

void SolarFoxEnemy::resetPosition(const Vector &originPos)
{
    try {
        this->_positions.clear();
        this->_positions.push_back(originPos);
    } catch (BaseException const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void SolarFoxEnemy::updateMovment()
{
    if (_positions[0].x <= 3 && _movment == Direction::LEFT)
        _movment = Direction::RIGHT;
    if (_positions[0].x >= _posMax.x - 4 && _movment == Direction::RIGHT)
        _movment = Direction::LEFT;
    if (_positions[0].y <= 3 && _movment == Direction::UP)
        _movment = Direction::DOWN;
    if (_positions[0].y >= _posMax.y - 4 && _movment == Direction::DOWN)
        _movment = Direction::UP;
}

void SolarFoxEnemy::shoot(const Vector &mapSize)
{
    if (rand() % 100 < 5) {
        if (_positions[0].y == 1)
            _projectile.push_back(new SolarFoxProjectile(mapSize, _positions[0],
            SolarFoxProjectile::Direction::DOWN, 38));
        if (_positions[0].y == 38)
            _projectile.push_back(new SolarFoxProjectile(mapSize, _positions[0],
            SolarFoxProjectile::Direction::UP, 38));
        if (_positions[0].x == 1)
            _projectile.push_back(new SolarFoxProjectile(mapSize, _positions[0],
            SolarFoxProjectile::Direction::RIGHT, 38));
        if (_positions[0].x == 38)
            _projectile.push_back(new SolarFoxProjectile(mapSize, _positions[0],
            SolarFoxProjectile::Direction::LEFT, 38));
    }
    handleProjectile();
}

void SolarFoxEnemy::handleProjectile()
{
    for (size_t i = 0; i < _projectile.size(); i++) {
        if (!(_projectile[i]->isAlive())) {
            delete *(_projectile.begin() + i);
            _projectile.erase(_projectile.begin() + i);
            handleProjectile();
            return;
        }
    }
}

void SolarFoxEnemy::display(arcade::IDisplayModule &mod)
{
    for (size_t i = 0; i < _projectile.size(); i++) {
        this->_projectile[i]->display(mod);
    }
    GameObject::display(mod);
}