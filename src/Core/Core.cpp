/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Core.cpp
*/

#include "Core.hpp"

using namespace arcade;

Core::Core(const std::string &defGraphicFile)
    : _config(defGraphicFile), _mainMenu(_config)
{
}

Core::~Core()
{
}

void Core::loop()
{
    std::shared_ptr<IDisplayModule> selectedGraphic =
        _config.getSelectedGraphic();
    std::shared_ptr<IGameModule> selectedGame = _config.getSelectedGame();

    while (_config.getStatus() == CoreConfig::ExitStatus::LOOP) {
        selectedGraphic = _config.getSelectedGraphic();
        selectedGame = _config.getSelectedGame();
        if (selectedGraphic) {
            selectedGraphic->clearScreen();
            selectedGraphic->refreshScreen();
        }
        if (selectedGraphic->isOpen() == false) {
            this->_config.setStatus(CoreConfig::ExitStatus::SUCCESS);
            continue;
        }
        if (selectedGame == nullptr) {
            _mainMenu.refresh();
            this->_config.setUsername(_mainMenu.getUsername());
            selectedGraphic = _config.getSelectedGraphic();
        } else {
            selectedGame->setUsername(_mainMenu.getUsername());
            selectedGame->refresh();
        }
        if (selectedGraphic) {
            selectedGraphic->displayScreen();
            this->eventManager();
            selectedGraphic = _config.getSelectedGraphic();
            if (selectedGraphic->isOpen() == false) {
                this->_config.setStatus(CoreConfig::ExitStatus::SUCCESS);
            }
        }
    }
    if (selectedGraphic && selectedGraphic->isOpen()) {
        selectedGraphic->close();
    }
}

void Core::eventManager()
{
    std::shared_ptr<IDisplayModule> selectedGraphic =
        _config.getSelectedGraphic();
    std::shared_ptr<IGameModule> selectedGame = _config.getSelectedGame();

    if (selectedGraphic == nullptr)
        return;
    if (!_mainMenu.eventLocked()) {
        if (selectedGraphic->isKeyPress(Key::NEXT_GAME)) {
        _config.rotateGameLib(false);
        }
        if (selectedGraphic->isKeyPress(Key::PREV_GAME)) {
            _config.rotateGameLib(true);
        }
        if (selectedGraphic->isKeyPress(Key::NEXT_LIB)) {
            _config.rotateGraphLib(false);
        }
        if (selectedGraphic->isKeyPress(Key::PREV_LIB)) {
            _config.rotateGraphLib(true);
        }
        if (selectedGraphic->isKeyPress(Key::RESTART_GAME)) {
            _config.resetGame();
        }
        if (selectedGame && selectedGraphic->isKeyPress(Key::MENU)) {
            _config.gotoMainMenu();
        }
    }
    if (selectedGraphic->isKeyPress(Key::EXIT)) {
        _config.setStatus(CoreConfig::ExitStatus::SUCCESS);
    }
}

CoreConfig &Core::getConfig()
{
    return _config;
}