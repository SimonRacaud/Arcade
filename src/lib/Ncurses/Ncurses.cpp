/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Ncurses
*/

#include "Ncurses.hpp"
#include <memory>

const std::map<arcade::IDisplayModule::Color, short> Ncurses::_caseColor = {
    {arcade::IDisplayModule::Color::BLACK, COLOR_BLACK},
    {arcade::IDisplayModule::Color::RED, COLOR_RED},
    {arcade::IDisplayModule::Color::GREEN, COLOR_GREEN},
    {arcade::IDisplayModule::Color::YELLOW, COLOR_YELLOW},
    {arcade::IDisplayModule::Color::BLUE, COLOR_BLUE},
    {arcade::IDisplayModule::Color::MAGENTA, COLOR_MAGENTA},
    {arcade::IDisplayModule::Color::CYAN, COLOR_CYAN},
    {arcade::IDisplayModule::Color::WHITE, COLOR_WHITE},
};

const std::map<arcade::IDisplayModule::Color, short> Ncurses::_textColor = {
    {arcade::IDisplayModule::Color::BLACK, 8},
    {arcade::IDisplayModule::Color::RED, 9},
    {arcade::IDisplayModule::Color::GREEN, 10},
    {arcade::IDisplayModule::Color::YELLOW, 11},
    {arcade::IDisplayModule::Color::BLUE, 12},
    {arcade::IDisplayModule::Color::MAGENTA, 13},
    {arcade::IDisplayModule::Color::CYAN, 14},
    {arcade::IDisplayModule::Color::WHITE, 15},
};

const std::map<arcade::IDisplayModule::KeyList, int> Ncurses::_key = {
    {arcade::IDisplayModule::KeyList::NEXT_GAME, 'z'},
    {arcade::IDisplayModule::KeyList::PREV_GAME, 'a'},
    {arcade::IDisplayModule::KeyList::NEXT_LIB, 'x'},
    {arcade::IDisplayModule::KeyList::PREV_LIB, 'w'},
    {arcade::IDisplayModule::KeyList::RESTART_GAME, 'r'},
    {arcade::IDisplayModule::KeyList::MENU, 'q'},
    {arcade::IDisplayModule::KeyList::EXIT, 27},
    {arcade::IDisplayModule::KeyList::PAUSE, 'p'},
    {arcade::IDisplayModule::KeyList::KEY_A, 'a'},
    {arcade::IDisplayModule::KeyList::KEY_B, 'b'},
    {arcade::IDisplayModule::KeyList::KEY_C, 'c'},
    {arcade::IDisplayModule::KeyList::KEY_D, 'd'},
    {arcade::IDisplayModule::KeyList::KEY_E, 'e'},
    {arcade::IDisplayModule::KeyList::KEY_F, 'f'},
    {arcade::IDisplayModule::KeyList::KEY_G, 'g'},
    {arcade::IDisplayModule::KeyList::KEY_H, 'h'},
    {arcade::IDisplayModule::KeyList::KEY_I, 'i'},
    {arcade::IDisplayModule::KeyList::KEY_J, 'j'},
    {arcade::IDisplayModule::KeyList::KEY_K, 'k'},
    {arcade::IDisplayModule::KeyList::KEY_L, 'l'},
    {arcade::IDisplayModule::KeyList::KEY_M, 'm'},
    {arcade::IDisplayModule::KeyList::KEY_N, 'n'},
    {arcade::IDisplayModule::KeyList::KEY_O, 'o'},
    {arcade::IDisplayModule::KeyList::KEY_P, 'p'},
    {arcade::IDisplayModule::KeyList::KEY_Q, 'q'},
    {arcade::IDisplayModule::KeyList::KEY_R, 'r'},
    {arcade::IDisplayModule::KeyList::KEY_S, 's'},
    {arcade::IDisplayModule::KeyList::KEY_T, 't'},
    {arcade::IDisplayModule::KeyList::KEY_U, 'u'},
    {arcade::IDisplayModule::KeyList::KEY_V, 'v'},
    {arcade::IDisplayModule::KeyList::KEY_W, 'w'},
    {arcade::IDisplayModule::KeyList::KEY_X, 'x'},
    {arcade::IDisplayModule::KeyList::KEY_Y, 'y'},
    {arcade::IDisplayModule::KeyList::KEY_Z, 'z'},
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

Ncurses::Ncurses()
    : _isOpen(false), _timer(80), _refresh(false), _window(nullptr), _ch(-1),
      _scale(2, 1), _textSize(1)
{
}

Ncurses::~Ncurses()
{
}

void Ncurses::open(Coord screenSize, Coord screenScale)
{
    short colorList[] = {COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW,
        COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE};

    (void) screenSize;
    (void) screenScale;
    _window = initscr();
    if (_window == NULL)
        std::cerr << "Ncurses : The initialization "
                  << "of the window failed !" << std::endl;
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
    _ch = -1;
    if (!_isOpen)
        return;
    if (endwin() == ERR)
        std::cerr << "Ncurses : The closing "
                  << "of the window failed !" << std::endl;
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
    if (pos.x * _scale.x + size.x * 2 >= windowX)
        line = line.substr(0, windowX - (pos.x * _scale.x));
    for (size_t i = 0; i < size.y; i++)
        mvprintw(pos.y * _scale.y + i, pos.x * _scale.x, line.data());
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
    if (pos.x * _scale.x + size.x * 2 >= windowX)
        line = line.substr(0, windowX - (pos.x));
    mvprintw(pos.y * _scale.y, pos.x * _scale.x, line.data());
    for (size_t i = 0; i < size.y; i++) {
        mvprintw(
            pos.y * _scale.y + i, pos.x * _scale.x, line.substr(0, 2).data());
        if (line.size() > size.x * 2 - 2)
            mvprintw(pos.y * _scale.y + i, pos.x * _scale.x + size.x * 2 - 2,
                line.substr(size.x * 2 - 2, 2).data());
    }
    mvprintw(pos.y * _scale.y + size.y - 1, pos.x * _scale.x, line.data());
    attroff(COLOR_PAIR(_caseColor.at(color)));
}

void Ncurses::putCircle(Color color, Coord pos, size_t radius)
{
    size_t difx = 0;
    size_t dify = 0;
    size_t windowX = 0;
    __attribute__((unused)) size_t windowY = 0;

    if (radius == 1) {
        this->putText(color, pos, "o");
        return;
    }
    getmaxyx(_window, windowY, windowX);
    attron(COLOR_PAIR(_caseColor.at(color)));
    for (size_t y = pos.y * _scale.y; y < pos.y * _scale.y + 2 * radius; y++) {
        for (size_t x = pos.x * _scale.x; x < pos.x * _scale.x + 2 * radius;
             x++) {
            difx = x - (pos.x * _scale.x) - radius;
            dify = y - (pos.y * _scale.y) - radius;
            if (sqrt((difx) * (difx) + (dify) * (dify)) > radius
                || sqrt((difx + 1) * (difx + 1) + (dify + 1) * (dify + 1))
                    > radius
                || sqrt((difx + 1) * (difx + 1) + (dify) * (dify)) > radius
                || sqrt((difx) * (difx) + (dify + 1) * (dify + 1)) > radius)
                continue;
            if (x + x - (pos.x * _scale.x) < windowX - 1)
                mvprintw(y, x + x - (pos.x * _scale.x), "  ");
            else if (x + x - (pos.x * _scale.x) < windowX)
                mvprintw(y, x + x - (pos.x * _scale.x), " ");
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
    if (pos.x * _scale.x + value.size() >= windowX)
        mvprintw(pos.y * _scale.y, pos.x * _scale.x,
            value.substr(0, windowX - (pos.x * _scale.x)).data());
    else
        mvprintw(pos.y * _scale.y, pos.x * _scale.x, value.data());
    attroff(COLOR_PAIR(_textColor.at(color)));
}

void Ncurses::displayScreen()
{
    if (_refresh) {
        _refresh = false;
        if (refresh() == ERR)
            std::cerr << "Ncurses : The refreshment "
                      << "of the window failed !" << std::endl;
    }
}

void Ncurses::refreshScreen()
{
    cbreak();
    if (cbreak() == ERR)
        std::cerr << "Ncurses : The unblocking "
                  << "of the getch failed !" << std::endl;
    _ch = wgetch(_window);
}

void Ncurses::clearScreen()
{
    if (_timer.shouldRefresh()) {
        _refresh = true;
        if (clear() == ERR)
            std::cerr << "Ncurses : The cleaning "
                      << "of the window failed !" << std::endl;
    }
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
        if (event.bstate & BUTTON1_CLICKED || event.bstate & BUTTON2_CLICKED) {
            return Coord(event.x, event.y);
        }
    }
    return Coord(0, 0);
}

extern "C" std::shared_ptr<arcade::IDisplayModule> entryPoint()
{
    return std::make_shared<Ncurses>();
}