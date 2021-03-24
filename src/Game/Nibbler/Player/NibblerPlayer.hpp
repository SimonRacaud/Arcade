/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** NibblerPlayer.hpp.h
*/

#ifndef NIBBLERPLAYER_HPP_
#define NIBBLERPLAYER_HPP_

#include <deque>
#include "../../GameObject/GameObject.hpp"
#include "Vector.hpp"
#include <iostream>

namespace Game
{
    class NibblerPlayer : public GameObject {
      public:
        NibblerPlayer(Vector const &mapSize);
        virtual ~NibblerPlayer();

        void move();

        void increaseLength();

        bool isCollideWithSelf() const;
        ssize_t isCollideWith(std::deque<GameObject> const &coins) const;
    };
} // namespace Game

#endif // NIBBLERPLAYER_HPP_
