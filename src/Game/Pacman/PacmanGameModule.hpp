/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** PacmanGameModule.hpp.h
*/

#ifndef PACMANGAMEMODULE_HPP_
#define PACMANGAMEMODULE_HPP_

#include "../AbstractGameModule/AbstractGameModule.hpp"
#include "./PacmanMap/PacmanMap.hpp"
#include "./PacmanPlayer/PacmanPlayer.hpp"
#include "pacmanEnv.hpp"
#include "./PacmanGhost/PacmanGhost.hpp"
#include <memory>

namespace Game
{
    class PacmanGameModule : public AbstractGameModule {
      private:
        double _speedCoef;
        PacmanPlayer _player;
        PacmanMap _map;
        std::deque<std::shared_ptr<PacmanGhost>> _ghosts;

      public:
        PacmanGameModule();
        virtual ~PacmanGameModule();

        void reset() override;

        bool isEndGame() const;

      protected:
        void refreshGame(bool refreshActions) override;
        void nextStage();
        virtual void eventManager(arcade::IDisplayModule &displayModule);

        void coinsCollision();
        void ghostsCollision();
    };
}

#endif // PACMANGAMEMODULE_HPP_
