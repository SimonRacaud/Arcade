/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SDL2
*/

#ifndef SDL2_HPP_
#define SDL2_HPP_

#include "../IDisplayModule.hpp"
#include <stdlib.h>
#include <map>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

using namespace arcade;

class SDL2 : public IDisplayModule {
    public:
        SDL2();
        ~SDL2();

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
        bool isMouseClicked() const; // Any key of the mouse
        Coord getMousePos() const;

    protected:
    private:
        float _scaleX;
        float _scaleY;
        size_t _textSize;
        TTF_Font *_font;
        static const std::map<Color, SDL_Color> _color;
        static const std::map<KeyList, SDL_Keycode> _key;
        SDL_Window *_window;
        SDL_Renderer *_renderer;
};

#endif /* !SDL2_HPP_ */
