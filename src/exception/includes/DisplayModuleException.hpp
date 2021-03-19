/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** DisplayModuleException.hpp
*/

#ifndef DISPLAYMODULEEXCEPTION_H_
#define DISPLAYMODULEEXCEPTION_H_

#include "ModuleException.hpp"

class DisplayModuleException : public ModuleException {
public:
    DisplayModuleException(std::string const& message): ModuleException(message) {}
    DisplayModuleException(): ModuleException("Display Module error") {}

    virtual ~DisplayModuleException() = default;
};

#endif //MODULEEXCEPTION_H_
