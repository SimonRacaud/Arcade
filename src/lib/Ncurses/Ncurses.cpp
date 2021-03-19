/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

const std::map <arcade::IDisplayModule::Color, short> Ncurses::_caseColor = {
    {arcade::IDisplayModule::Color::BLACK, 0},
    {arcade::IDisplayModule::Color::RED, 1},
    {arcade::IDisplayModule::Color::GREEN, 2},
    {arcade::IDisplayModule::Color::YELLOW, 3},
    {arcade::IDisplayModule::Color::BLUE, 4},
    {arcade::IDisplayModule::Color::MAGENTA, 5},
    {arcade::IDisplayModule::Color::CYAN, 6},
    {arcade::IDisplayModule::Color::WHITE, 7},
};

const std::map <arcade::IDisplayModule::Color, short> Ncurses::_textColor = {
    {arcade::IDisplayModule::Color::BLACK, 8},
    {arcade::IDisplayModule::Color::RED, 9},
    {arcade::IDisplayModule::Color::GREEN, 10},
    {arcade::IDisplayModule::Color::YELLOW, 11},
    {arcade::IDisplayModule::Color::BLUE, 12},
    {arcade::IDisplayModule::Color::MAGENTA, 13},
    {arcade::IDisplayModule::Color::CYAN, 14},
    {arcade::IDisplayModule::Color::WHITE, 15},
};

const std::map <arcade::IDisplayModule::KeyList, int> Ncurses::_key = {
    //{arcade::IDisplayModule::KeyList::NEXT_GAME, sf::Keyboard::Num0},
    //{arcade::IDisplayModule::KeyList::PREV_GAME, sf::Keyboard::Num0},
    //{arcade::IDisplayModule::KeyList::NEXT_LIB, sf::Keyboard::Num0},
    //{arcade::IDisplayModule::KeyList::PREV_LIB, sf::Keyboard::Num0},
    //{arcade::IDisplayModule::KeyList::RESTART_GAME, sf::Keyboard::Num0},
    //{arcade::IDisplayModule::KeyList::MENU, sf::Keyboard::Num0},
    //{arcade::IDisplayModule::KeyList::EXIT, sf::Keyboard::Num0},
    {arcade::IDisplayModule::KeyList::KEY_Z, 'z'},
    {arcade::IDisplayModule::KeyList::KEY_Q, 'q'},
    {arcade::IDisplayModule::KeyList::KEY_S, 's'},
    {arcade::IDisplayModule::KeyList::KEY_D, 'd'},
    {arcade::IDisplayModule::KeyList::ARROW_UP, KEY_UP},
    {arcade::IDisplayModule::KeyList::ARROW_DOWN, KEY_DOWN},
    {arcade::IDisplayModule::KeyList::ARROW_LEFT, KEY_LEFT},
    {arcade::IDisplayModule::KeyList::ARROW_RIGHT,KEY_RIGHT},
    {arcade::IDisplayModule::KeyList::KEY_SPACE, ' '},
    {arcade::IDisplayModule::KeyList::KEY_MOUSE_CLICK, KEY_MOUSE},
};

Ncurses::Ncurses() :
 _scaleX(1), _scaleY(1),
 _textSize(1)
{
    _isOpen = false;
    _window = nullptr;
    _ch = -1;
}

Ncurses::~Ncurses() {}

void Ncurses::open()
{
    short colorList[] = {COLOR_BLACK, COLOR_RED, COLOR_GREEN,
    COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE};

    _window = initscr();
    if (_window == NULL)
        throw DisplayModuleException("The initialization of the window failed !");
    timeout(1);
    _isOpen = true;
    keypad(_window, true);
    mousemask(ALL_MOUSE_EVENTS, nullptr);
    noecho();
    curs_set(0);
    start_color();
    for (size_t i = 0; i < 8; i++) {
        init_pair(i, colorList[i], colorList[i]);
        init_pair(i + 8, colorList[i], colorList[0]);
    }
}

void Ncurses::close()
{
    if (endwin() == ERR)
        throw DisplayModuleException("The closing of the window failed !");
    _isOpen = false;
}

bool Ncurses::isOpen() const
{
    return _isOpen;
}

void Ncurses::putRectFill(Color color, arcade::Coord size, arcade::Coord pos)
{
    std::string line = "";
    size_t windowX = 0;
    __attribute__((unused)) size_t windowY = 0;

    getmaxyx(_window, windowY, windowX);
    attron(COLOR_PAIR(_caseColor.at(color)));
    for (size_t i = 0; i < size.first; i++)
        line += "  ";
    if (pos.first + size.first * 2 >= windowX)
        line = line.substr(0, windowX - pos.first);
    for (size_t i = 0; i < size.second; i++)
        mvprintw(pos.second + i, pos.first, line.data());
    attroff(COLOR_PAIR(_caseColor.at(color)));
}

void Ncurses::putRectOutline(Color color, Coord size, Coord pos)
{
    std::string line = "";
    size_t windowX = 0;
    __attribute__((unused)) size_t windowY = 0;

    getmaxyx(_window, windowY, windowX);
    attron(COLOR_PAIR(_caseColor.at(color)));
    for (size_t i = 0; i < size.first; i++)
        line += "  ";
    if (pos.first + size.first * 2 >= windowX)
        line = line.substr(0, windowX - pos.first);
    mvprintw(pos.second, pos.first, line.data());
    for (size_t i = 0; i < size.second; i++) {
        mvprintw(pos.second + i, pos.first, line.substr(0, 2).data());
        if (line.size() > size.first * 2 - 2)
            mvprintw(pos.second + i, pos.first + size.first * 2 - 2,
            line.substr(size.first * 2 - 2, 2).data());
    }
    mvprintw(pos.second + size.second - 1, pos.first, line.data());
    attroff(COLOR_PAIR(_caseColor.at(color)));
}

void Ncurses::putCircle(Color color, Coord pos, size_t radius)
{
    size_t difx = 0;
    size_t dify = 0;
    size_t windowX = 0;
    __attribute__((unused)) size_t windowY = 0;

    getmaxyx(_window, windowY, windowX);
    attron(COLOR_PAIR(_caseColor.at(color)));
    for (size_t y = pos.second; y < pos.second + 2 * radius; y++) {
        for (size_t x = pos.first; x < pos.first + 2 * radius; x++) {
            difx = x - pos.first - radius;
            dify = y - pos.second - radius;
            if (sqrt((difx) * (difx) + (dify) * (dify)) > radius
            || sqrt((difx + 1) * (difx + 1) + (dify + 1) * (dify + 1)) > radius
            || sqrt((difx + 1) * (difx + 1) + (dify) * (dify)) > radius
            || sqrt((difx) * (difx) + (dify + 1) * (dify + 1)) > radius)
                continue;
            if (x + x - pos.first < windowX - 1)
                mvprintw(y, x + x - pos.first, "  ");
            else if (x + x - pos.first < windowX)
                mvprintw(y, x + x - pos.first, " ");
        }
    }
    attroff(COLOR_PAIR(_caseColor.at(color)));
}

void Ncurses::putText(Color color, Coord pos, std::string const &value)
{
    std::string string = "";
    size_t windowX = 0;
    __attribute__((unused)) size_t windowY = 0;

    getmaxyx(_window, windowY, windowX);
    attron(COLOR_PAIR(_textColor.at(color)));
    if (pos.first + value.size() >= windowX)
        mvprintw(pos.second, pos.first, value.substr(0, windowX - pos.first).data());
    else
        mvprintw(pos.second, pos.first, value.data());
    attroff(COLOR_PAIR(_textColor.at(color)));
}

void Ncurses::displayScreen() {}

void Ncurses::refreshScreen()
{
    if (refresh() == ERR)
        throw DisplayModuleException("The refreshment of the window failed !");
    cbreak();
    if (cbreak() == ERR)
        throw DisplayModuleException("The unblocking of the getch failed !");
    _ch = wgetch(_window);
}

void Ncurses::clearScreen()
{
    if (clear() == ERR)
        throw DisplayModuleException("The cleaning of the window failed !");
}

bool Ncurses::isKeyPress(const KeyList key) const
{
    if (key == KeyList::KEY_MOUSE_CLICK)
        return false;
    if (_ch == _key.at(key))
        return true;
    return false;
}

bool Ncurses::isMouseClicked() const
{
    if (_ch == KEY_MOUSE)
        return true;
    return false;
}

Coord Ncurses::getMousePos() const
{
    MEVENT event;

    if (_ch == KEY_MOUSE && getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_CLICKED
        || event.bstate & BUTTON2_CLICKED) {
            return Coord(event.x, event.y);
        }
    }
    return Coord(0, 0);
}

extern "C" arcade::IDisplayModule *entryPoint()
{
    return new Ncurses;
}