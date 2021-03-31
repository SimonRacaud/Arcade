/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Coord_t.hpp.h
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

namespace arcade
{
    class Vector {
      public:
        Vector(double ix, double iy);
        Vector(Vector const &v);
        ~Vector() = default;

        bool operator==(Vector const &v) const;
        bool operator!=(Vector const &v) const;

        Vector &operator=(Vector const &v);
        Vector operator+(Vector const &v);
        Vector operator-(Vector const &v);

        Vector &ceil();
        Vector &round();
        Vector &floor();

        double x;
        double y;
    };
} // namespace arcade

#endif // VECTOR_HPP_
