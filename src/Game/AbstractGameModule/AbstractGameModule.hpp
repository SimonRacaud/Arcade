/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** AbstractGameModule.hpp.h
*/

#ifndef ABSTRACTGAMEMODULE_HPP_
#define ABSTRACTGAMEMODULE_HPP_

#include <deque>
#include <iostream>
#include "Game/GameMap/GameMap.hpp"
#include "Game/GameObject/GameObject.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "ModuleException.hpp"

namespace Game
{
    typedef arcade::IDisplayModule::Color Color;
    typedef arcade::Coord Coord;
    typedef arcade::GameStatus GameStatus;

    class AbstractGameModule : public arcade::IGameModule {
      public:
        AbstractGameModule(std::string const& username, Vector const &mapSize);
        AbstractGameModule(std::string const& username, Vector const &mapSize,
            std::deque<Color> const &map);
        virtual ~AbstractGameModule() = default;

        GameStatus getStatus() const;
        void setStatus(GameStatus status);

        virtual void refresh();
        virtual void reset() = 0;

        virtual size_t getScore() const;
        virtual size_t getScoreHigh() const;

        void setUsername(std::string const &username);

        const arcade::IDisplayModule &getDisplayModule() const;
        void setDisplayModule(arcade::IDisplayModule &displayModule);

      protected:
        void refreshEndMenu();
        void refreshPauseMenu();

        virtual void refreshGame() = 0;

        void increaseScore(size_t val);
        void evalHighScore();

        GameStatus _status;
        size_t _score;
        size_t _highScore;
        std::string _username;
        arcade::IDisplayModule *_graphModule;
        GameMap _map;
    };
} // namespace Game

#endif // ABSTRACTGAMEMODULE_HPP_
