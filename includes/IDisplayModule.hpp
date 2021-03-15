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

    typedef void (IGameModule::*key_evt)(int code);
    typedef void (IGameModule::*mouse_evt)(Coord const &pos);

    class IDisplayModule {
      public:
        typedef enum class Color_s {
            RED,
            BLUE,
            GREEN,
            BLACK,
            YELLOW,
            BROWN,
            GRAY,
            WHITE,
            ORANGE,
            PURPLE
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
            KEY_MOUSE_LEFT,
            KEY_MOUSE_RIGHT
        } KeyList;

        virtual ~IDisplayModule(){};

        virtual void open();
        virtual void close();
        virtual void putRect(Color color, Coord size, Coord pos) = 0;
        virtual void putCircle(Color color, Coord pos, size_t radius) = 0;
        virtual void putLine(Color color, Coord startPos, Coord endPos) = 0;
        virtual void putText(Color color, Coord pos, std::string const &value) = 0;
        virtual void putMatrix(Color color, std::string *mtx);

        virtual void displayScreen() = 0;
        virtual void refreshScreen() = 0;
        virtual void clearScreen() = 0;

        virtual bool isKeyPress(const KeyList key) const = 0;
        virtual bool isKeyRelease(const KeyList key) const = 0;
        virtual Coord getMousePos() const = 0;

        virtual void eventClicked(mouse_evt func) = 0;
        virtual void eventKeyPressed(key_evt func) = 0;
        virtual void eventKeyReleased(key_evt func) = 0;
    };
} // namespace arcade

#endif /* !IDISPLAYMODULE_HPP_ */
