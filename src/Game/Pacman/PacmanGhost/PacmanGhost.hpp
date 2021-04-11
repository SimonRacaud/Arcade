/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** PacmanGhost.hpp
*/

#ifndef PACMANGHOST_HPP_
#define PACMANGHOST_HPP_

#include "Vector.hpp"
#include "../../GameObject/GameObject.hpp"
#include "../PacmanDriver/PacmanDriver.hpp"
#include "../PacmanMap/PacmanMap.hpp"
#include "Timer/Timer.hpp"
#include <unordered_map>
#include <queue>

namespace Game
{
    typedef arcade::IDisplayModule::Color Color;

    class PacmanGhost : public GameObject {
      public:
        enum class State { HUNT, FLEE, IDLE, DEATH };
        enum Skin { DEFAULT, DEATH, FLEE };
        enum class Collision { KILLED, KILLER, NONE };

        static std::unordered_map<Skin, Color> COLOR;

        PacmanGhost(arcade::Vector initPosition, arcade::Vector const &mapSize);
        virtual ~PacmanGhost();

        void move(arcade::Vector target, PacmanMap const& map);

        void reset();

        Vector getPosition() const;

        void enableFlee();
        void kill();

        Collision isCollideWithPlayer(GameObject const& player);

      protected:
        void moveHunt(arcade::Vector target, PacmanMap const& map);
        void moveFlee(arcade::Vector target, PacmanMap const& map);
        void moveDeath(PacmanMap const& map);

        void processStateSwitch();
        void setStateTimeout(clock_t duration, State next, bool now);

        void setSkin(Skin skin);

        void resetStateQueue();
      private:
        arcade::Vector _homePosition;
        double _speed;
        State _status;
        Timer _timer;
        PacmanDriver _driver;
        std::queue<State> _stateQueue;
        std::queue<clock_t> _durationQueue;
    };
} // namespace Game

#endif // PACMANGHOST_HPP_
