/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** DlManager.cpp.cc
*/

#include "DLManager.hpp"

using namespace DL;

template <class T>
DLManager<T>::DLManager(std::string const& libsPath, std::string const& extension)
    : _libPath(libsPath), _extension(extension)
{
    this->loadLibs();
}

template <class T>
DLManager<T>::~DLManager()
{
    this->cleanLoaders();
}

template <class T>
void DLManager<T>::loadLibs()
{
    this->fetchLibFiles();
    this->generateLoaders();
}

template <class T>
std::unordered_map<std::string, T *> &DLManager<T>::getLibs(void) const
{
    auto result = new std::unordered_map<std::string, T *>;

    for (auto const loader : _libsLoader) {
        std::cerr << "HELLO\n";
        (*result)[loader.first] = &loader.second->getInstance();
    }
    return *result;
}

template <class T>
void DLManager<T>::fetchLibFiles(void)
{
    DIR *dir = opendir(_libPath.c_str());
    struct dirent *fileInfo;
    std::string filename;
    size_t pos;

    if (dir == nullptr) {
        throw LibLoadingException("Fail to load lib directory");
    }
    this->_libFileNames.clear();
    while ((fileInfo = readdir(dir)) != nullptr) {
        if (fileInfo->d_type != DT_REG)
            continue;
        filename = fileInfo->d_name;
        pos = filename.find_last_of('.');
        if (pos == filename.size() || filename.compare(pos, _extension.size(), _extension))
            continue;
        this->_libFileNames.push_back(filename);
    }
    closedir(dir);
}

// throw LibLoadException
template <class T>
void DLManager<T>::generateLoaders()
{
    this->cleanLoaders();
    for (std::string const& filename : _libFileNames) {
        _libsLoader[filename] = new DLLoader<T>(_libPath + filename);
    }
}

template <class T>
void DLManager<T>::cleanLoaders()
{
    while (this->_libsLoader.empty() == false) {
        delete this->_libsLoader.begin()->second;
        this->_libsLoader.erase(_libsLoader.begin());
    }
}

template class DLManager<arcade::IDisplayModule>;
template class DLManager<arcade::IGameModule>;