/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SolarFoxPlayer.cpp.cc
*/

#include "SolarFoxPlayer.hpp"

using namespace Game;

static const double DEF_SPEED = 0.1;

static const clock_t PLAYER_MOVE_PERIOD = 10;

static const size_t SHOOT_COUNTER_MAX = 60;

SolarFoxPlayer::SolarFoxPlayer(const Vector &mapSize)
    : GameObject(Color::RED, mapSize), _currentMovment(Direction::UP),
      _newMovment(Direction::UP), _speed(DEF_SPEED),
      _timer(PLAYER_MOVE_PERIOD), _nbOfMovement(0), _shootCounter(0)
{
    this->resetPosition();
}

SolarFoxPlayer::~SolarFoxPlayer() {}

void SolarFoxPlayer::move()
{
    for (size_t i = 0; i < _projectile.size(); i++)
        _projectile[i]->move();
    if (!(_timer.shouldRefresh()))
        return;
    if (!(isInMovement()))
        _currentMovment = _newMovment;
    if (_currentMovment == Direction::UP) {
        GameObject::move(0, -_speed);
    } else if (_currentMovment == Direction::DOWN) {
        GameObject::move(0, _speed);
    } else if (_currentMovment == Direction::LEFT) {
        GameObject::move(-_speed, 0);
    } else if (_currentMovment == Direction::RIGHT) {
        GameObject::move(_speed, 0);
    }
    _nbOfMovement += 1;
}

void SolarFoxPlayer::display(arcade::IDisplayModule &mod)
{
    for (size_t i = 0; i < _projectile.size(); i++) {
        this->_projectile[i]->display(mod);
    }
    GameObject::display(mod);
}

void SolarFoxPlayer::reset()
{
    this->_speed = DEF_SPEED;
    this->resetPosition();
}

void SolarFoxPlayer::shoot(const Vector &mapSize)
{
    if (_shootCounter == 0) {
        handleProjectile();
        return;
    }
    if (_shootCounter != SHOOT_COUNTER_MAX && _shootCounter != 0) {
        _shootCounter -= 1;
        handleProjectile();
        return;
    }
    _shootCounter -= 1;
    if (_currentMovment == Direction::DOWN)
        _projectile.push_back(new SolarFoxProjectile(mapSize, _positions[0],
        SolarFoxProjectile::Direction::DOWN, 3));
    if (_currentMovment == Direction::UP)
        _projectile.push_back(new SolarFoxProjectile(mapSize, _positions[0],
        SolarFoxProjectile::Direction::UP, 3));
    if (_currentMovment == Direction::RIGHT)
        _projectile.push_back(new SolarFoxProjectile(mapSize, _positions[0],
        SolarFoxProjectile::Direction::RIGHT, 3));
    if (_currentMovment == Direction::LEFT)
        _projectile.push_back(new SolarFoxProjectile(mapSize, _positions[0],
        SolarFoxProjectile::Direction::LEFT, 3));
    handleProjectile();
}

void SolarFoxPlayer::prepareShooting()
{
    if (_shootCounter == 0)
        _shootCounter = SHOOT_COUNTER_MAX;
}

void SolarFoxPlayer::setMovment(const SolarFoxPlayer::Direction &movment)
{
    if (_currentMovment == Direction::UP && movment == Direction::DOWN)
        return;
    if (_currentMovment == Direction::DOWN && movment == Direction::UP)
        return;
    if (_currentMovment == Direction::RIGHT && movment == Direction::LEFT)
        return;
    if (_currentMovment == Direction::LEFT && movment == Direction::RIGHT)
        return;
    if (isInMovement()) {
        _newMovment = movment;
        return;
    }
    _newMovment = movment;
}

void SolarFoxPlayer::setMovePeriod(clock_t newPeriod)
{
    _timer.setPeriod(newPeriod);
}

clock_t SolarFoxPlayer::getMovePeriod() const
{
    return _timer.getPeriod();
}

Vector SolarFoxPlayer::getPosition() const
{
    return _positions[0];
}

bool SolarFoxPlayer::isInMovement()
{
    if (_nbOfMovement % 10 == 0) {
        _nbOfMovement = 0;
        _positions[0].x = std::round(_positions[0].x);
        _positions[0].y = std::round(_positions[0].y);
        return false;
    }
    return true;
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

ssize_t SolarFoxPlayer::isShootCollideWith(const std::deque<GameObject *> &coins) const
{
    ssize_t returnValue = 0;

    for (size_t i = 0; i < _projectile.size(); i++) {
        returnValue = _projectile[i]->isCollideWith(coins);
        if (returnValue != -1)
            return returnValue;
    }
    return -1;
}

void SolarFoxPlayer::isCollideWith(const std::deque<SolarFoxEnemy *> &enemies)
{
    for (size_t i = 0; i < enemies.size(); i++) {
        enemies[i]->isShootCollideWith(*this);
        for (size_t j = 0; j < _projectile.size(); j++)
            if (enemies[i]->isShootCollideWith(*_projectile[j])) {
                delete *(_projectile.begin() + j);
                _projectile.erase(_projectile.begin() + j);
            }
    }
}

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

void SolarFoxPlayer::handleProjectile()
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