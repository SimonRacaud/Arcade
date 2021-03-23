/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Vector.cpp.c
*/

#include "Vector.hpp"

Vector::Vector(ssize_t ix, ssize_t iy) : x(ix), y(iy)
{
}

Vector::Vector(Vector const &v) : x(v.x), y(v.y)
{
}

Vector Vector::operator+(Vector const &v)
{
    return Vector (this->y + v.y, this->x + v.x);
}

Vector Vector::operator-(Vector const &v)
{
    return Vector (this->y - v.y, this->x - v.x);
}