/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Coord_t.hpp.h
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <cstddef>
#include <sys/types.h>

class Vector {
  public:
    Vector(ssize_t ix, ssize_t iy);
    Vector(Vector const &v);
    ~Vector() = default;

    Vector operator+(Vector const &v);
    Vector operator-(Vector const &v);

    ssize_t x;
    ssize_t y;
};

#endif // VECTOR_HPP_
