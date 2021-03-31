/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Arcade.cpp.cc
*/

#include "Arcade.hpp"

using namespace arcade;

const std::deque<std::string> Arcade::GAME_LIB_NAMES = {
    "arcade_nibbler.so", "arcade_solarfox.so"};

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
            this->_selectedGraphicName = defGraphicFile;
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
                this->_selectedGraphic->refreshScreen();
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
                    this->_selectedGraphic->displayScreen();
                }
                this->eventManager();
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
        this->_selectedGameName = name;
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

void Arcade::selectGraphic(std::string const &name)
{
    try {
        IDisplayModule &displayMod = this->_graphLibManager.getModule(name);
        if (this->_selectedGraphic)
            this->_selectedGraphic->close();
        this->_selectedGraphic = &displayMod;
        this->_selectedGraphic->open();
        this->_selectedGraphicName = name;
        if (this->_selectedGame) {
            this->_selectedGame->setDisplayModule(displayMod);
        }
    } catch (LibNotFoundException const &e) {
        std::cerr << "Arcade::selectGraphic : " << e.what() << std::endl;
    }
}

Arcade::ExitStatus Arcade::getStatus() const
{
    return _status;
}

void Arcade::eventManager()
{
    if (this->_selectedGraphic == nullptr)
        return;
    if (_selectedGraphic->isKeyPress(Key::NEXT_GAME)) {
        this->rotateGameLib(false);
    }
    if (_selectedGraphic->isKeyPress(Key::PREV_GAME)) {
        this->rotateGameLib(true);
    }
    if (_selectedGraphic->isKeyPress(Key::NEXT_LIB)) {
        this->rotateGraphLib(false);
    }
    if (_selectedGraphic->isKeyPress(Key::PREV_LIB)) {
        this->rotateGraphLib(true);
    }
    if (_selectedGraphic->isKeyPress(Key::RESTART_GAME)) {
        this->resetGame();
    }
    if (_selectedGraphic->isKeyPress(Key::EXIT)) {
        this->_status = ExitStatus::SUCCESS;
    }
    if (_selectedGame && _selectedGraphic->isKeyPress(Key::MENU)) {
        this->gotoMainMenu();
    }
}

/** Private **/

void Arcade::gotoMainMenu()
{
    if (this->_selectedGame == nullptr)
        return;
    this->_selectedGame = nullptr;
    // TODO : open main menu
}

void Arcade::rotateGraphLib(bool rev)
{
    const std::deque<std::string> &libNames =
        this->_graphLibManager.getAvailableLibs();

    if (libNames.empty())
        return;
    if (_selectedGraphic == nullptr && !libNames.empty()) {
        this->selectGraphic(libNames.front());
    } else if (libNames.size() > 1) {
        std::string selectedName = this->_selectedGraphicName;
        auto it = std::find_if(libNames.begin(), libNames.end(),
            [selectedName](std::string const &name) {
                return name.find(selectedName) != std::string::npos;
            });
        if (it == libNames.end()) {
            std::cerr << "Warning: Arcade::rotateGraphLib() "
                      << _selectedGraphicName << " Lib not found\n";
            return;
        } else {
            if (rev) {
                if (it == libNames.end() - 1) {
                    this->selectGraphic(libNames.front());
                } else {
                    this->selectGraphic(*(it + 1));
                }
            } else {
                if (it == libNames.begin()) {
                    this->selectGraphic(libNames.back());
                } else {
                    this->selectGraphic(*(it - 1));
                }
            }
        }
    }
}

void Arcade::rotateGameLib(bool rev)
{
    const std::deque<std::string> &libNames =
        this->_gameLibManager.getAvailableLibs();

    if (libNames.empty())
        return;

    if (_selectedGame == nullptr && !libNames.empty()) {
        this->selectGame(libNames.front());
    } else if (libNames.size() > 1) {
        std::string selectedName = this->_selectedGameName;
        auto it = std::find_if(libNames.begin(), libNames.end(),
            [selectedName](std::string const &name) {
                return name.find(selectedName) != std::string::npos;
            });
        if (it == libNames.end()) {
            std::cerr << "Warning: Arcade::rotateGameLib() "
                      << _selectedGameName << " Lib not found\n";
            return;
        } else {
            if (rev) {
                if (it == libNames.end() - 1) {
                    this->selectGame(libNames.front());
                } else {
                    this->selectGame(*(it + 1));
                }
            } else {
                if (it == libNames.begin()) {
                    this->selectGame(libNames.back());
                } else {
                    this->selectGame(*(it - 1));
                }
            }
        }
    }
}
