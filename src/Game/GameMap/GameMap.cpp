/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** GameMap.cpp.cc
*/

#include "GameMap.hpp"

using namespace Game;

GameMap::GameMap(const Vector &size) : _size(size), _mtx(nullptr)
{
}

GameMap::GameMap(const Vector &size, std::deque<Color> const &fill)
    : _size(size), _mtx(nullptr)
{
    size_t idx = 0;

    this->_mtx = new Color *[size.y];
    for (size_t y = 0; y < (size_t)size.y; y++) {
        this->_mtx[y] = new Color[size.x];
        for (size_t x = 0; x < (size_t)size.x; x++) {
            if (fill.size() > idx) {
                this->_mtx[y][x] = fill[idx++];
            } else {
                this->_mtx[y][x] = arcade::IDisplayModule::Color::BLACK;
            }
        }
    }
}

GameMap::~GameMap()
{
    delete[] this->_mtx;
}

void GameMap::display(arcade::IDisplayModule &mod)
{
    if (this->_mtx != nullptr) {
        for (size_t y = 0; y < (size_t)_size.y; y++) {
            for (size_t x = 0; x < (size_t)_size.x; x++) {
                mod.putRectFill(
                    this->_mtx[y][x], arcade::Coord(1, 1), arcade::Coord(y, x));
            }
        }
    }
    this->draw(mod);
}

void GameMap::draw(arcade::IDisplayModule &)
{
    // To override
}

const std::deque<Color> &GameMap::getCollideColors() const
{
    return _collideColors;
}

void GameMap::setCollideColors(const std::deque<Color> &collideColors)
{
    _collideColors = collideColors;
}

/**
 * throw OutOfBoundException
 * @param x
 * @param y
 * @return
 */
bool GameMap::isCollideToCoord(int x, int y) const
{
    if (x >= (int)_size.x || y >= (int)_size.y || x < 0 || y < 0) {
        throw OutOfBoundException();
    }
    if (_mtx == nullptr) {
        return false;
    }
    if (std::find(_collideColors.begin(), _collideColors.end(), _mtx[y][x])
        != _collideColors.end()) {
        return true;
    }
    return false;
}

const Vector &GameMap::getSize() const
{
    return _size;
}
