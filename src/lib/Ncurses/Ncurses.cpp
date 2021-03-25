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
    {arcade::IDisplayModule::KeyList::NEXT_GAME, 'z'},
    {arcade::IDisplayModule::KeyList::PREV_GAME, 'a'},
    {arcade::IDisplayModule::KeyList::NEXT_LIB, 'x'},
    {arcade::IDisplayModule::KeyList::PREV_LIB, 'w'},
    {arcade::IDisplayModule::KeyList::RESTART_GAME, 'r'},
    {arcade::IDisplayModule::KeyList::MENU, 'q'},
    {arcade::IDisplayModule::KeyList::EXIT, 27},
    {arcade::IDisplayModule::KeyList::PAUSE, 'p'},
    {arcade::IDisplayModule::KeyList::KEY_A, 'A'},
    {arcade::IDisplayModule::KeyList::KEY_B, 'B'},
    {arcade::IDisplayModule::KeyList::KEY_C, 'C'},
    {arcade::IDisplayModule::KeyList::KEY_D, 'D'},
    {arcade::IDisplayModule::KeyList::KEY_E, 'E'},
    {arcade::IDisplayModule::KeyList::KEY_F, 'F'},
    {arcade::IDisplayModule::KeyList::KEY_G, 'G'},
    {arcade::IDisplayModule::KeyList::KEY_H, 'H'},
    {arcade::IDisplayModule::KeyList::KEY_I, 'I'},
    {arcade::IDisplayModule::KeyList::KEY_J, 'J'},
    {arcade::IDisplayModule::KeyList::KEY_K, 'K'},
    {arcade::IDisplayModule::KeyList::KEY_L, 'L'},
    {arcade::IDisplayModule::KeyList::KEY_M, 'M'},
    {arcade::IDisplayModule::KeyList::KEY_N, 'N'},
    {arcade::IDisplayModule::KeyList::KEY_O, 'O'},
    {arcade::IDisplayModule::KeyList::KEY_P, 'P'},
    {arcade::IDisplayModule::KeyList::KEY_Q, 'Q'},
    {arcade::IDisplayModule::KeyList::KEY_R, 'R'},
    {arcade::IDisplayModule::KeyList::KEY_S, 'S'},
    {arcade::IDisplayModule::KeyList::KEY_T, 'T'},
    {arcade::IDisplayModule::KeyList::KEY_U, 'U'},
    {arcade::IDisplayModule::KeyList::KEY_V, 'V'},
    {arcade::IDisplayModule::KeyList::KEY_W, 'W'},
    {arcade::IDisplayModule::KeyList::KEY_X, 'X'},
    {arcade::IDisplayModule::KeyList::KEY_Y, 'Y'},
    {arcade::IDisplayModule::KeyList::KEY_Z, 'Z'},
    {arcade::IDisplayModule::KeyList::KEY_1, '1'},
    {arcade::IDisplayModule::KeyList::KEY_2, '2'},
    {arcade::IDisplayModule::KeyList::KEY_3, '3'},
    {arcade::IDisplayModule::KeyList::KEY_4, '4'},
    {arcade::IDisplayModule::KeyList::KEY_5, '5'},
    {arcade::IDisplayModule::KeyList::KEY_6, '6'},
    {arcade::IDisplayModule::KeyList::KEY_7, '7'},
    {arcade::IDisplayModule::KeyList::KEY_8, '8'},
    {arcade::IDisplayModule::KeyList::KEY_9, '9'},
    {arcade::IDisplayModule::KeyList::KEY_0, '0'},
    {arcade::IDisplayModule::KeyList::ARROW_UP, KEY_UP},
    {arcade::IDisplayModule::KeyList::ARROW_DOWN, KEY_DOWN},
    {arcade::IDisplayModule::KeyList::ARROW_LEFT, KEY_LEFT},
    {arcade::IDisplayModule::KeyList::ARROW_RIGHT, KEY_RIGHT},
    {arcade::IDisplayModule::KeyList::KEY_SPACE, ' '},
    {arcade::IDisplayModule::KeyList::BACK_SPACE, KEY_BACKSPACE},
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
    for (size_t i = 0; i < size.x; i++)
        line += "  ";
    if (pos.x + size.x * 2 >= windowX)
        line = line.substr(0, windowX - pos.x);
    for (size_t i = 0; i < size.y; i++)
        mvprintw(pos.y + i, pos.x, line.data());
    attroff(COLOR_PAIR(_caseColor.at(color)));
}

void Ncurses::putRectOutline(Color color, Coord size, Coord pos)
{
    std::string line = "";
    size_t windowX = 0;
    __attribute__((unused)) size_t windowY = 0;

    getmaxyx(_window, windowY, windowX);
    attron(COLOR_PAIR(_caseColor.at(color)));
    for (size_t i = 0; i < size.x; i++)
        line += "  ";
    if (pos.x + size.x * 2 >= windowX)
        line = line.substr(0, windowX - pos.x);
    mvprintw(pos.y, pos.x, line.data());
    for (size_t i = 0; i < size.y; i++) {
        mvprintw(pos.y + i, pos.x, line.substr(0, 2).data());
        if (line.size() > size.x * 2 - 2)
            mvprintw(pos.y + i, pos.x + size.x * 2 - 2,
            line.substr(size.x * 2 - 2, 2).data());
    }
    mvprintw(pos.y + size.y - 1, pos.x, line.data());
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
    for (size_t y = pos.y; y < pos.y + 2 * radius; y++) {
        for (size_t x = pos.x; x < pos.x + 2 * radius; x++) {
            difx = x - pos.x - radius;
            dify = y - pos.y - radius;
            if (sqrt((difx) * (difx) + (dify) * (dify)) > radius
            || sqrt((difx + 1) * (difx + 1) + (dify + 1) * (dify + 1)) > radius
            || sqrt((difx + 1) * (difx + 1) + (dify) * (dify)) > radius
            || sqrt((difx) * (difx) + (dify + 1) * (dify + 1)) > radius)
                continue;
            if (x + x - pos.x < windowX - 1)
                mvprintw(y, x + x - pos.x, "  ");
            else if (x + x - pos.x < windowX)
                mvprintw(y, x + x - pos.x, " ");
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
    if (pos.x + value.size() >= windowX)
        mvprintw(pos.y, pos.x, value.substr(0, windowX - pos.x).data());
    else
        mvprintw(pos.y, pos.x, value.data());
    attroff(COLOR_PAIR(_textColor.at(color)));
}

void Ncurses::displayScreen()
{
    if (refresh() == ERR)
        throw DisplayModuleException("The refreshment of the window failed !");
}

void Ncurses::refreshScreen()
{
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