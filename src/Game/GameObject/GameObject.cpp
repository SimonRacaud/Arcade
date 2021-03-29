/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** GameObject.cpp.cc
*/

#include "GameObject.hpp"

using namespace Game;

GameObject::GameObject(Color color, const Vector &mapSize)
    : _anim(false), _color(color), _posMax(mapSize)
{
    this->_positions.push_back(Vector(0, 0));
}

GameObject::~GameObject()
{
}

void GameObject::display(arcade::IDisplayModule &mod)
{
    Color c = _color;

    if (_anim) {
        if ((size_t)clock() - _time >= _animFreq) {
            _time = clock();
            _colorState = !_colorState;
        }
        c = _animColor[_colorState];
    }
    for (size_t i = 0; i < _positions.size(); i++) {
        mod.putRectFill(
            c, Coord(1, 1), Coord(_positions[i].x, _positions[i].y));
    }
}

/**
 * throw OutOfBoundException
 * @param offsetX
 * @param offsetY
 */
void GameObject::move(double offsetX, double offsetY)
{
    if (this->canMove(offsetX, offsetY)) {
        for (size_t i = _positions.size() - 1; i > 0; i--) {
            this->_positions[i].y = this->_positions[i - 1].y;
            this->_positions[i].x = this->_positions[i - 1].x;
        }
        this->_positions[0].y += offsetY;
        this->_positions[0].x += offsetX;
    } else {
        throw OutOfBoundException("GameObject::move");
    }
}

/**
 * throw ObjectException
 * @param coord
 */
void GameObject::setPosition(Vector const &coord)
{
    if (_positions.size() == 1) {
        this->_positions[0].x = coord.x;
        this->_positions[0].y = coord.y;
    } else {
        throw ObjectException("GameObject::setPosition");
    }
}

bool GameObject::isCollideWith(const GameObject &obj) const
{
    for (size_t i = 0; i < _positions.size(); i++) {
        if (obj.isCollideCoord(_positions[i])) {
            return true;
        }
    }
    return false;
}

bool GameObject::isCollideWith(const GameMap &map) const
{
    for (size_t i = 0; i < _positions.size(); i++) {
        try {
            if (map.isCollideToCoord(_positions[i].x, _positions[i].y)) {
                return true;
            }
        } catch (OutOfBoundException const &e) {
            return true;
        }
    }
    return false;
}

/** Private **/

bool GameObject::canMove(double offsetX, double offsetY) const
{
    if (_positions.empty())
        return false;
    if (offsetX + _positions[0].x < 0
        || offsetY + _positions[0].y < 0) {
        return false;
    } else if (offsetY + _positions[0].y >= _posMax.y
        || offsetX + _positions[0].x >= _posMax.x) {
        return false;
    }
    return true;
}

bool GameObject::isCollideCoord(const Vector &pos) const
{
    for (size_t i = 0; i < _positions.size(); i++) {
        if (_positions[i].x - pos.x >= -0.0000001 && _positions[i].x - pos.x <= 0.0000001
        && _positions[i].y - pos.y >= -0.0000001 && _positions[i].y - pos.y <= 0.0000001) {
            return true;
        }
    }
    return false;
}

void GameObject::setAnimation(Color secondary, size_t freq)
{
    this->_anim = true;
    this->_animFreq = (freq * CLOCKS_PER_SEC) / 1000;
    this->_colorState = false;
    this->_animColor[0] = _color;
    this->_animColor[1] = secondary;
    this->_time = 0;
}

GameObject &GameObject::operator=(const GameObject &obj)
{
    _anim = obj._anim;
    _color = obj._color;
    _posMax.x = obj._posMax.x;
    _posMax.y = obj._posMax.y;
    _positions = obj._positions;
    _animFreq = obj._animFreq;
    _time = obj._time;
    _colorState = obj._colorState;
    _animColor[0] = obj._animColor[0];
    _animColor[1] = obj._animColor[1];
    return *this;
}
