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

static const clock_t COIN_GEN_PERIOD = 5000;
static const size_t COIN_LIMIT = 10;

static const clock_t LOOP_FREQ = 200;

NibblerGameModule::NibblerGameModule()
try : AbstractGameModule("Unknown", LOOP_FREQ, MAP_SIZE, MAP),
    _player(MAP_SIZE), _coinGenTimer(COIN_GEN_PERIOD) {
    srand((unsigned) time(nullptr));
    this->generateCoin();
} catch (BaseException const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
}

NibblerGameModule::~NibblerGameModule()
{
    while (!_coins.empty()) {
        delete _coins.back();
        _coins.pop_back();
    }
}

void NibblerGameModule::refreshGame(bool refreshActions)
{
    if (refreshActions) {
        this->refreshLogic();
    }
    this->_map.display(*this->_graphModule);
    this->_player.display(*this->_graphModule);
    for (size_t i = 0; i < _coins.size(); i++) {
        this->_coins[i]->display(*this->_graphModule);
    }
    if (refreshActions) {
        if (_coins.size() < COIN_LIMIT && this->_coinGenTimer.shouldRefresh()) {
            this->generateCoin();
        }
    }
}

void NibblerGameModule::refreshLogic()
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
        delete *(_coins.begin() + coinIdx);
        _coins.erase(_coins.begin() + coinIdx);
        this->increaseScore(10);
        this->_player.increaseLength();
        if (_coins.empty()) {
            this->generateCoin();
        }
    }
}


void NibblerGameModule::reset()
{
    try {
        _coins.clear();
        this->generateCoin();
        this->_player.reset();
        this->_status = GameStatus::SUCCESS;
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
        position.x = (rand() % (size_t) mapSize.x);
        position.y = (rand() % (size_t) mapSize.y);
        if (_player.isCollideCoord(position)) {
            continue;
        }
        for (GameObject const *coin : _coins) {
            if (coin->isCollideCoord(position) == true) {
                continue;
            }
        }
        this->_coins.push_back(new GameObject(Color::YELLOW, _map.getSize()));
        this->_coins.back()->setPosition(position);
        this->_coins.back()->setAnimation(Color::BLUE, 4);
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