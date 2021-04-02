/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SolarFoxGameModule.cpp.cc
*/

#include "SolarFoxGameModule.hpp"
#include "../../../includes/IDisplayModule.hpp"

using namespace Game;

const Color c = Color::BLUE;

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

static const std::deque<Vector> PATTERN_EASY = {{7, 7}, {12, 7}, {17, 7}, {22, 7}, {27, 7}, {32, 7},
    {7, 12}, {12, 12}, {17, 12}, {22, 12}, {27, 12}, {32, 12},
    {7, 17}, {12, 17}, {17, 17}, {22, 17}, {27, 17}, {32, 17},
    {7, 22}, {12, 22}, {17, 22}, {22, 22}, {27, 22}, {32, 22},
    {7, 27}, {12, 27}, {17, 27}, {22, 27}, {27, 27}, {32, 27},
    {7, 32}, {12, 32}, {17, 32}, {22, 32}, {27, 32}, {32, 32}};

static const std::deque<Vector> PATTERN_MEDIUM = {{7, 9}, {12, 5}, {17, 9}, {22, 5}, {27, 9}, {32, 5},
    {7, 14}, {12, 10}, {17, 14}, {22, 10}, {27, 14}, {32, 10},
    {7, 19}, {12, 15}, {17, 19}, {22, 15}, {27, 19}, {32, 15},
    {7, 24}, {12, 20}, {17, 24}, {22, 20}, {27, 24}, {32, 20},
    {7, 29}, {12, 25}, {17, 29}, {22, 25}, {27, 29}, {32, 25},
    {7, 34}, {12, 30}, {17, 34}, {22, 30}, {27, 34}, {32, 30}};

static const std::deque<Vector> PATTERN_HARD = {{9, 9}, {10, 5}, {19, 9}, {20, 5}, {29, 9}, {30, 5},
    {5, 14}, {14, 10}, {15, 14}, {24, 10}, {25, 14}, {34, 10},
    {9, 19}, {10, 15}, {19, 19}, {20, 15}, {29, 19}, {30, 15},
    {5, 24}, {14, 20}, {15, 24}, {24, 20}, {25, 24}, {34, 20},
    {9, 29}, {10, 25}, {19, 29}, {20, 25}, {29, 29}, {30, 25},
    {5, 34}, {14, 30}, {15, 34}, {24, 30}, {25, 34}, {34, 30}};

static const clock_t LOOP_FREQ = 10;

SolarFoxGameModule::SolarFoxGameModule()
try : AbstractGameModule("Unknown", LOOP_FREQ, MAP_SIZE, MAP), _player(MAP_SIZE),
_difficulty(Difficulty::EASY) {
    srand((unsigned) time(nullptr));
    this->generateCoin();
    this->generateEnemies();
} catch (BaseException const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
}

SolarFoxGameModule::~SolarFoxGameModule() {}

void SolarFoxGameModule::reset()
{
    try {
        _goodCoins.clear();
        _badCoins.clear();
        _enemies.clear();
        _difficulty = Difficulty::EASY;
        this->generateCoin();
        this->generateEnemies();
        this->_player.reset();
        this->_status = GameStatus::SUCCESS;
    } catch (BaseException const &e) {
        std::cerr << "Error: SolarFoxGameModule::reset() " << e.what()
                  << std::endl;
    }
}

void SolarFoxGameModule::eventManager(arcade::IDisplayModule &displayModule)
{
    AbstractGameModule::eventManager(displayModule);
    if (displayModule.isKeyPress(KeyList::ARROW_LEFT))
        this->_player.setMovment(SolarFoxPlayer::Direction::LEFT);
    if (displayModule.isKeyPress(KeyList::ARROW_RIGHT))
        this->_player.setMovment(SolarFoxPlayer::Direction::RIGHT);
    if (displayModule.isKeyPress(KeyList::ARROW_UP))
        this->_player.setMovment(SolarFoxPlayer::Direction::UP);
    if (displayModule.isKeyPress(KeyList::ARROW_DOWN))
        this->_player.setMovment(SolarFoxPlayer::Direction::DOWN);
    if (displayModule.isKeyPress(KeyList::KEY_S)
    && this->_player.getMovePeriod() == 10)
        this->_player.setMovePeriod((clock_t) 1);
    else if (displayModule.isKeyPress(KeyList::KEY_S)
    && this->_player.getMovePeriod() == 1)
        this->_player.setMovePeriod((clock_t) 10);
    if (displayModule.isKeyPress(KeyList::KEY_SPACE))
        this->_player.prepareShooting();
}

void SolarFoxGameModule::refreshGame()
{
    ssize_t coinIdx;

    // Player Move
    try {
        this->_player.move();
    } catch (OutOfBoundException const &e) {
        this->_status = GameStatus::GAMEOVER;
        return;
    }
    // Player Shoot
    this->_player.shoot(MAP_SIZE);
    // Check Collision With Border
    if (this->_player.isOutsideOfWalkableArea()) {
        this->_status = GameStatus::GAMEOVER;
        return;
    }
    // Check Collision With Coins
    coinIdx = this->_player.isShootCollideWith(_goodCoins);
    if (coinIdx != -1) {
        delete *(_goodCoins.begin() + coinIdx);
        _goodCoins.erase(_goodCoins.begin() + coinIdx);
        this->increaseScore(10);
        if (_goodCoins.empty()) {
            updateDifficulty();
            this->generateCoin();
            this->generateEnemies();
        }
    }
    if (this->_player.isShootCollideWith(_badCoins) != -1) {
        this->_status = GameStatus::GAMEOVER;
        return;
    }
    // Check Collision With Enemies Projectile
    try {
        this->_player.isCollideWith(_enemies);
    } catch (ShootException const &e) {
        this->_status = GameStatus::GAMEOVER;
        return;
    }
    // Handle Enemies
    for (size_t i = 0; i < _enemies.size(); i++) {
        this->_enemies[i]->move();
        this->_enemies[i]->shoot(MAP_SIZE);
        this->_enemies[i]->updateMovment();
    }
    // Display
    this->_map.display(*this->_graphModule);
    this->_player.display(*this->_graphModule);
    for (size_t i = 0; i < _goodCoins.size(); i++)
        this->_goodCoins[i]->display(*this->_graphModule);
    for (size_t i = 0; i < _badCoins.size(); i++)
        this->_badCoins[i]->display(*this->_graphModule);
    for (size_t i = 0; i < _enemies.size(); i++)
        this->_enemies[i]->display(*this->_graphModule);
}

void SolarFoxGameModule::updateDifficulty()
{
    if (_difficulty == Difficulty::EASY) {
        _difficulty = Difficulty::MEDIUM;
        return;
    }
    if (_difficulty == Difficulty::MEDIUM)
        _difficulty = Difficulty::HARD;
}

void SolarFoxGameModule::generateCoin()
{
    std::deque<Vector> pattern = {};

    if (_difficulty == Difficulty::EASY)
        pattern = PATTERN_EASY;
    if (_difficulty == Difficulty::MEDIUM)
        pattern = PATTERN_MEDIUM;
    if (_difficulty == Difficulty::HARD)
        pattern = PATTERN_HARD;
    for (size_t i = 0; i < pattern.size(); i++) {
        if (rand() % 100 < 95) {
            this->_goodCoins.push_back(new GameObject(Color::YELLOW, _map.getSize()));
            this->_goodCoins.back()->setPosition(pattern[i]);
            this->_goodCoins.back()->setAnimation(Color::GREEN, 500000);
        } else {
            this->_badCoins.push_back(new GameObject(Color::YELLOW, _map.getSize()));
            this->_badCoins.back()->setPosition(pattern[i]);
            this->_badCoins.back()->setAnimation(Color::RED, 500000);
        }
    }
}

void SolarFoxGameModule::generateEnemies()
{
    if (_difficulty == Difficulty::EASY) {
        this->_enemies.push_back(new SolarFoxEnemy(_map.getSize(), {2, 1}, SolarFoxEnemy::Direction::RIGHT));
        this->_enemies.back()->setPosition({2, 1});
    }
    if (_difficulty == Difficulty::MEDIUM) {
        this->_enemies.push_back(new SolarFoxEnemy(_map.getSize(), {2, 38}, SolarFoxEnemy::Direction::RIGHT));
        this->_enemies.back()->setPosition({2, 38});
    }
    if (_difficulty == Difficulty::HARD && _enemies.size() != 4) {
        this->_enemies.push_back(new SolarFoxEnemy(_map.getSize(), {1, 2}, SolarFoxEnemy::Direction::DOWN));
        this->_enemies.back()->setPosition({1, 2});
        this->_enemies.push_back(new SolarFoxEnemy(_map.getSize(), {38, 37}, SolarFoxEnemy::Direction::UP));
        this->_enemies.back()->setPosition({38, 37});
    }
}