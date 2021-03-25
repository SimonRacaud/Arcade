/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** NibblerGameModule.cpp.cc
*/

#include "NibblerGameModule.hpp"
#include "../../../includes/IDisplayModule.hpp"

using namespace Game;

const Color c = Color::WHITE;

static const std::deque<Color> MAP = {c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
    c, c, c, c, c, c, c, c, c, c, c};

NibblerGameModule::NibblerGameModule()
try : AbstractGameModule("Unknown", MAP_SIZE, MAP), _player(MAP_SIZE)
{
    srand((unsigned) time(nullptr));
    this->generateCoin();
} catch (BaseException const& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}

void NibblerGameModule::refreshGame()
{
    ssize_t coinIdx;

    // move player
    try {
        this->_player.move();
    } catch (OutOfBoundException const &e) {
        this->_status = GameStatus::GAMEOVER;
        return;
    }
    // check collision (game over)
    if (this->_player.isCollideWithSelf()) {
        this->_status = GameStatus::GAMEOVER;
        return;
    }
    // check collision coins
    coinIdx = this->_player.isCollideWith(_coins);
    if (coinIdx != -1) {
        _coins.erase(_coins.begin() + coinIdx);
        // TODO : increate score
        // TODO : increate snake size
        if (_coins.empty()) {
            this->generateCoin();
        }
    }
    this->_map.display(*this->_graphModule);
    this->_player.display(*this->_graphModule);
    for (size_t i = 0; i < _coins.size(); i++) {
        this->_coins[i].display(*this->_graphModule);
    }
}

void NibblerGameModule::reset()
{
    try {
        _coins.clear();
        this->generateCoin();
        // TODO: reset player
    } catch (BaseException const &e) {
        std::cerr << "Error: NibblerGameModule::reset() " << e.what()
                  << std::endl;
    }
}

void NibblerGameModule::generateCoin()
{
    Vector const &mapSize = _map.getSize();
    Vector position(0, 0);

    for (size_t i = 0; i < 20; i++) {
        position.x = (rand() % (size_t)mapSize.x);
        position.y = (rand() % (size_t)mapSize.y);
        if (_player.isCollideCoord(position)) {
            continue;
        }
        for (GameObject const &coin : _coins) {
            if (coin.isCollideCoord(position) == true) {
                continue;
            }
        }
        this->_coins.push_back(GameObject(Color::YELLOW, _map.getSize()));
        this->_coins.back().setPosition(position);
        this->_coins.back().setAnimation(Color::BLUE, 4);
        return;
    }
    std::cerr << "Warning: NibblerGameModule::generateCoin() fail"
              << std::endl;
}

void NibblerGameModule::eventManager(arcade::IDisplayModule &displayModule)
{
    AbstractGameModule::eventManager(displayModule);
    if (displayModule.isKeyPress(KeyList::ARROW_LEFT)) {
        this->_player.setMovment(NibblerPlayer::Direction::LEFT);
    }
    if (displayModule.isKeyPress(KeyList::ARROW_RIGHT)) {
        this->_player.setMovment(NibblerPlayer::Direction::RIGHT);
    }
    if (displayModule.isKeyPress(KeyList::ARROW_UP)) {
        this->_player.setMovment(NibblerPlayer::Direction::UP);
    }
    if (displayModule.isKeyPress(KeyList::ARROW_DOWN)) {
        this->_player.setMovment(NibblerPlayer::Direction::DOWN);
    }
}
