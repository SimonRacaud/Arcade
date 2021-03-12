/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** LibLoadingException.h
*/

#ifndef LIBLOADINGEXCEPTION_H_
#define LIBLOADINGEXCEPTION_H_

#include "exception/BaseException.hpp"

class LibLoadingException : public BaseException {
public:
    LibLoadingException(std::string const &message): BaseException(message) {}
    LibLoadingException(): BaseException("Fail to load the library") {}

    virtual ~LibLoadingException() = default;
};

#endif //LIBLOADINGEXCEPTION_H_
