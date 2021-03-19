/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Coord_t.hpp.h
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

class Vector {
  public:
    Vector(size_t ix, size_t iy) : x(ix), y(iy) {}
    Vector(Vector const& v) : x(v.x), y(v.y) {}
    ~Vector() = default;

    size_t x;
    size_t y;
};

#endif // VECTOR_HPP_
