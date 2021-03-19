/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** GameMap.hpp.h
*/

#ifndef GAMEMAP_HPP_
#define GAMEMAP_HPP_

#include <algorithm>
#include <deque>
#include "IDisplayModule.hpp"
#include "OutOfBoundException.hpp"
#include "Vector.hpp"
#include "../../../../../../../../media/work/2_CURRENT/B-OOP-400-REN-4-1-arcade-aurelien.joncour/includes/Vector.hpp"

namespace Game
{
    typedef arcade::IDisplayModule::Color Color;

    class GameMap {
      protected:
        Vector _size;
        Color **_mtx;
        std::deque<Color> _collideColors;

        virtual void draw(arcade::IDisplayModule &mod);

      public:
        GameMap(Vector const &size);
        GameMap(Vector const &size, std::deque<Color> const &fill);
        virtual ~GameMap();

        void display(arcade::IDisplayModule &mod);

        const std::deque<Color> &getCollideColors() const;
        void setCollideColors(const std::deque<Color> &collideColors);
        const Vector &getSize() const;

        bool isCollideToCoord(int x, int y) const;
    };
} // namespace Game

#endif // GAMEMAP_HPP_
