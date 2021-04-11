/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** PacmanMap.hpp.h
*/

#ifndef PACMANMAP_HPP_
#define PACMANMAP_HPP_

#include <deque>
#include "../../GameMap/GameMap.hpp"
#include "../../GameObject/GameObject.hpp"
#include <unordered_map>
#include "Game/Pacman/pacmanEnv.hpp"

namespace Game
{
    class PacmanMap : public GameMap {
      private:
        std::deque<GameObject *> _pacgums;
        std::deque<GameObject *> _superPacgums;

      public:
        enum class CoinCollision {NONE, COIN, SUPERCOIN};

        PacmanMap();
        virtual ~PacmanMap();

        void reset();

        CoinCollision isCollideCoin(GameObject &player);
        bool isCollideToCase(Vector coord) const;

        bool isCoinsEmpty() const;

      protected:
        void draw(arcade::IDisplayModule &mod) override;

        void loadMap(Vector const &size, std::deque<Color> const &fill);

        void destroyPacgums();
    };
} // namespace Game

#endif // PACMANMAP_HPP_
