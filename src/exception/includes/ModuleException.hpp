/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** ModuleException.h
*/

#ifndef MODULEEXCEPTION_H_
#define MODULEEXCEPTION_H_

#include "exception/BaseException.hpp"

class ModuleException : public BaseException {
public:
    ModuleException(std::string const& message): BaseException(message) {}
    ModuleException(): BaseException("Module error") {}

    virtual ~ModuleException() = default;
};

#endif //MODULEEXCEPTION_H_
