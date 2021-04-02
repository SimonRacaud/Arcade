/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** ShootException.hpp.h
*/

#ifndef SHOOT_EXCEPTION_HPP
#define SHOOT_EXCEPTION_HPP

#include "../BaseException.hpp"

class ShootException : public BaseException {
  public:
    ShootException(std::string const& message): BaseException(message) {}
    ShootException(): BaseException("Shoot Exception") {}

    virtual ~ShootException() = default;
};

#endif // SHOOT_EXCEPTION_HPP
