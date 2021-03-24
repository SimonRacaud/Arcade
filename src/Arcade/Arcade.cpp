/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Arcade.cpp.cc
*/

#include "Arcade.hpp"

using namespace arcade;

const std::deque<std::string> Arcade::GAME_LIB_NAMES = {
    "arcade_nibbler.so", "arcade_pacman.so"};

const std::deque<std::string> Arcade::GRAPHIC_LIB_NAMES = {
    "arcade_sfml.so", "arcade_ncurses.so", "arcade_sdl2.so"};

Arcade::Arcade(const std::string &defGraphicFile)
    : _username("unknown"), _status(ExitStatus::LOOP), _selectedGame(nullptr),
      _selectedGraphic(nullptr), _graphLibManager("./lib"),
      _gameLibManager("./lib"), _timer(CORE_TIMER)
{
    try {
        this->_gameLibManager.fetchAvailableLibs(Arcade::GAME_LIB_NAMES);
        this->_graphLibManager.fetchAvailableLibs(Arcade::GRAPHIC_LIB_NAMES);
        try {
            IDisplayModule &displayMod =
                this->_graphLibManager.getModule(defGraphicFile);
            this->_selectedGraphic = &displayMod;
            this->_selectedGraphic->open();
        } catch (LibNotFoundException const &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            this->_status = ExitStatus::ERROR;
            return;
        }
    } catch (LibLoadingException const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        this->_status = ExitStatus::ERROR;
    }
}

Arcade::~Arcade()
{
    if (this->_selectedGraphic) {
        this->_selectedGraphic->close();
    }
}

void Arcade::loop()
{
    while (this->_status == ExitStatus::LOOP) {
        if (this->_timer.shouldRefresh()) {
            if (this->_selectedGraphic) {
                this->_selectedGraphic->clearScreen();
            }
            if (this->_selectedGame == nullptr) {
                // TODO: main menu
            } else {
                this->_selectedGame->refresh();
            }
            if (this->_selectedGraphic) {
                if (this->_selectedGraphic->isOpen() == false) {
                    this->_status = ExitStatus::SUCCESS;
                } else {
                    this->_selectedGraphic->refreshScreen();
                    this->_selectedGraphic->displayScreen();
                }
            }
        }
    }
}

void Arcade::resetGame()
{
    if (this->_selectedGame != nullptr) {
       this->_selectedGame->reset();
    }
}

void Arcade::setUsername(const std::string &username)
{
    this->_username = username;
    if (this->_selectedGame != nullptr) {
        this->_selectedGame->setUsername(username);
    }
}

std::string const &Arcade::getUsername() const
{
    return _username;
}

/* Private */

void Arcade::selectGame(std::string const &name)
{
    try {
        IGameModule &gameMod = this->_gameLibManager.getModule(name);
        if (this->_selectedGame != nullptr)
            this->_selectedGame->reset();
        this->_selectedGame = &gameMod;
        this->_selectedGame->setUsername(this->getUsername());
        if (this->_selectedGraphic)
            this->_selectedGame->setDisplayModule(*this->_selectedGraphic);
        else
            std::cerr
                << "Warning: Arcade::selectGame no selected graphic module"
                << std::endl;
    } catch (LibNotFoundException const &e) {
        std::cerr << "Arcade::selectGame Error: " << e.what() << std::endl;
    }
}

void Arcade::gotoMainMenu()
{
    if (this->_selectedGame == nullptr)
        return;
    this->_selectedGame = nullptr;
    // TODO : open main menu
}

void Arcade::selectGraphic(std::string const &name)
{
    try {
        IDisplayModule &displayMod = this->_graphLibManager.getModule(name);
        if (this->_selectedGraphic)
            this->_selectedGraphic->close();
        this->_selectedGraphic = &displayMod;
        this->_selectedGraphic->open();
    } catch (LibNotFoundException const &e) {
        std::cerr << "Arcade::selectGraphic : " << e.what() << std::endl;
    }
}