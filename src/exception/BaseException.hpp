/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** AbstractException.h
*/

#ifndef BASEEXCEPTION_H_
#define BASEEXCEPTION_H_

#include <exception>
#include <string>

class BaseException: public std::exception {
public:
    BaseException(std::string const& message);
    virtual ~BaseException() = default;

    const char *what() const noexcept;
private:
    std::string _message;
};

#endif //ABSTRACTEXCEPTION_H_
