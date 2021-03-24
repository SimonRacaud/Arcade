/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** NibblerPlayer.cpp.cc
*/

#include "NibblerPlayer.hpp"

using namespace Game;

NibblerPlayer::NibblerPlayer(const Vector &mapSize)
    : GameObject(Color::RED, mapSize)
{
    Vector initPos1(mapSize.x / 2, mapSize.y / 2);
    Vector initPos2(mapSize.x / 2, mapSize.y / 2 + 1);

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

NibblerPlayer::~NibblerPlayer()
{
}

void NibblerPlayer::move()
{
    if (_positions.size() >= 2) {
        Vector offset(this->_positions[0] - this->_positions[1]);
        GameObject::move(offset.x, offset.y);
    } else {
        std::cerr << "Warning: invalid snake size in "
                     "NibblerPlayer::move()\n";
    }
}

void NibblerPlayer::increaseLength()
{
    if (_positions.size() >= 2) {
        Vector delta = _positions[_positions.size() - 1]
            - _positions[_positions.size() - 2];
        Vector newBlock = _positions.back() + delta;

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

ssize_t NibblerPlayer::isCollideWith(const std::deque<GameObject> &coins) const
{
    for (size_t i = 0; i < coins.size(); i++) {
        if (coins[i].isCollideWith(*this)) {
            return (ssize_t) i;
        }
    }
    return -1;
}
