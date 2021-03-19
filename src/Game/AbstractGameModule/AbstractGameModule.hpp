/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** AbstractGameModule.hpp.h
*/

#ifndef ABSTRACTGAMEMODULE_HPP_
#define ABSTRACTGAMEMODULE_HPP_

#include "IGameModule.hpp"
#include "IDisplayModule.hpp"
#include "Game/GameMap/GameMap.hpp"
#include "Game/GameObject/GameObject.hpp"
#include "ModuleException.hpp"

namespace Game {
    class AbstractGameModule : public arcade::IGameModule {
    public:
        AbstractGameModule(std::string &username);
        virtual ~AbstractGameModule() = default;

        virtual void refresh() = 0;
        virtual void reset() = 0;

        virtual size_t getScore() const;
        virtual size_t getScoreHigh() const;

        void setUsername(std::string const& username);

        const arcade::IDisplayModule &getDisplayModule() const;
        void setDisplayModule(arcade::IDisplayModule &displayModule);

    protected:
        size_t _score;
        size_t _highScore;
        std::string &_username;
        arcade::IDisplayModule *_graphModule;
        GameMap *_map;
        std::deque<GameObject> _objs;
    };
}


#endif //ABSTRACTGAMEMODULE_HPP_
