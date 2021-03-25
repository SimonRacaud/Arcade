/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** SDL2
*/

#include <iostream>
#include <vector>
#include "./SDL2.hpp"
#include "../../../includes/config.h"
#include "../../../includes/Vector.hpp"

const std::map<arcade::IDisplayModule::Color, SDL_Color> SDL2::_color = {
    {arcade::IDisplayModule::Color::BLACK, {0, 0, 0, 255}},
    {arcade::IDisplayModule::Color::RED, {255, 0, 0, 255}},
    {arcade::IDisplayModule::Color::GREEN, {0, 255, 0, 255}},
    {arcade::IDisplayModule::Color::YELLOW, {255, 255, 0, 255}},
    {arcade::IDisplayModule::Color::BLUE, {0, 0, 255, 255}},
    {arcade::IDisplayModule::Color::MAGENTA, {255, 0, 255, 255}},
    {arcade::IDisplayModule::Color::CYAN, {0, 255, 255, 255}},
    {arcade::IDisplayModule::Color::WHITE, {255, 255, 255, 255}},
};

const std::map<arcade::IDisplayModule::KeyList, SDL_Keycode> SDL2::_key = {
    {arcade::IDisplayModule::KeyList::NEXT_GAME, SDLK_UNKNOWN},
    {arcade::IDisplayModule::KeyList::PREV_GAME, SDLK_UNKNOWN},
    {arcade::IDisplayModule::KeyList::NEXT_LIB, SDLK_UNKNOWN},
    {arcade::IDisplayModule::KeyList::PREV_LIB, SDLK_UNKNOWN},
    {arcade::IDisplayModule::KeyList::RESTART_GAME, SDLK_UNKNOWN},
    {arcade::IDisplayModule::KeyList::MENU, SDLK_UNKNOWN},
    {arcade::IDisplayModule::KeyList::EXIT, SDLK_UNKNOWN},
    {arcade::IDisplayModule::KeyList::PAUSE, SDLK_UNKNOWN},
    {arcade::IDisplayModule::KeyList::KEY_Z, SDLK_z},
    {arcade::IDisplayModule::KeyList::KEY_Q, SDLK_q},
    {arcade::IDisplayModule::KeyList::KEY_S, SDLK_s},
    {arcade::IDisplayModule::KeyList::KEY_D, SDLK_d},
    {arcade::IDisplayModule::KeyList::ARROW_UP, SDLK_UP},
    {arcade::IDisplayModule::KeyList::ARROW_DOWN, SDLK_DOWN},
    {arcade::IDisplayModule::KeyList::ARROW_LEFT, SDLK_LEFT},
    {arcade::IDisplayModule::KeyList::ARROW_RIGHT, SDLK_RIGHT},
    {arcade::IDisplayModule::KeyList::KEY_SPACE, SDLK_SPACE},
    {arcade::IDisplayModule::KeyList::KEY_MOUSE_CLICK, SDLK_UNKNOWN},
};

SDL2::SDL2() :
    _isMouseClicked(false), _isOpen(false),
    _scaleX(SCALE_X), _scaleY(SCALE_Y),
    _textSize(TEXT_SIZE),
    _window(NULL), _renderer(NULL)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    _font = TTF_OpenFont(FONT_PATH, _textSize);
    if (_font == NULL) {
        std::cout << "font is null" << std::endl;
        //throw error
    }
}

SDL2::~SDL2()
{
    if (_font) {
        TTF_CloseFont(_font);
    }
    SDL_Quit();
    TTF_Quit();
}

void SDL2::open()
{
    _window = SDL_CreateWindow(
        WINDOW_NAME,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        W_WIDTH,
        W_HEIGH,
        SDL_WINDOW_OPENGL
    );
    if (_window == NULL) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        //THROW ERROR
    }
    _isOpen = true;
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

void SDL2::close()
{
    _isOpen = false;
    SDL_DestroyWindow(_window);
}

bool SDL2::isOpen() const
{
    return _isOpen;
}

void SDL2::putRectFill(Color color, arcade::Coord size, arcade::Coord pos)
{
    SDL_Color sdl_color = _color.at(color);
    SDL_Rect r;

    r.x = pos.first * _scaleX;
    r.y = pos.second * _scaleY;
    r.w = size.first * _scaleX;
    r.h = size.second * _scaleY;

    SDL_SetRenderDrawColor(_renderer, sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a);
    SDL_RenderFillRect(_renderer, &r);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

void SDL2::putRectOutline(Color color, Coord size, Coord pos)
{
    SDL_Color sdl_color = _color.at(color);
    SDL_Rect r;

    r.x = pos.first * _scaleX;
    r.y = pos.second * _scaleY;
    r.w = size.first * _scaleX;
    r.h = size.second * _scaleY;
    SDL_SetRenderDrawColor(_renderer, sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a);
    SDL_RenderDrawRect(_renderer, &r);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

void SDL2::putCircle(Color color, Coord pos, size_t radius)
{
    SDL_Color sdl_color = _color.at(color);
    float position_x = pos.first * SCALE_X;
    float position_y = pos.second * SCALE_Y;
    Vector center( position_x + radius, position_y + radius);
    std::vector<float> v = {0, 0};

    SDL_SetRenderDrawColor(_renderer, sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a);
    for (size_t x = 0; x < radius * 2; x++) {
        for (size_t y = 0; y < radius * 2; y++) {
            v[0] = position_x + x - center.x;
            v[1] = position_y + y - center.y;
            if ((pow(v[0], 2) + pow(v[1], 2)) <= pow(radius, 2)) {
                SDL_RenderDrawPoint(_renderer, position_x + x, position_y + y);
            }
        }
    }
}

void SDL2::putText(Color color, Coord pos, std::string const &value)
{
    SDL_Surface *surface = TTF_RenderText_Solid(_font, value.c_str(), _color.at(color));
    SDL_Texture *message = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_Rect rect = {0, 0, 0, 0};

    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = pos.first * SCALE_X;
    rect.y = pos.second * SCALE_Y;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(_renderer, message, NULL, &rect);
}

void SDL2::displayScreen()
{
    SDL_RenderPresent(_renderer);
}

void SDL2::refreshScreen()
{
    this->_isMouseClicked = false;
    this->_keyStack.clear();
    this->refreshEvent();
}

void SDL2::clearScreen()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void SDL2::refreshEvent()
{
    SDL_Event event = {0};

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            _isOpen = false;
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            _isMouseClicked = true;
        }
        if (event.type == SDL_KEYDOWN) {
            _keyStack.push_back(event.key.keysym.sym);
        }
    }
}

bool SDL2::isKeyPress(const KeyList key) const
{
    if (key == KeyList::KEY_MOUSE_CLICK) {
        return _isMouseClicked;
    }
    for (SDL_Keycode n : _keyStack) {
        if (_key.at(key) == n) {
            return true;
        }
    }
    return false;
}

bool SDL2::isMouseClicked() const // Any key of the mouse
{
    return _isMouseClicked;
}

Coord SDL2::getMousePos() const
{
    int x = 0;
    int y = 0;

    SDL_GetMouseState(&x, &y);
    return Coord(x, y);
}

extern "C" arcade::IDisplayModule *entryPoint()
{
    return new SDL2;
}