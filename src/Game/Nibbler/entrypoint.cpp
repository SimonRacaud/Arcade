/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** entrypoint.c
*/

#include "./NibblerGameModule.hpp"
#include "IGameModule.hpp"

extern "C" arcade::IGameModule *entryPoint()
{
    return new Game::NibblerGameModule;
}