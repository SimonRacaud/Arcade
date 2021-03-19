/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Projectile.cpp.cc
*/

#include "Projectile.hpp"

Game::Projectile::Projectile(
    Color color, const Vector &mapSize, const Vector &initPos, Direction dir)
    : GameObject(color, mapSize), _direction(dir), _time(0),
      _speed(GAME_PROJECTILE_SPEED)
{
    this->setPosition(initPos);
}

/**
 * throw OutOfBoundException
 */
void Game::Projectile::move()
{
    if ((clock() - _time) / CLOCKS_PER_SEC >= _speed) {
        _time = clock();
        if (_direction == Direction::UP) {
            GameObject::move(0, 1);
        } else if (_direction == Direction::DOWN) {
            GameObject::move(0, -1);
        }
    }
}

void Game::Projectile::setSpeed(size_t speed)
{
    _speed = speed;
}
