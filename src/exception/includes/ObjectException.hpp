/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** ObjectException.hpp.h
*/

#ifndef OBJECTEXCEPTION_HPP_
#define OBJECTEXCEPTION_HPP_

#include "../BaseException.hpp"

class ObjectException : public BaseException {
  public:
    ObjectException(std::string const& message): BaseException(message) {}
    ObjectException(): BaseException("Object Exception") {}

    virtual ~ObjectException() = default;
};

#endif // OBJECTEXCEPTION_HPP_
