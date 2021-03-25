/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** NibblerPlayer.hpp.h
*/

#ifndef NIBBLERPLAYER_HPP_
#define NIBBLERPLAYER_HPP_

#include <deque>
#include <unordered_map>
#include <iostream>
#include "../../GameObject/GameObject.hpp"
#include "Vector.hpp"

namespace Game
{
    class NibblerPlayer : public GameObject {
      public:
        enum class Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

      private:
        Direction _movment;
        double _speed;

        void resetPosition();
      public:
        NibblerPlayer(Vector const &mapSize);
        virtual ~NibblerPlayer();

        void move();
        void reset();

        void setMovment(const Direction &movment);
        void rotate(const Direction &dir);

        void increaseLength();

        bool isCollideWithSelf() const;
        ssize_t isCollideWith(std::deque<GameObject *> const &coins) const;
    };
} // namespace Game

#endif // NIBBLERPLAYER_HPP_
