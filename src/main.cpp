/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main function
*/

#include <iostream>
#include "./exception/BaseException.hpp"
#include "Core/Core.hpp"

int main(int argc, char **argv)
{
    if (argc != 2 || std::string(argv[1]) == "-h") {
        std::cout << "USAGE:\n\t" << argv[0]
                  << " lib/[graphical-library-path].so" << std::endl;
    } else {
        arcade::Core core(argv[1]);
        arcade::CoreConfig &config = core.getConfig();
        try {
            core.loop();
        } catch (BaseException const &e) {
            std::cerr << e.what() << std::endl;
            return EXIT_ERROR;
        }
        if (config.getStatus() == arcade::CoreConfig::ExitStatus::ERROR) {
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}
