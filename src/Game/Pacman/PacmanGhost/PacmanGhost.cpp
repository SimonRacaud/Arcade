/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** PacmanGhost.cpp.cc
*/

#include "PacmanGhost.hpp"

using namespace Game;

const double INIT_SPEED = 0.5;
const clock_t IDLE_TIMEOUT = 10000;
const clock_t INIT_FLEE_TIMEOUT = 3000;
const clock_t FLEE_TIMEOUT = 10000;

std::unordered_map<PacmanGhost::Skin, Color> PacmanGhost::COLOR = {
    {DEFAULT, Color::RED}, {FLEE, Color::BLUE}, {DEATH, Color::MAGENTA}};

Game::PacmanGhost::PacmanGhost(
    arcade::Vector initPosition, arcade::Vector const &mapSize)
    : GameObject(PacmanGhost::COLOR[Skin::DEFAULT], mapSize),
      _homePosition(initPosition), _speed(INIT_SPEED), _status(State::IDLE)
{
    this->setPosition(initPosition);
    this->setStateTimeout(IDLE_TIMEOUT, State::FLEE, true);
    this->setStateTimeout(INIT_FLEE_TIMEOUT, State::HUNT, false);
}

Game::PacmanGhost::~PacmanGhost()
{
}

void PacmanGhost::reset()
{
    this->_speed = INIT_SPEED;
    _status = State::IDLE;
    this->setPosition(_homePosition);
    this->setSkin(Skin::DEFAULT);
    this->resetStateQueue();
    this->setStateTimeout(IDLE_TIMEOUT, State::FLEE, true);
    this->setStateTimeout(INIT_FLEE_TIMEOUT, State::HUNT, false);
}

void Game::PacmanGhost::move(arcade::Vector target, PacmanMap const &map)
{
    try {
        if (_status == State::HUNT) {
            this->moveHunt(target, map);
        } else if (_status == State::FLEE) {
            this->moveFlee(target, map);
        } else if (_status == State::DEATH) {
            this->moveDeath(map);
        }
        this->processStateSwitch();
    } catch (OutOfBoundException const &e) {
        std::cerr << "Ghost out of bound\n"; // DEBUG
    }
}

void PacmanGhost::enableFlee()
{
    this->resetStateQueue();
    this->setStateTimeout(FLEE_TIMEOUT, State::HUNT, true);
    this->_status = State::FLEE;
    this->setSkin(Skin::FLEE);
    this->_speed = 0.25;
}

void PacmanGhost::kill()
{
    this->resetStateQueue();
    this->_status = State::DEATH;
    this->setSkin(Skin::DEATH);
}

Vector PacmanGhost::getPosition() const
{
    return this->_positions[0];
}

/* Private */

void PacmanGhost::resetStateQueue()
{
    while (!_durationQueue.empty())
        this->_durationQueue.pop();
    while (!_stateQueue.empty())
        this->_stateQueue.pop();
}

void Game::PacmanGhost::moveHunt(arcade::Vector target, PacmanMap const &map)
{
    arcade::Vector pos =
        _driver.getStepTowardTarget(target, this->getPosition(), _speed, map);

    this->setPosition(pos);
}

void Game::PacmanGhost::moveFlee(arcade::Vector target, PacmanMap const &map)
{
    arcade::Vector pos =
        _driver.getStepAgainstTarget(target, this->getPosition(), _speed, map);

    this->setPosition(pos);
}

void Game::PacmanGhost::moveDeath(PacmanMap const &map)
{
    arcade::Vector pos = _driver.getStepTowardTarget(
        _homePosition, this->getPosition(), _speed, map);

    if (pos.x == _homePosition.x && pos.y == _homePosition.y) {
        this->_status = State::IDLE;
        this->setStateTimeout(IDLE_TIMEOUT, State::FLEE, true);
        this->setStateTimeout(INIT_FLEE_TIMEOUT, State::HUNT, false);
    }
    this->setPosition(pos);
}

void Game::PacmanGhost::setSkin(Skin skin)
{
    this->_color = PacmanGhost::COLOR[skin];
    this->_animColor[0] = this->_color;
}

void Game::PacmanGhost::setStateTimeout(clock_t duration, State next, bool now)
{
    this->_stateQueue.push(next);
    if (now) {
        this->_timer.setTimeout(duration);
    } else {
        this->_durationQueue.push(duration);
    }
}

void PacmanGhost::processStateSwitch()
{
    if (_timer.isTimeout()) {
        if (_stateQueue.empty() == false) {
            _status = _stateQueue.front();
            _stateQueue.pop();
        }
        if (_status == State::HUNT || _status == State::IDLE) {
            this->setSkin(Skin::DEFAULT);
            this->_speed = INIT_SPEED;
        }
        if (_durationQueue.empty() == false) {
            this->_timer.setTimeout(_durationQueue.front());
            _durationQueue.pop();
        }
    }
}

PacmanGhost::Collision PacmanGhost::isCollideWithPlayer(const GameObject &player)
{
    bool collide = player.isCollideToCase(this->getPosition());

    if (collide && _status == State::FLEE) {
        this->kill();
        return Collision::KILLED;
    } else if (collide && _status == State::HUNT) {
        return Collision::KILLER;
    }
    return Collision::NONE;
}
