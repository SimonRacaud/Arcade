/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** DLLoader.h
*/

#ifndef DLLOADER_H
#define DLLOADER_H

#include <string>
#include <dlfcn.h>

#include "LibLoadingException.hpp"


namespace DL
{
    template<typename T>
    class Loader {
    public:
        Loader(std::string const &filepath);

        virtual ~Loader(void);

        T &getInstance(void);

    private:
        std::string getFilename(std::string const& filepath);

        void *_lib;
        T *_instance;
        std::string _filepath;
    };
}


#endif //DLLOADER_H
