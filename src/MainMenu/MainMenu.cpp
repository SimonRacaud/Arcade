/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

using namespace arcade;

const std::vector<std::string> MainMenu::_menuTitle = {
    "          _____   _____          _____  ______  ",
    "    /\\   |  __ \\ / ____|   /\\   |  __ \\|  ____| ",
    "   /  \\  | |__) | |       /  \\  | |  | | |__    ",
    "  / /\\ \\ |  _  /| |      / /\\ \\ | |  | |  __|   ",
    " / ____ \\| | \\ \\| |____ / ____ \\| |__| | |____  ",
    "/_/    \\_\\_|  \\_\\\\_____/_/    \\_\\_____/|______|",
};

const std::vector<std::string> MainMenu::_title = {
    " /$$$$$$$$ /$$$$$$$  /$$$$$$ /$$$$$$$$ /$$$$$$$$ /$$   /$$ /$$$$$$$   /$$$$$$",
    "| $$_____/| $$__  $$|_  $$_/|__  $$__/| $$_____/| $$$ | $$| $$__  $$ /$$__  $$",
    "| $$      | $$  \\ $$  | $$     | $$   | $$      | $$$$| $$| $$  \\ $$| $$  \\ $$",
    "| $$$$$   | $$$$$$$/  | $$     | $$   | $$$$$   | $$ $$ $$| $$  | $$| $$  | $$",
    "| $$__/   | $$____/   | $$     | $$   | $$__/   | $$  $$$$| $$  | $$| $$  | $$",
    "| $$      | $$        | $$     | $$   | $$      | $$\\  $$$| $$  | $$| $$  | $$",
    "| $$$$$$$$| $$       /$$$$$$   | $$   | $$$$$$$$| $$ \\  $$| $$$$$$$/|  $$$$$$/",
    "|________/|__/      |______/   |__/   |________/|__/  \\__/|_______/  \\______/ "
};

const std::deque<std::string> MainMenu::CATEGORIE_NAMES = {
    "GAMES",
    "GRAPHICS",
    "SETTINGS",
    "HELP",
    "EXIT"
};

const std::deque<std::string> MainMenu::_helpText = {
    "MENU VALIDATION: SPACE",
    "MOVE UP: ARROW UP",
    "MOVE DOWN: ARROW DOWN",
    "MOVE RIGHT: ARROW RIGHT",
    "MOVE LEFT: ARROW LEFT",
    "PAUSE: P",
    "EXIT: ESCAPE",
    "GO TO MENU: Q",
    "RESTART GAME: R",
    "NEXT GAME: Z",
    "PREV GAME: W",
    "NEXT GRAPHIC: X",
    "PREV GRAPHIC: W"
};

const std::deque<std::string> MainMenu::_settings = {
    "USERNAME",
    "RELOAD LIBS"
};

MainMenu::MainMenu(CoreConfig &coreConfig) :
    _coreConfig(coreConfig),
    _textInput("USERNAME"),
    _gamesScores(coreConfig.getScores()),
    _selectedCategorie("HELP"),
    _selectedSetting("USERNAME"),
    _selectedPanel(0),
    _isLoading(true),
    _animationTimer(500),
    _pressStart(true),
    _eventLocked(false)
{
    const std::deque<std::string> &GameNames = _coreConfig.getGameNames();
    const std::deque<std::string> &GraphicNames = _coreConfig.getGraphicNames();

    if (GameNames.size() != 0 && GraphicNames.size() != 0) {
        _selectedGame = GameNames.at(0);
        _selectedGraphic = GraphicNames.at(0);
    }
}

MainMenu::~MainMenu() {}

std::string MainMenu::rotate(const std::deque<std::string> &listName, std::string selected, bool rev)
{
    auto it = std::find_if(listName.begin(), listName.end(),
        [selected](std::string const &name) {
            return name.find(selected) != std::string::npos;
    });

    if (rev) {
        if (it == listName.end() - 1) {
            selected = listName.front();
        } else {
            selected = *(it + 1);
        }
    } else {
        if (it == listName.begin()) {
            selected = listName.back();
        } else {
            selected = *(it - 1);
        }
    }
    return selected;
}

void MainMenu::movePanelEvent(IDisplayModule &selectedGraphic)
{
    size_t maxMove = 0;

    if (std::string("GAMES").find(_selectedCategorie) != std::string::npos) {
        maxMove = 1;
    }
    if (std::string("GRAPHICS").find(_selectedCategorie) != std::string::npos) {
        maxMove = 1;
    }
    if (std::string("SETTINGS").find(_selectedCategorie) != std::string::npos) {
        maxMove = 1;
    }
    if (selectedGraphic.isKeyPress(IDisplayModule::KeyList::ARROW_RIGHT)) {
        if (_selectedPanel != maxMove)
            _selectedPanel++;
    }
    if (selectedGraphic.isKeyPress(IDisplayModule::KeyList::ARROW_LEFT)) {
        if (_selectedPanel != 0)
            _selectedPanel--;
    }
}

void MainMenu::eventHandler()
{
    const std::deque<std::string> &GameNames = _coreConfig.getGameNames();
    const std::deque<std::string> &GraphicNames = _coreConfig.getGraphicNames();
    std::shared_ptr<IDisplayModule> selectedGraphic = _coreConfig.getSelectedGraphic();

    if (_selectedPanel == 0) {
        if (selectedGraphic->isKeyPress(IDisplayModule::KeyList::ARROW_UP))
            _selectedCategorie = rotate(CATEGORIE_NAMES, _selectedCategorie, false);
        if (selectedGraphic->isKeyPress(IDisplayModule::KeyList::ARROW_DOWN))
            _selectedCategorie = rotate(CATEGORIE_NAMES, _selectedCategorie, true);
        if (std::string("EXIT").find(_selectedCategorie) != std::string::npos) {
            if (selectedGraphic->isKeyPress(IDisplayModule::KeyList::KEY_SPACE)) {
                _coreConfig.setStatus(arcade::CoreConfig::ExitStatus::SUCCESS);
            }
        }
    }
    if (_selectedPanel == 1) {
        if (std::string("GAMES").find(_selectedCategorie) != std::string::npos) {
            if (selectedGraphic->isKeyPress(IDisplayModule::KeyList::KEY_SPACE)) {
                _coreConfig.selectGame("./lib/" + _selectedGame);
            }
            if (selectedGraphic->isKeyPress(IDisplayModule::KeyList::ARROW_UP))
                _selectedGame = rotate(GameNames, _selectedGame, false);
            if (selectedGraphic->isKeyPress(IDisplayModule::KeyList::ARROW_DOWN))
                _selectedGame = rotate(GameNames, _selectedGame, true);
        }
        if (std::string("GRAPHICS").find(_selectedCategorie) != std::string::npos) {
            if (selectedGraphic->isKeyPress(IDisplayModule::KeyList::KEY_SPACE)) {
                _coreConfig.selectGraphic("./lib/" + _selectedGraphic);
            }
            if (selectedGraphic->isKeyPress(IDisplayModule::KeyList::ARROW_UP))
                _selectedGraphic = rotate(GraphicNames, _selectedGraphic, false);
            if (selectedGraphic->isKeyPress(IDisplayModule::KeyList::ARROW_DOWN))
                _selectedGraphic = rotate(GraphicNames, _selectedGraphic, true);
        }
        if (std::string("SETTINGS").find(_selectedCategorie) != std::string::npos) {
            if (std::string(_settings.at(0)).find(_selectedSetting) != std::string::npos) {
                _textInput.refresh(*selectedGraphic.get());
                _eventLocked = true;
            }
            if (std::string(_settings.at(1)).find(_selectedSetting) != std::string::npos) {
                if (selectedGraphic->isKeyPress(IDisplayModule::KeyList::KEY_SPACE)) {
                    _coreConfig.reloadLib();
                    selectedGraphic = _coreConfig.getSelectedGraphic();
                }
            }
            if (selectedGraphic->isKeyPress(IDisplayModule::KeyList::ARROW_UP))
                _selectedSetting = rotate(_settings, _selectedSetting, false);
            if (selectedGraphic->isKeyPress(IDisplayModule::KeyList::ARROW_DOWN))
                _selectedSetting = rotate(_settings, _selectedSetting, true);
        }
    }
    movePanelEvent(*selectedGraphic);
}

void MainMenu::displayFirstPanel(IDisplayModule &selectedGraphic)
{
    for (auto i = CATEGORIE_NAMES.begin(); i != CATEGORIE_NAMES.end(); i++) {
        if ((*i).find(_selectedCategorie) != std::string::npos && _selectedPanel == 0) {
            selectedGraphic.putText(IDisplayModule::Color::RED, Coord(6, 14 + (i - CATEGORIE_NAMES.begin())), "> " + *i);
        } else {
            selectedGraphic.putText(IDisplayModule::Color::RED, Coord(6, 14 + (i - CATEGORIE_NAMES.begin())), *i);
        }
    }
}

void MainMenu::displaySecondPanel(IDisplayModule &selectedGraphic)
{
    const std::deque<std::string> &GameNames = _coreConfig.getGameNames();
    const std::deque<std::string> &GraphicNames = _coreConfig.getGraphicNames();

    if (std::string("GAMES").find(_selectedCategorie) != std::string::npos) {
        for (auto i = GameNames.begin(); i != GameNames.end(); i++) {
            if ((*i).find(_selectedGame) != std::string::npos && _selectedPanel == 1) {
                selectedGraphic.putText(IDisplayModule::Color::RED, Coord(18, 14 + (i - GameNames.begin())), "> " + *i);
            } else {
                selectedGraphic.putText(IDisplayModule::Color::RED, Coord(18, 14 + (i - GameNames.begin())), *i);
            }
        }
    }
    if (std::string("GRAPHICS").find(_selectedCategorie) != std::string::npos) {
        for (auto i = GraphicNames.begin(); i != GraphicNames.end(); i++) {
            if ((*i).find(_selectedGraphic) != std::string::npos && _selectedPanel == 1) {
                selectedGraphic.putText(IDisplayModule::Color::RED, Coord(18, 14 + (i - GraphicNames.begin())), "> " + *i);
            } else {
                selectedGraphic.putText(IDisplayModule::Color::RED, Coord(18, 14 + (i - GraphicNames.begin())), *i);
            }
        }
    }
    if (std::string("SETTINGS").find(_selectedCategorie) != std::string::npos) {
        for (auto i = _settings.begin(); i != _settings.end(); i++) {
            if ((*i).find(_selectedSetting) != std::string::npos && _selectedPanel == 1) {
                selectedGraphic.putText(IDisplayModule::Color::RED, Coord(18, 14 + (i - _settings.begin())), "> " + *i);
            } else {
                selectedGraphic.putText(IDisplayModule::Color::RED, Coord(18, 14 + (i - _settings.begin())), *i);
            }
        }
    }
    if (std::string("HELP").find(_selectedCategorie) != std::string::npos) {
        for (auto i = _helpText.begin(); i != _helpText.end(); i++) {
            selectedGraphic.putText(IDisplayModule::Color::RED, Coord(18, 14 + (i - _helpText.begin())), *i);
        }
    }
}

void MainMenu::displayThirdPanel(IDisplayModule &selectedGraphic)
{
    std::string highScore("0");
    std::string score("0");
    std::string username;

    for (auto it = _gamesScores.begin(); it != _gamesScores.end(); it++) {
        if ((*it)->name.find(_selectedGame) != std::string::npos) {
            highScore = std::to_string((*it)->highScore);
            score = std::to_string((*it)->score);
        }
    }
    if (std::string("GAMES").find(_selectedCategorie) != std::string::npos) {
        selectedGraphic.putText(IDisplayModule::Color::RED, Coord(32, 14), "SCORE: " + score);
        selectedGraphic.putText(IDisplayModule::Color::RED, Coord(32, 15), "HIGH SCORE: " + highScore);
        selectedGraphic.putText(IDisplayModule::Color::RED, Coord(32, 16), "USER: ");
    }
    if (std::string("SETTINGS").find(_selectedCategorie) != std::string::npos) {
        username = _textInput.getInputText();
        selectedGraphic.putText(IDisplayModule::Color::RED, Coord(32, 14), username + " (select to change)");
    }
}

void MainMenu::displayMenu(IDisplayModule &selectedGraphic)
{
    size_t i = 0;

    for (std::string line : _menuTitle) {
        selectedGraphic.putText(IDisplayModule::Color::MAGENTA, Coord(14, 4 + i), line);
        i++;
    }
    displayFirstPanel(selectedGraphic);
    displaySecondPanel(selectedGraphic);
    displayThirdPanel(selectedGraphic);
}

void MainMenu::displayLoading(IDisplayModule &selectedGraphic)
{
    const std::string startMsg("PRESS SPACE OR CLICK TO START");
    const std::string studio("Epietch Games");
    const std::string credits("Made by Simon Racaud, Aurelien Joncour and Thomas Jouanolle");
    size_t i = 0;

    for (std::string line : _title) {
        selectedGraphic.putText(IDisplayModule::Color::BLUE, Coord(7, 14 + i), line);
        i++;
    }
    if (_pressStart) {
        selectedGraphic.putText(IDisplayModule::Color::WHITE, Coord(18, 19 + i), startMsg);
    }
    selectedGraphic.putText(IDisplayModule::Color::WHITE, Coord(4, 45), studio);
    selectedGraphic.putText(IDisplayModule::Color::WHITE, Coord(19, 45), credits);
    if (selectedGraphic.isKeyPress(IDisplayModule::KeyList::KEY_SPACE)) {
        _isLoading = false;
    }
    if (selectedGraphic.isMouseClicked()) {
        _isLoading = false;
    }
}

std::string MainMenu::getUsername() const
{
    return _textInput.getInputText();
}

bool MainMenu::eventLocked() const
{
    return _eventLocked;
}

void MainMenu::refresh()
{
    std::shared_ptr<IDisplayModule> selectedGraphic = _coreConfig.getSelectedGraphic();
    std::string categoriesName;

    _eventLocked = false;
    _gamesScores = _coreConfig.getScores();
    if (_animationTimer.shouldRefresh()) {
        _pressStart = !_pressStart;
    }
    if (!selectedGraphic)
        return;
    if (_isLoading) {
        displayLoading(*selectedGraphic);
    } else {
        displayMenu(*selectedGraphic);
        eventHandler();
    }
}
