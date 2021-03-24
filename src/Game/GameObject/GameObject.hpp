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
#include <ctime>
#include <iostream>

namespace Game
{
    typedef arcade::Coord Coord;

    class GameObject {
      public:
        GameObject(Color color, Vector const &mapSize);
        virtual ~GameObject();

        GameObject &operator=(GameObject const& obj);

        void display(arcade::IDisplayModule &mod);

        virtual void move(int offsetX, int offsetY);
        void setPosition(Vector const &coord);

        bool isCollideWith(GameObject const &obj) const;
        bool isCollideWith(GameMap const &map) const;

        void setAnimation(Color secondary, size_t freq);

        bool isCollideCoord(Vector const &pos) const;
      protected:
        bool canMove(int offsetX, int offsetY) const;

        bool _anim;

        Color _color;
        Vector _posMax;
        std::deque<Vector> _positions;

        size_t _animFreq;
        clock_t _time;
        bool _colorState;
        Color _animColor[2];
    };
} // namespace Game

#endif // GAMEOBJECT_HPP_
