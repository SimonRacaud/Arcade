/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** DLLoader.cpp.cc
*/

#include "DLLoader.hpp"

template <typename T>
DL::DLLoader<T>::DLLoader(std::string const &filepath)
: _lib(nullptr), _instance(nullptr), _filepath(filepath), _entryPointName("entryPoint")
{
    this->_lib = dlopen(filepath.c_str(), RTLD_LAZY);
    if (this->_lib == nullptr) {
        throw LibLoadingException("Fail to load the lib: "+filepath);
    }
    this->setName(filepath);
}

template <typename T>
DL::DLLoader<T>::~DLLoader(void)
{
    if (_instance != nullptr)
        delete _instance;
    if (this->_lib != nullptr) {
        dlclose(this->_lib);
    }
}

template <typename T>
void DL::DLLoader<T>::setName(const std::string &filepath)
{
    const size_t posPath = filepath.find_last_of('/');
    const size_t posExt = filepath.find_last_of('.');
    std::string result = filepath;

    if (posExt != filepath.size()) {
        result = filepath.substr(0, posExt);
    }
    if (posPath != filepath.size()) {
        result = result.substr(posPath);
    }
    this->_name = result;
}

template <typename T>
T &DL::DLLoader<T>::getInstance(void)
{
    if (_instance == nullptr) {
        this->fetchInstance();
    }
    return *_instance;
}

template <typename T>
void DL::DLLoader<T>::fetchInstance(void)
{
    DLLoader::entryPoint func;
    T *res;

    func = (DLLoader::entryPoint)dlsym(this->_lib, this->_entryPointName.c_str());
    if (func == nullptr) {
        throw LibLoadingException("Lib entry point not found");
    }
    res = (*func)();
    if (res == nullptr) {
        throw LibLoadingException("Fail to get lib module");
    }
    this->_instance = res;
}


template <typename T>
std::string const &DL::DLLoader<T>::getName(void) const
{
    return this->_name;
}

template class DL::DLLoader<arcade::IDisplayModule>;
template class DL::DLLoader<arcade::IGameModule>;