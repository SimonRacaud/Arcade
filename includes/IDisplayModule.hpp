/*
** EPITECH PROJECT, 2021
** OOP_arcade_Interface
** File description:
** IDisplayModule
*/

#ifndef IDISPLAY_MODULE_HPP_
#define IDISPLAY_MODULE_HPP_

#include <utility>
#include <string>
#include <stddef.h>

#include "IGameModule.hpp"

namespace arcade
{
    class IGameModule;

    typedef std::pair<size_t, size_t> Coord;

    class IDisplayModule {
      public:
        typedef enum class Color_s {
            BLACK,
            RED,
            GREEN,
            YELLOW,
            BLUE,
            MAGENTA,
            CYAN,
            WHITE
        } Color;

        typedef enum class EKeyList {
            // GUI
            NEXT_GAME,
            PREV_GAME,
            NEXT_LIB,
            PREV_LIB,
            RESTART_GAME,
            MENU,
            EXIT,
            // Keys
            KEY_Z,
            KEY_Q,
            KEY_S,
            KEY_D,
            ARROW_UP,
            ARROW_DOWN,
            ARROW_LEFT,
            ARROW_RIGHT,
            KEY_SPACE,
            KEY_MOUSE_CLICK
        } KeyList;

        virtual ~IDisplayModule() = default;

        virtual void open() = 0;
        virtual void close() = 0;

        virtual void putRectFill(Color color, Coord size, Coord pos) = 0;
        virtual void putRectOutline(Color color, Coord size, Coord pos) = 0;
        virtual void putCircle(Color color, Coord pos, size_t radius) = 0;
        virtual void putText(Color color, Coord pos, std::string const &value) = 0;

        virtual void displayScreen() = 0;
        virtual void refreshScreen() = 0;
        virtual void clearScreen() = 0;

        virtual bool isKeyPress(const KeyList key) const = 0;
        virtual bool isMouseClicked() const = 0; // Any key of the mouse
        virtual Coord getMousePos() const = 0;
    };
} // namespace arcade

#endif /* !IDISPLAYMODULE_HPP_ */
