/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** OutOfBoundException.hpp.h
*/

#ifndef OUTOFBOUNDEXCEPTION_HPP_
#define OUTOFBOUNDEXCEPTION_HPP_

#include "../BaseException.hpp"

class OutOfBoundException : public BaseException {
  public:
    OutOfBoundException(std::string const& message): BaseException(message) {}
    OutOfBoundException(): BaseException("Out of Bound Exception") {}

    virtual ~OutOfBoundException() = default;
};

#endif // OUTOFBOUNDEXCEPTION_HPP_
