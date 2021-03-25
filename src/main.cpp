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
    if (argc == 2) {
        try {
            arcade::Arcade core(argv[1]);
            core.selectGame("./lib/arcade_nibbler.so"); // DEBUG TODO
            core.loop();
        } catch (BaseException const& e) {
            std::cerr << e.what() << std::endl;
            return EXIT_ERROR;
        }
        if (core.getStatus() == Arcade::ExitStatus::ERROR) {
            return EXIT_ERROR;
        }
    } else {
        std::cout << "USAGE: " << argv[0] << " {{Graphical/library/path}}"
                  << std::endl;
    }
    return EXIT_SUCCESS;
}
