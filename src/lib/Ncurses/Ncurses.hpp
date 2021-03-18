/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "../../../includes/IDisplayModule.hpp"
#include <curses.h>
#include <map>
#include <iostream>
#include <math.h>

using namespace arcade;

class Ncurses : public IDisplayModule {
    public:
        ~Ncurses();
        Ncurses();

        void open();
        void close();
        bool isOpen() const;

        void putRectFill(Color color, Coord size, Coord pos);
        void putRectOutline(Color color, Coord size, Coord pos);
        void putCircle(Color color, Coord pos, size_t radius);
        void putText(Color color, Coord pos, std::string const &value);

        void displayScreen();
        void refreshScreen();
        void clearScreen();

        bool isKeyPress(const KeyList key) const;
        bool isMouseClicked() const;
        Coord getMousePos() const;

    protected:
    private:
        float _scaleX;
        float _scaleY;
        size_t _textSize;
        bool _isOpen;
        static const std::map<Color, short> _caseColor;
        static const std::map<Color, short> _textColor;
        static const std::map<KeyList, int> _key;
        WINDOW *_window;
        int _ch;
};

#endif /* !NCURSES_HPP_ */
