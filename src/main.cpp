/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main function
*/

#include <iostream>
#include "Arcade/Arcade.hpp"
#include "./exception/BaseException.hpp"

int main(int argc, char **argv)
{
    arcade::Arcade core(argv[1]);

    if (argc == 2) {
        arcade::Arcade core(argv[1]);
        try {
            core.selectGame("./lib/arcade_nibbler.so"); // DEBUG TODO
            core.loop();
        } catch (BaseException const& e) {
            std::cerr << e.what() << std::endl;
            return EXIT_ERROR;
        }
        if (core.getStatus() == arcade::Arcade::ExitStatus::ERROR) {
            return EXIT_ERROR;
        }
    } else {
        std::cout << "USAGE: " << argv[0] << " {{Graphical/library/path}}"
                  << std::endl;
    }
    return EXIT_SUCCESS;
}
