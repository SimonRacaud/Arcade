/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** DlManager.hpp.h
*/

#ifndef DLMANAGER_HPP_
#define DLMANAGER_HPP_

#include "lib/DLLoader/DLLoader.hpp"
#include "LibLoadingException.hpp"
#include "LibNotFoundException.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "utility.hpp"

#include <string>
#include <unordered_map>
#include <deque>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <memory>

namespace DL {
    template <class T>
    class DLManager {
    public:
        DLManager(std::string const& libsPath, std::string const &extension = ".so");
        virtual ~DLManager();

        void loadLibs(void);

        std::unordered_map<std::string, T *> &getLibs(void) const;

        std::deque<std::string> const& getAvailableLibs(void) const;
        T &getModule(std::string const& filePath);

    private:
        void fetchLibFiles(void);
        void generateLoaders(void);
        void cleanLoaders(void);

        std::string mergeFilePath(std::string const& path, std::string const& file);

        const std::string _libPath;
        const std::string _extension;
        std::unordered_map<std::string, DLLoader<T> *> _libsLoader;
        std::deque<std::string> _libFilePath;
    };
}

#endif //DLMANAGER_HPP_
