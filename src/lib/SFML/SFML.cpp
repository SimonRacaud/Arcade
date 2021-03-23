/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SFML
*/

#include "../../../includes/lib/SFML.hpp"

const std::map <arcade::IDisplayModule::Color, sf::Color> SFML::_color = {
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

const std::map <arcade::IDisplayModule::KeyList, sf::Keyboard::Key> SFML::_key = {
    //{arcade::IDisplayModule::KeyList::NEXT_GAME, sf::Keyboard::Num0},
    //{arcade::IDisplayModule::KeyList::PREV_GAME, sf::Keyboard::Num0},
    //{arcade::IDisplayModule::KeyList::NEXT_LIB, sf::Keyboard::Num0},
    //{arcade::IDisplayModule::KeyList::PREV_LIB, sf::Keyboard::Num0},
    //{arcade::IDisplayModule::KeyList::RESTART_GAME, sf::Keyboard::Num0},
    //{arcade::IDisplayModule::KeyList::MENU, sf::Keyboard::Num0},
    //{arcade::IDisplayModule::KeyList::EXIT, sf::Keyboard::Num0},
    {arcade::IDisplayModule::KeyList::KEY_Z, sf::Keyboard::Z},
    {arcade::IDisplayModule::KeyList::KEY_Q, sf::Keyboard::Q},
    {arcade::IDisplayModule::KeyList::KEY_S, sf::Keyboard::S},
    {arcade::IDisplayModule::KeyList::KEY_D, sf::Keyboard::D},
    {arcade::IDisplayModule::KeyList::ARROW_UP, sf::Keyboard::Up},
    {arcade::IDisplayModule::KeyList::ARROW_DOWN, sf::Keyboard::Down},
    {arcade::IDisplayModule::KeyList::ARROW_LEFT, sf::Keyboard::Left},
    {arcade::IDisplayModule::KeyList::ARROW_RIGHT, sf::Keyboard::Right},
    {arcade::IDisplayModule::KeyList::KEY_SPACE, sf::Keyboard::Space},
    {arcade::IDisplayModule::KeyList::KEY_MOUSE_CLICK, sf::Keyboard::Num0},
};

SFML::SFML() :
 _scaleX(40), _scaleY(40),
 _textSize(40)
{
    if (!_font.loadFromFile("assets/arial.ttf")) {
        //throw error ?
    }
}

SFML::~SFML() {}

void SFML::open()
{
    _window = new sf::RenderWindow(sf::VideoMode(800, 600), "My window");
}

void SFML::close()
{
    _window->close();
}


bool SFML::isOpen() const
{
    sf::Event event;

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            return false;
        }
    }
    return _window->isOpen();
}

void SFML::putRectFill(Color color, arcade::Coord size, arcade::Coord pos)
{
    sf::RectangleShape rectangle;

    rectangle.setSize(sf::Vector2f((float)size.first * _scaleX, (float)size.second * _scaleY));
    rectangle.setPosition(sf::Vector2f((float)pos.first * _scaleX, (float)pos.second * _scaleY));
    rectangle.setFillColor(_color.at(color));
    _window->draw(rectangle);
}

void SFML::putRectOutline(Color color, Coord size, Coord pos)
{
    sf::RectangleShape rectangle;

    rectangle.setSize(sf::Vector2f((float)size.first * _scaleX, (float)size.second * _scaleY));
    rectangle.setPosition(sf::Vector2f((float)pos.first * _scaleX, (float)pos.second * _scaleY));
    rectangle.setOutlineColor(_color.at(color));
    rectangle.setOutlineThickness(_scaleX);
    rectangle.setFillColor(sf::Color(0, 0, 0, 0));
    _window->draw(rectangle);
}

void SFML::putCircle(Color color, Coord pos, size_t radius)
{
    sf::CircleShape circle;

    circle.setRadius((float)radius);
    circle.setPosition(sf::Vector2f((float)pos.first, (float)pos.second));
    circle.setFillColor(_color.at(color));
    _window->draw(circle);
}

void SFML::putText(Color color, Coord pos, std::string const &value)
{
    sf::Text text;

    text.setFont(_font);
    text.setString(value.c_str());
    text.setCharacterSize(_textSize);
    text.setFillColor(_color.at(color));
    text.setPosition(sf::Vector2f((float)pos.first, (float)pos.second));
    _window->draw(text);
}

void SFML::displayScreen()
{
    _window->display();
}

void SFML::refreshScreen()
{
}

void SFML::clearScreen()
{
    _window->clear(sf::Color::Black);
}

bool SFML::isKeyPress(const KeyList key) const
{
    if (key == KeyList::KEY_MOUSE_CLICK) {
        return false;
    }
    return sf::Keyboard::isKeyPressed(_key.at(key));
}

bool SFML::isMouseClicked() const // Any key of the mouse
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
        sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
    } {
        return true;
    }
    return false;
}

Coord SFML::getMousePos() const
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(*_window);

    return Coord(localPosition.x, localPosition.y);
}

extern "C" arcade::IDisplayModule *entryPoint()
{
    return new SFML;
}