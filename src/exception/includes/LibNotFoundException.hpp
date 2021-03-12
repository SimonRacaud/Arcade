/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** LibNotFoundException.h
*/

#ifndef LIBNOTFOUNDEXCEPTION_H_
#define LIBNOTFOUNDEXCEPTION_H_

#include "LibLoadingException.hpp"

class LibNotFoundException : public LibLoadingException {
public:
    LibNotFoundException(std::string const &message): LibLoadingException(message) {}
    LibNotFoundException(): LibLoadingException("Lib not found") {}

    virtual ~LibNotFoundException() = default;
};

#endif //LIBNOTFOUNDEXCEPTION_H_
