/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** PacmanGameModule.cpp.cc
*/

#include "PacmanGameModule.hpp"

using namespace Game;

static const size_t DEF_SPEED_COEF = 1;

PacmanGameModule::PacmanGameModule()
    : AbstractGameModule("unknown", PACMAN_FREQ, MAP_SIZE),
      _speedCoef(DEF_SPEED_COEF)
{
    this->_player.setSpeedCoef(_speedCoef);
    this->_player.setMap(_map);

    this->_ghosts.push_back(std::make_shared<PacmanGhost>((Vector){9, 9}, MAP_SIZE));
    this->_ghosts.push_back(std::make_shared<PacmanGhost>((Vector){10, 9}, MAP_SIZE));
    this->_ghosts.push_back(std::make_shared<PacmanGhost>((Vector){11, 9}, MAP_SIZE));
    this->_ghosts.push_back(std::make_shared<PacmanGhost>((Vector){10, 7}, MAP_SIZE));
}

PacmanGameModule::~PacmanGameModule()
{
}

void PacmanGameModule::reset()
{
    this->_player.reset();
    this->_map.reset();
    for (auto &ghost : _ghosts) {
        ghost->reset();
    }
}

/** Private **/

void PacmanGameModule::refreshGame(bool refreshActions)
{
    if (refreshActions) {
        this->_player.move();
        this->coinsCollision();
        for (auto const &ghost : _ghosts) {
            ghost->move(this->_player.getPosition(), _map);
        }
        this->ghostsCollision();
        if (this->isEndGame()) {
            this->nextStage();
        }
    }
    this->_map.display(*this->_graphModule);
    this->_player.display(*this->_graphModule);
    for (auto const &ghost : _ghosts) {
        ghost->display(*this->_graphModule);
    }
}

void PacmanGameModule::nextStage()
{
    this->reset();
    this->_speedCoef += 0.2;
}

void PacmanGameModule::eventManager(arcade::IDisplayModule &displayModule)
{
    AbstractGameModule::eventManager(displayModule);
    if (displayModule.isKeyPress(KeyList::ARROW_LEFT)) {
        this->_player.setDirection(PacmanPlayer::Direction::LEFT);
    }
    if (displayModule.isKeyPress(KeyList::ARROW_RIGHT)) {
        this->_player.setDirection(PacmanPlayer::Direction::RIGHT);
    }
    if (displayModule.isKeyPress(KeyList::ARROW_UP)) {
        this->_player.setDirection(PacmanPlayer::Direction::UP);
    }
    if (displayModule.isKeyPress(KeyList::ARROW_DOWN)) {
        this->_player.setDirection(PacmanPlayer::Direction::DOWN);
    }
}

void PacmanGameModule::coinsCollision()
{
    PacmanMap::CoinCollision collision = _map.isCollideCoin(_player);

    if (collision == PacmanMap::CoinCollision::COIN) {
        this->increaseScore(GUM_SCORE_INC);
    } else if (collision == PacmanMap::CoinCollision::SUPERCOIN) {
        this->increaseScore(SGUM_SCORE_INC);
        for (auto &ghost : _ghosts) {
            ghost->enableFlee();
        }
    }
}

void PacmanGameModule::ghostsCollision()
{
    for (auto &ghost : _ghosts) {
        PacmanGhost::Collision collision = ghost->isCollideWithPlayer(_player);
        if (collision == PacmanGhost::Collision::KILLED) {
            this->increaseScore(KILL_SCORE_INC);
        } else if (collision == PacmanGhost::Collision::KILLER) {
            this->setStatus(GameStatus::GAMEOVER);
        }
    }
}

bool PacmanGameModule::isEndGame() const
{
    return _map.isCoinsEmpty();
}
