/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** CoreConfig
*/

#include "CoreConfig.hpp"

using namespace arcade;

const std::deque<std::string> CoreConfig::GAME_LIB_NAMES = {
    "arcade_nibbler.so", "arcade_pacman.so"};

const std::deque<std::string> CoreConfig::GRAPHIC_LIB_NAMES = {
    "arcade_sfml.so", "arcade_ncurses.so", "arcade_sdl2.so"};

CoreConfig::CoreConfig(const std::string &defGraphicFile) :
    _username("unknow"), _status(ExitStatus::LOOP), _selectedGame(nullptr),
    _selectedGraphic(nullptr), _graphLibManager("./lib"),
    _gameLibManager("./lib")
{
    try {
        this->_gameLibManager.fetchAvailableLibs(CoreConfig::GAME_LIB_NAMES);
        this->_graphLibManager.fetchAvailableLibs(CoreConfig::GRAPHIC_LIB_NAMES);
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

CoreConfig::~CoreConfig()
{
}

void CoreConfig::reloadLib()
{
    this->_gameLibManager.fetchAvailableLibs(CoreConfig::GAME_LIB_NAMES);
    this->_graphLibManager.fetchAvailableLibs(CoreConfig::GRAPHIC_LIB_NAMES);
}

void CoreConfig::resetGame()
{
    if (this->_selectedGame != nullptr) {
        this->_selectedGame->reset();
    }
}

void CoreConfig::setUsername(std::string const &username)
{
    this->_username = username;
    if (this->_selectedGame != nullptr) {
        this->_selectedGame->setUsername(username);
    }
}

std::string const &CoreConfig::getUsername() const
{
    return _username;
}

void CoreConfig::selectGame(std::string const &name)
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
                << "Warning: CoreConfig::selectGame no selected graphic module"
                << std::endl;
    } catch (LibNotFoundException const &e) {
        std::cerr << "CoreConfig::selectGame Error: " << e.what() << std::endl;
    }
}

void CoreConfig::selectGraphic(std::string const &name)
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
        std::cerr << "CoreConfig::selectGraphic : " << e.what() << std::endl;
    }
}

CoreConfig::ExitStatus CoreConfig::getStatus() const
{
    return _status;
}

void CoreConfig::setStatus(ExitStatus const status)
{
    _status = status;
}

IGameModule *CoreConfig::getSelectedGame()
{
    return _selectedGame;
}

IDisplayModule *CoreConfig::getSelectedGraphic()
{
    return _selectedGraphic;
}

std::deque<std::string> CoreConfig::getGameNames()
{
    return GAME_LIB_NAMES;
}

std::deque<std::string> CoreConfig::getGraphicNames()
{
    return GRAPHIC_LIB_NAMES;
}

/** Private **/

void CoreConfig::gotoMainMenu()
{
    if (this->_selectedGame == nullptr)
        return;
    this->_selectedGame = nullptr;
    // TODO : open main menu
}

void CoreConfig::rotateGraphLib(bool rev)
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
            std::cerr << "Warning: CoreConfig::rotateGraphLib() "
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

void CoreConfig::rotateGameLib(bool rev)
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
            std::cerr << "Warning: CoreConfig::rotateGameLib() "
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