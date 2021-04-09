/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SFML
*/

#include <memory>
#include "./SFML.hpp"
#include "../../../includes/config.h"

using namespace arcade;

const std::map<arcade::IDisplayModule::Color, sf::Color> SFML::_color = {
    {arcade::IDisplayModule::Color::BLACK, sf::Color::Black},
    {arcade::IDisplayModule::Color::RED, sf::Color::Red},
    {arcade::IDisplayModule::Color::GREEN, sf::Color::Green},
    {arcade::IDisplayModule::Color::YELLOW, sf::Color::Yellow},
    {arcade::IDisplayModule::Color::BLUE, sf::Color::Blue},
    {arcade::IDisplayModule::Color::MAGENTA, sf::Color::Magenta},
    {arcade::IDisplayModule::Color::CYAN, sf::Color::Cyan},
    {arcade::IDisplayModule::Color::WHITE, sf::Color(255, 255, 255)},
    {arcade::IDisplayModule::Color::BLACK, sf::Color::Black},
};

const std::map<arcade::IDisplayModule::KeyList, sf::Keyboard::Key> SFML::_key =
    {
        {arcade::IDisplayModule::KeyList::NEXT_GAME, sf::Keyboard::Z},
        {arcade::IDisplayModule::KeyList::PREV_GAME, sf::Keyboard::A},
        {arcade::IDisplayModule::KeyList::NEXT_LIB, sf::Keyboard::X},
        {arcade::IDisplayModule::KeyList::PREV_LIB, sf::Keyboard::W},
        {arcade::IDisplayModule::KeyList::RESTART_GAME, sf::Keyboard::R},
        {arcade::IDisplayModule::KeyList::MENU, sf::Keyboard::Q},
        {arcade::IDisplayModule::KeyList::EXIT, sf::Keyboard::Escape},
        {arcade::IDisplayModule::KeyList::PAUSE, sf::Keyboard::P},
        {arcade::IDisplayModule::KeyList::KEY_A, sf::Keyboard::A},
        {arcade::IDisplayModule::KeyList::KEY_B, sf::Keyboard::B},
        {arcade::IDisplayModule::KeyList::KEY_C, sf::Keyboard::C},
        {arcade::IDisplayModule::KeyList::KEY_D, sf::Keyboard::D},
        {arcade::IDisplayModule::KeyList::KEY_E, sf::Keyboard::E},
        {arcade::IDisplayModule::KeyList::KEY_F, sf::Keyboard::F},
        {arcade::IDisplayModule::KeyList::KEY_G, sf::Keyboard::G},
        {arcade::IDisplayModule::KeyList::KEY_H, sf::Keyboard::H},
        {arcade::IDisplayModule::KeyList::KEY_I, sf::Keyboard::I},
        {arcade::IDisplayModule::KeyList::KEY_J, sf::Keyboard::J},
        {arcade::IDisplayModule::KeyList::KEY_K, sf::Keyboard::K},
        {arcade::IDisplayModule::KeyList::KEY_L, sf::Keyboard::L},
        {arcade::IDisplayModule::KeyList::KEY_M, sf::Keyboard::M},
        {arcade::IDisplayModule::KeyList::KEY_N, sf::Keyboard::N},
        {arcade::IDisplayModule::KeyList::KEY_O, sf::Keyboard::O},
        {arcade::IDisplayModule::KeyList::KEY_P, sf::Keyboard::P},
        {arcade::IDisplayModule::KeyList::KEY_Q, sf::Keyboard::Q},
        {arcade::IDisplayModule::KeyList::KEY_R, sf::Keyboard::R},
        {arcade::IDisplayModule::KeyList::KEY_S, sf::Keyboard::S},
        {arcade::IDisplayModule::KeyList::KEY_T, sf::Keyboard::T},
        {arcade::IDisplayModule::KeyList::KEY_U, sf::Keyboard::U},
        {arcade::IDisplayModule::KeyList::KEY_V, sf::Keyboard::V},
        {arcade::IDisplayModule::KeyList::KEY_W, sf::Keyboard::W},
        {arcade::IDisplayModule::KeyList::KEY_X, sf::Keyboard::X},
        {arcade::IDisplayModule::KeyList::KEY_Y, sf::Keyboard::Y},
        {arcade::IDisplayModule::KeyList::KEY_Z, sf::Keyboard::Z},
        {arcade::IDisplayModule::KeyList::KEY_1, sf::Keyboard::Num1},
        {arcade::IDisplayModule::KeyList::KEY_2, sf::Keyboard::Num2},
        {arcade::IDisplayModule::KeyList::KEY_3, sf::Keyboard::Num3},
        {arcade::IDisplayModule::KeyList::KEY_4, sf::Keyboard::Num4},
        {arcade::IDisplayModule::KeyList::KEY_5, sf::Keyboard::Num5},
        {arcade::IDisplayModule::KeyList::KEY_6, sf::Keyboard::Num6},
        {arcade::IDisplayModule::KeyList::KEY_7, sf::Keyboard::Num7},
        {arcade::IDisplayModule::KeyList::KEY_8, sf::Keyboard::Num8},
        {arcade::IDisplayModule::KeyList::KEY_9, sf::Keyboard::Num9},
        {arcade::IDisplayModule::KeyList::KEY_0, sf::Keyboard::Num0},
        {arcade::IDisplayModule::KeyList::ARROW_UP, sf::Keyboard::Up},
        {arcade::IDisplayModule::KeyList::ARROW_DOWN, sf::Keyboard::Down},
        {arcade::IDisplayModule::KeyList::ARROW_LEFT, sf::Keyboard::Left},
        {arcade::IDisplayModule::KeyList::ARROW_RIGHT, sf::Keyboard::Right},
        {arcade::IDisplayModule::KeyList::KEY_SPACE, sf::Keyboard::Space},
        {arcade::IDisplayModule::KeyList::BACK_SPACE, sf::Keyboard::BackSpace},
        {arcade::IDisplayModule::KeyList::KEY_MOUSE_CLICK, sf::Keyboard::Num0},
};

SFML::SFML() :
 _isMouseClicked(false), _isOpen(false),
 _scale(SCALE_X, SCALE_Y),
 _origin(ORIGIN_X * SCALE_X, ORIGIN_Y * SCALE_Y),
 _textSize(TEXT_SIZE)
{
}

SFML::~SFML()
{
}

void SFML::open(Coord screenSize, Coord screenScale)
{
    _scale.x = screenScale.x;
    _scale.y = screenScale.y;
    _font = new sf::Font;
    if (!_font->loadFromFile(FONT_PATH)) {
        // throw error ?
    }
    _isOpen = true;
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(screenSize.x, screenSize.y), WINDOW_NAME);
}

void SFML::close()
{
    _keyStack.clear();
    _isOpen = false;
    _window->close();
    _window.release();
    delete _font;
}

bool SFML::isOpen() const
{
    if (!_isOpen)
        return false;
    return _window->isOpen();
}

void SFML::putRectFill(Color color, arcade::Coord size, arcade::Coord pos)
{
    sf::RectangleShape rectangle;

    rectangle.setSize(
        sf::Vector2f(size.x * _scale.x, size.y * _scale.y));
    rectangle.setPosition(
        sf::Vector2f(_origin.x + pos.x * _scale.x, _origin.y + pos.y * _scale.y));
    rectangle.setFillColor(_color.at(color));
    _window->draw(rectangle);
}

void SFML::putRectOutline(Color color, Coord size, Coord pos)
{
    sf::RectangleShape rectangle;

    rectangle.setSize(
        sf::Vector2f(size.x * _scale.x, size.y * _scale.y));
    rectangle.setPosition(
        sf::Vector2f(_origin.x + pos.x * _scale.x, _origin.y + pos.y * _scale.y));
    rectangle.setOutlineColor(_color.at(color));
    rectangle.setOutlineThickness(_scale.x);
    rectangle.setFillColor(sf::Color(0, 0, 0, 0));
    _window->draw(rectangle);
}

void SFML::putCircle(Color color, Coord pos, size_t radius)
{
    sf::CircleShape circle;

    circle.setRadius((float)radius);
    circle.setPosition(
        sf::Vector2f(_origin.x + pos.x * _scale.x, _origin.y + pos.y * _scale.y));
    circle.setFillColor(_color.at(color));
    _window->draw(circle);
}

void SFML::putText(Color color, Coord pos, std::string const &value)
{
    sf::Text text;

    text.setFont(*_font);
    text.setString(value.c_str());
    text.setCharacterSize(_textSize);
    text.setFillColor(_color.at(color));
    text.setPosition(
        sf::Vector2f(_origin.x + pos.x * _scale.x, _origin.y + pos.y * _scale.y));
    _window->draw(text);
}

void SFML::displayScreen()
{
    _window->display();
}

void SFML::refreshScreen()
{
    this->_isMouseClicked = false;
    this->_keyStack.clear();
    this->refreshEvent();
}

void SFML::clearScreen()
{
    _window->clear(sf::Color::Black);
}

void SFML::refreshEvent()
{
    sf::Event event;

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _isOpen = false;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            _isMouseClicked = true;
        }
        if (event.type == sf::Event::KeyPressed) {
            _keyStack.push_back(event.key.code);
        }
    }
}

bool SFML::isKeyPress(const KeyList key) const
{
    if (key == KeyList::KEY_MOUSE_CLICK) {
        return _isMouseClicked;
    }
    for (sf::Keyboard::Key n : _keyStack) {
        if (_key.at(key) == n) {
            return true;
        }
    }
    return false;
}

bool SFML::isMouseClicked() const // Any key of the mouse
{
    return _isMouseClicked;
}

Coord SFML::getMousePos() const
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(*_window);

    return Coord(localPosition.x, localPosition.y);
}

extern "C" std::shared_ptr<arcade::IDisplayModule> entryPoint()
{
    return std::make_shared<SFML>();
}