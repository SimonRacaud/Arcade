/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** PacmanPlayer.hpp.h
*/

#ifndef PACMANPLAYER_HPP_
#define PACMANPLAYER_HPP_

#include "../../GameObject/GameObject.hpp"
#include "../PacmanMap/PacmanMap.hpp"

namespace Game
{
    class PacmanPlayer : public GameObject {
      public:
        enum class Direction {
            UP = 0,
            RIGHT = 1,
            DOWN = 2,
            LEFT = 3,
            IDLE = 4
        };

      private:
        Direction _dir;
        PacmanMap *_map;
        double _speed;
        double *_speedCoef;

        bool isCollideWithMap(Vector const& offset);

      public:
        PacmanPlayer();
        virtual ~PacmanPlayer();

        void move();
        void reset();

        void setDirection(Direction dir);
        void setSpeedCoef(double &speedCoef);

        void setMap(PacmanMap &map);

        Vector getPosition() const;
    };
} // namespace Game

#endif // PACMANPLAYER_HPP_
