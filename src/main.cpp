/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main function
*/

#include <iostream>
#include "Core/Core.hpp"
#include "./exception/BaseException.hpp"

int main(int argc, char **argv)
{
    if (argc == 2) {
        arcade::Core core(argv[1]);
        arcade::CoreConfig &config = core.getConfig();
        try {
            core.loop();
        } catch (BaseException const& e) {
            std::cerr << e.what() << std::endl;
            return EXIT_ERROR;
        }
        if (config.getStatus() == arcade::CoreConfig::ExitStatus::ERROR) {
            return EXIT_ERROR;
        }
    } else {
        std::cout << "USAGE: " << argv[0] << " {{Graphical/library/path}}"
                  << std::endl;
    }
    return EXIT_SUCCESS;
}
