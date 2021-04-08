/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** extractFilename.cpp.c
*/

#include "utility.hpp"

std::string extractFilename(std::string const &filepath)
{
    size_t idx = 0;

    idx = filepath.find_last_of('/');
    if (idx != std::string::npos) {
        return filepath.substr(idx + 1);
    }
    return filepath;
}