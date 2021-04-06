/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** DisplayModuleException.hpp
*/

#ifndef SCORE_EXCEPTION_H_
#define SCORE_EXCEPTION_H_

#include "ModuleException.hpp"

class ScoreException : public ModuleException {
public:
    ScoreException(std::string const& message): ModuleException(message) {}
    ScoreException(): ModuleException("Score error") {}

    virtual ~ScoreException() = default;
};

#endif //MODULEEXCEPTION_H_
