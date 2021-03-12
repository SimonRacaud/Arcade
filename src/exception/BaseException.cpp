/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** BaseException.cpp.c
*/

#include "BaseException.hpp"

BaseException::BaseException(std::string const &message)
: _message(message)
{
}

const char *BaseException::what() const noexcept
{
    return _message.c_str();
}