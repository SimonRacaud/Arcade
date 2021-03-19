/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** AbstractGameModule.cpp.cc
*/

#include "AbstractGameModule.hpp"

using namespace Game;

AbstractGameModule::AbstractGameModule(std::string &username)
    : _score(0), _highScore(0), _username(username), _graphModule(nullptr),
      _map(nullptr)
{
}

size_t AbstractGameModule::getScore() const
{
    return _score;
}

size_t AbstractGameModule::getScoreHigh() const
{
    return _highScore;
}

void AbstractGameModule::setUsername(std::string const &username)
{
    this->_username = username;
}

/**
 * throw ModuleException
 * @return
 */
const arcade::IDisplayModule &AbstractGameModule::getDisplayModule() const
{
    if (this->_graphModule != nullptr)
        return *_graphModule;
    throw ModuleException();
}

void AbstractGameModule::setDisplayModule(
    arcade::IDisplayModule &displayModule)
{
    this->_graphModule = &displayModule;
}
