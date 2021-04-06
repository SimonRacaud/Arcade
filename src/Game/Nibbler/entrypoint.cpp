/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** entrypoint.c
*/

#include <memory>
#include "./NibblerGameModule.hpp"
#include "IGameModule.hpp"

extern "C" std::shared_ptr<arcade::IGameModule> entryPoint()
{
    return std::make_shared<Game::NibblerGameModule>();
}