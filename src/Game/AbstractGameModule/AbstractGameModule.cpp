/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** AbstractGameModule.cpp.cc
*/

#include "AbstractGameModule.hpp"
#include "../../../includes/IDisplayModule.hpp"

using namespace Game;

AbstractGameModule::AbstractGameModule(
    std::string const& username, Vector const &mapSize)
    : _status(GameStatus::SUCCESS), _score(0), _highScore(0), _username(username),
      _graphModule(nullptr), _map(mapSize)
{
}

AbstractGameModule::AbstractGameModule(
    std::string const& username, Vector const &mapSize, std::deque<Color> const &map)
    : _status(GameStatus::SUCCESS), _score(0), _highScore(0), _username(username),
      _graphModule(nullptr), _map(mapSize, map)
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
    return *_graphModule;
}

void AbstractGameModule::setDisplayModule(
    arcade::IDisplayModule &displayModule)
{
    this->_graphModule = &displayModule;
}

GameStatus AbstractGameModule::getStatus() const
{
    return _status;
}

void AbstractGameModule::setStatus(GameStatus status)
{
    this->_status = status;
}

void AbstractGameModule::refresh()
{
    if (_graphModule == nullptr)
        return;
    try {
        if (_status == GameStatus::SUCCESS) {
            this->refreshGame();
        } else if (_status == GameStatus::GAMEOVER) {
            this->refreshEndMenu();
        } else if (_status == GameStatus::PAUSE) {
            this->refreshPauseMenu();
        }
        this->eventManager(*this->_graphModule);
    } catch (BaseException const& e) {
        this->_status = GameStatus::ERROR;
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "AbstractGameModule::refresh() An exception occured\n";
        this->_status = GameStatus::ERROR;
    }
}

/** Private/Protected **/

void AbstractGameModule::refreshEndMenu()
{
    if (_graphModule != nullptr) {
        Vector const &mapSize = _map.getSize();
        Coord posTitle(mapSize.x / 2 - 2, mapSize.y / 2);
        Coord posMsg(mapSize.x / 2 - 4, mapSize.y / 2 + 3);

        this->_graphModule->putText(Color::RED, posTitle, "GAME OVER");
        this->_graphModule->putText(
            Color::RED, posMsg, "press space to restart");
    }
}

void AbstractGameModule::refreshPauseMenu()
{
    if (_graphModule != nullptr) {
        Vector const &mapSize = _map.getSize();
        Coord posTitle(mapSize.x / 2 - 1, mapSize.y / 2);
        Coord posMsg(mapSize.x / 2 - 4, mapSize.y / 2 + 3);

        this->_graphModule->putText(Color::RED, posTitle, "PAUSE");
        this->_graphModule->putText(
            Color::RED, posMsg, "press space to continue");
    }
}

void AbstractGameModule::increaseScore(size_t val)
{
    this->_score += val;
}

void AbstractGameModule::evalHighScore()
{
    if (_score > _highScore) {
        _highScore = _score;
    }
}

void AbstractGameModule::eventManager(arcade::IDisplayModule &displayModule)
{
    if (displayModule.isKeyPress(KeyList::PAUSE)) {
        if (this->_status == GameStatus::PAUSE) {
            this->_status = GameStatus::SUCCESS;
        } else {
            this->_status = GameStatus::PAUSE;
        }
    }
    if (_status == GameStatus::GAMEOVER || _status == GameStatus::PAUSE) {
        if (displayModule.isKeyPress(KeyList::KEY_SPACE)) {
            if (_status == GameStatus::GAMEOVER) {
                this->reset();
            }
            this->_status = GameStatus::SUCCESS;
        }
    }
}
