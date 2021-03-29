/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** PacmanMap.cpp.cc
*/

#include "PacmanMap.hpp"

using namespace Game;

static const double SUPER_GUM_ANIM_FREQ = 2;

#define F Color::BLACK
#define W Color::WHITE
#define D Color::MAGENTA
#define G Color::YELLOW
#define S Color::GREEN
#define SG Color::YELLOW

static const std::deque<Color> BASE_MAP = {
    F,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,F,
    F,W,G,G,G,G,G,G,G,G,W,G,G,G,G,G,G,G,G,W,F,
    F,W,S,W,W,G,W,W,W,G,W,G,W,W,W,G,W,W,S,W,F,
    F,W,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,W,F,
    F,W,G,W,W,G,W,G,W,W,W,W,W,G,W,G,W,W,G,W,F,
    F,W,G,G,G,G,W,G,G,G,W,G,G,G,W,G,G,G,G,W,F,
    F,W,W,W,W,G,W,W,W,F,W,F,W,W,W,G,W,W,W,W,F,
    F,F,F,F,W,G,W,F,F,F,F,F,F,F,W,G,W,F,F,F,F,
    W,W,W,W,W,G,W,F,W,W,D,W,W,F,W,G,W,W,W,W,W,
    F,F,F,F,F,G,F,F,W,F,F,F,W,F,F,G,F,F,F,F,F,
    W,W,W,W,W,G,W,F,W,W,W,W,W,F,W,G,W,W,W,W,W,
    F,F,F,F,W,G,W,F,F,F,F,F,F,F,W,G,W,F,F,F,F,
    F,W,W,W,W,G,W,F,W,W,W,W,W,F,W,G,W,W,W,W,F,
    F,W,G,G,G,G,G,G,G,G,W,G,G,G,G,G,G,G,G,W,F,
    F,W,G,W,W,G,W,W,W,G,W,G,W,W,W,G,W,W,G,W,F,
    F,W,S,G,W,G,G,G,G,G,G,G,G,G,G,G,W,G,S,W,F,
    F,W,W,G,W,G,W,G,W,W,W,W,W,G,W,G,W,G,W,W,F,
    F,W,G,G,G,G,W,G,G,G,W,G,G,G,W,G,G,G,G,W,F,
    F,W,G,W,W,W,W,W,W,G,W,G,W,W,W,W,W,W,G,W,F,
    F,W,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,W,F,
    F,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,F,
};

static const std::deque<Color> COLLIDE_COLOR = {W, D};

Game::PacmanMap::PacmanMap() : GameMap(MAP_SIZE)
{
    this->setCollideColors(COLLIDE_COLOR);
    this->loadMap(MAP_SIZE, BASE_MAP);
}

Game::PacmanMap::~PacmanMap()
{
    while (this->_pacgums.empty() == false) {
        delete this->_pacgums.back();
        this->_pacgums.pop_back();
    }
    while (this->_superPacgums.empty() == false) {
        delete this->_superPacgums.back();
        this->_superPacgums.pop_back();
    }
}

void Game::PacmanMap::draw(arcade::IDisplayModule &mod)
{
    for (GameObject *obj : _pacgums)  {
        obj->display(mod);
    }
    for (GameObject *obj : _superPacgums)  {
        obj->display(mod);
    }
}

void Game::PacmanMap::loadMap(
    Vector const &size, std::deque<Color> const &fill)
{
    size_t idx = 0;

    this->_mtx = new Color *[(size_t) size.y];
    for (size_t y = 0; y < (size_t) size.y; y++) {
        this->_mtx[y] = new Color[(size_t) size.x];
        for (size_t x = 0; x < (size_t) size.x; x++) {
            if (fill.size() > idx) {
                if (fill[idx] == G) {
                    // Set pacgum
                    this->_mtx[y][x] = F;
                    this->_pacgums.push_back(new GameObject(fill[idx++], size));
                    this->_pacgums.back()->setPosition(Vector(x, y));
                } else if (fill[idx] == S) {
                    // Set super pacgum
                    this->_mtx[y][x] = F;
                    this->_superPacgums.push_back(new GameObject(fill[idx++], size));
                    this->_superPacgums.back()->setPosition(Vector(x, y));
                    this->_superPacgums.back()->setAnimation(SG, SUPER_GUM_ANIM_FREQ);
                } else {
                    // Set colored case
                    this->_mtx[y][x] = fill[idx++];
                }
            } else {
                this->_mtx[y][x] = F;
            }
        }
    }
}

void PacmanMap::reset()
{
    GameMap::~GameMap();
    this->~PacmanMap();
    this->loadMap(MAP_SIZE, BASE_MAP);
}

size_t PacmanMap::processCoinCollision(GameObject &player)
{
    size_t score = 0;

    for (auto it = _pacgums.begin(); it != _pacgums.end(); it++) {
        if ((*it)->isCollideWith(player)) {
            delete *it;
            _pacgums.erase(it);
            score += GUM_SCORE_INC;
            break;
        }
    }
    for (auto it = _superPacgums.begin(); it != _superPacgums.end(); it++) {
        if ((*it)->isCollideWith(player)) {
            delete *it;
            _superPacgums.erase(it);
            // timer
            score += SGUM_SCORE_INC;
            break;
        }
    }
    return score;
}
