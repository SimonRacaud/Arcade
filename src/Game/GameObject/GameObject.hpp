/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** GameObject.hpp.h
*/

#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include "Game/GameMap/GameMap.hpp"
#include "Game/GameObject/GameObject.hpp"
#include "IDisplayModule.hpp"
#include "ObjectException.hpp"
#include "OutOfBoundException.hpp"
#include "Vector.hpp"

namespace Game
{
    typedef arcade::Coord Coord;

    class GameObject {
      public:
        GameObject(Color color, Coord const &mapSize);
        virtual ~GameObject();

        void display(arcade::IDisplayModule &mod);

        void move(int offsetX, int offsetY);
        void setPosition(Vector const &coord);

        bool isCollideWith(GameObject const &obj) const;
        bool isCollideWith(GameMap const &map) const;

      protected:
        bool canMove(int offsetX, int offsetY) const;

        bool isCollideCoord(Vector const &pos) const;

        Color _color;
        Vector _posMax;
        size_t _size;
        std::deque<Vector> _positions;
    };
} // namespace Game

#endif // GAMEOBJECT_HPP_
