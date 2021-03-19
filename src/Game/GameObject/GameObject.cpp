/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** GameObject.cpp.cc
*/

#include "GameObject.hpp"

using namespace Game;

GameObject::GameObject(Color color, const Coord &mapSize)
    : _color(color), _posMax({mapSize.first, mapSize.second}), _size(1)
{
    this->_positions.push_back(Vector(0, 0));
}

GameObject::~GameObject()
{
}

void GameObject::display(arcade::IDisplayModule &mod)
{
    for (size_t i = 0; i < _size; i++) {
        mod.putRectFill(
            _color, Coord(1, 1), Coord(_positions[i].y, _positions[i].x));
    }
}

/**
 * throw ObjectException
 * @param offsetX
 * @param offsetY
 */
void GameObject::move(int offsetX, int offsetY)
{
    if (this->canMove(offsetX, offsetY)) {
        for (ssize_t i = _size - 1; i >= 0; i--) {
            this->_positions[i].y = this->_positions[i - 1].y;
            this->_positions[i].x = this->_positions[i - 1].x;
        }
        this->_positions[0].y += offsetY;
        this->_positions[0].x += offsetX;
    } else {
        throw ObjectException("GameObject::move");
    }
}

/**
 * throw ObjectException
 * @param coord
 */
void GameObject::setPosition(Vector const& coord)
{
    if (_size == 1) {
        this->_positions[0].x = coord.x;
        this->_positions[0].y = coord.y;
    } else {
        throw ObjectException("GameObject::setPosition");
    }
}

bool GameObject::isCollideWith(const GameObject &obj) const
{
    for (size_t i = 0; i < _size; i++) {
        if (obj.isCollideCoord(_positions[i])) {
            return true;
        }
    }
    return false;
}

bool GameObject::isCollideWith(const GameMap &map) const
{
    for (size_t i = 0; i < _size; i++) {
        try {
            if (map.isCollideToCoord(_positions[i].x, _positions[i].y)) {
                return true;
            }
        } catch (OutOfBoundException const& e) {
            return true;
        }
    }
    return false;
}

/** Private **/

bool GameObject::canMove(int offsetX, int offsetY) const
{
    if (_positions.empty())
        return false;
    if (offsetX + (int) _positions[0].x < 0
        || offsetY + (int) _positions[0].y < 0) {
        return false;
    } else if (offsetY + (int) _positions[0].y >= (int) _posMax.y
               || offsetX + (int) _positions[0].x >= (int) _posMax.x) {
        return false;
    }
    for (size_t i = 1; i < _size; i++) {
        if (_positions[i].x == (offsetX + _positions[0].x)
            || _positions[i].y == (offsetY + _positions[0].y)) {
            return false;
        }
    }
    return true;
}
bool GameObject::isCollideCoord(const Vector &pos) const
{
    for (size_t i = 0; i < _size; i++) {
        if (_positions[i].x == pos.x && _positions[i].y == pos.y) {
            return true;
        }
    }
    return false;
}
