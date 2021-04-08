/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** NibblerPlayer.cpp.cc
*/

#include "NibblerPlayer.hpp"

using namespace Game;

static const double DEF_SPEED = 1;

NibblerPlayer::NibblerPlayer(const Vector &mapSize)
    : GameObject(Color::RED, mapSize), _movment(Direction::UP),
      _speed(DEF_SPEED)
{
    this->resetPosition();
}

NibblerPlayer::~NibblerPlayer()
{
}

void NibblerPlayer::move()
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

void NibblerPlayer::increaseLength()
{
    if (_positions.size() >= 2) {
        Vector delta = _positions[_positions.size() - 1]
            - _positions[_positions.size() - 2];
        Vector newBlock = _positions.back() - delta;

        _positions.push_back(newBlock);
    } else {
        std::cerr << "Warning: invalid snake size in "
                     "NibblerPlayer::increaseLength()\n";
    }
}

bool NibblerPlayer::isCollideWithSelf() const
{
    for (size_t i = 1; i < _positions.size(); i++) {
        if (_positions[i].x == _positions[0].x
            && _positions[i].y == _positions[0].y) {
            return true;
        }
    }
    return false;
}

ssize_t NibblerPlayer::isCollideWith(const std::deque<GameObject *> &coins) const
{
    for (size_t i = 0; i < coins.size(); i++) {
        if (coins[i]->isCollideWith(*this)) {
            return (ssize_t) i;
        }
    }
    return -1;
}

void NibblerPlayer::reset()
{
    this->_speed = DEF_SPEED;
    this->_movment = Direction::UP;
    this->resetPosition();
}

/** Private **/

void NibblerPlayer::resetPosition()
{
    Vector initPos1(_posMax.x / 2, _posMax.y / 2);
    Vector initPos2(_posMax.x / 2, _posMax.y / 2 + 1);

    try {
        this->_positions.clear();
        this->_positions.push_back(initPos1);
        this->_positions.push_back(initPos2);
        for (size_t p = 0; p < 2; p++) {
            this->increaseLength();
        }
    } catch (BaseException const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void NibblerPlayer::setMovment(const NibblerPlayer::Direction &movment)
{
    if (_positions.size() >= 2) {
        Vector offset(this->_positions[0] - this->_positions[1]);

        if (movment == Direction::UP && offset.y > 0) {
            return;
        } else if (movment == Direction::DOWN && offset.y < 0) {
            return;
        } else if (movment == Direction::LEFT && offset.x > 0) {
            return;
        } else if (movment == Direction::RIGHT && offset.x < 0) {
            return;
        }
    }
    _movment = movment;
}

void NibblerPlayer::rotate(const NibblerPlayer::Direction &dir)
{
    Direction update = _movment;

    if (dir == Direction::LEFT) {
        if (_movment == Direction::UP) {
            update = Direction::LEFT;
        } else {
            update = (Direction)((int)update - 1);
        }
    } else if (dir == Direction::RIGHT) {
        if (_movment == Direction::LEFT) {
            update = Direction::UP;
        } else {
            update = (Direction)((int)update + 1);
        }
    }
    this->setMovment(update);
}
