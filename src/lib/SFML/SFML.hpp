/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "../../../includes/IDisplayModule.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace arcade
{
    class SFML : public IDisplayModule {
      public:
        ~SFML();
        SFML();

        void open(Coord screenSize, Coord screenScale);
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
        void refreshEvent();
        std::vector<sf::Keyboard::Key> _keyStack;
        bool _isMouseClicked;
        bool _isOpen;
        Vector _scale;
        size_t _textSize;
        sf::Font *_font;
        static const std::map<Color, sf::Color> _color;
        static const std::map<KeyList, sf::Keyboard::Key> _key;
        std::unique_ptr<sf::RenderWindow> _window;
    };
}

#endif /* !SFML_HPP_ */
