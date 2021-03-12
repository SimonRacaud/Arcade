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
    class DLLoader {
    public:
        typedef T *(* entryPoint)(void);

        DLLoader(std::string const &filepath);

        virtual ~DLLoader(void);

        T &getInstance(void) const;
        std::string const& getName(void) const;

    private:
        void setName(std::string const& filepath);

        void *_lib;
        T *_instance;
        std::string _filepath;
        std::string _name;
        const std::string _entryPointName;
    };
}


#endif //DLLOADER_H
