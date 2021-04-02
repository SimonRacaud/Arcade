/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SolarFoxEnemy.cpp.cc
*/

#include "SolarFoxEnemy.hpp"

using namespace Game;

static const double DEF_SPEED = 0.1;

static const clock_t ENEMY_MOVE_PERIOD = 10;

SolarFoxEnemy::SolarFoxEnemy(const Vector &mapSize, const Vector &originPos,
const Direction &originDir)
    : GameObject(Color::BLACK, mapSize), _movment(originDir),
      _speed(DEF_SPEED), _originPos(originPos), _timer(ENEMY_MOVE_PERIOD),
      _nbOfMovement(0)
{
    this->resetPosition(originPos);
}

SolarFoxEnemy::~SolarFoxEnemy() {}

void SolarFoxEnemy::move()
{
    bool shouldRefresh = _timer.shouldRefresh();

    if (shouldRefresh) {
        if (_movment == Direction::UP) {
            GameObject::move(0, -_speed);
        } else if (_movment == Direction::DOWN) {
            GameObject::move(0, _speed);
        } else if (_movment == Direction::LEFT) {
            GameObject::move(-_speed, 0);
        } else if (_movment == Direction::RIGHT) {
            GameObject::move(_speed, 0);
        }
        _nbOfMovement += 1;
    }
    for (size_t i = 0; i < _projectile.size(); i++) {
        _projectile[i]->move();
    }
}

void SolarFoxEnemy::display(arcade::IDisplayModule &mod)
{
    for (size_t i = 0; i < _projectile.size(); i++) {
        this->_projectile[i]->display(mod);
    }
    GameObject::display(mod);
}

void SolarFoxEnemy::reset()
{
    this->_speed = DEF_SPEED;
    this->resetPosition(_originPos);
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
    if (isInMovement()) {
        handleProjectile();
        return;
    }
    if (rand() % 100 < 10) {
        if (_positions[0].y == 1)
            _projectile.push_back(new SolarFoxProjectile(mapSize, _positions[0],
            SolarFoxProjectile::Direction::DOWN, 36));
        if (_positions[0].y == 38)
            _projectile.push_back(new SolarFoxProjectile(mapSize, _positions[0],
            SolarFoxProjectile::Direction::UP, 36));
        if (_positions[0].x == 1)
            _projectile.push_back(new SolarFoxProjectile(mapSize, _positions[0],
            SolarFoxProjectile::Direction::RIGHT, 36));
        if (_positions[0].x == 38)
            _projectile.push_back(new SolarFoxProjectile(mapSize, _positions[0],
            SolarFoxProjectile::Direction::LEFT, 36));
    }
    handleProjectile();
}

bool SolarFoxEnemy::isInMovement()
{
    if (_nbOfMovement == 10) {
        _nbOfMovement = 0;
        return false;
    }
    return true;
}

void SolarFoxEnemy::isShootCollideWith(const SolarFoxPlayer &player) const
{
    for (size_t i = 0; i < _projectile.size(); i++) {
        if (_projectile[i]->isCollideWith(player)) {
            throw ShootException();
        }
    }
}

bool SolarFoxEnemy::isShootCollideWith(const SolarFoxProjectile &projectile)
{
    for (size_t i = 0; i < _projectile.size(); i++) {
        if (_projectile[i]->isCollideWith(projectile)) {
            delete *(_projectile.begin() + i);
            _projectile.erase(_projectile.begin() + i);
            return true;
        }
    }
    return false;
}

void SolarFoxEnemy::resetPosition(const Vector &originPos)
{
    try {
        this->_positions.clear();
        this->_positions.push_back(originPos);
    } catch (BaseException const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
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