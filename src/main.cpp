/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main function
*/

#include <iostream>
#include "Arcade/Arcade.hpp"

int main(int argc, char **argv)
{
    if (argc == 2) {
        try {
            arcade::Arcade core(argv[1]);
            core.loop();
        } catch (...) {
            return 84;
        }
    } else {
        std::cout << "USAGE: " << argv[0] << " {{Graphical/library/path}}"
                  << std::endl;
    }
    return EXIT_SUCCESS;
}
