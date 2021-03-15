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
}

template <class T>
DLManager<T>::~DLManager()
{
    this->cleanLoaders();
}

template <class T>
void DLManager<T>::loadLibs(std::deque<std::string> const& libNames)
{
    this->fetchLibFiles();
    this->generateLoaders(libNames);
}

template <class T>
std::unordered_map<std::string, T *> &DLManager<T>::getLibs(void) const
{
    auto result = new std::unordered_map<std::string, T *>;

    for (auto const loader : _libsLoader) {
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
    this->_libFilePath.clear();
    while ((fileInfo = readdir(dir)) != nullptr) {
        if (fileInfo->d_type != DT_REG)
            continue;
        filename = fileInfo->d_name;
        pos = filename.find_last_of('.');
        if (pos == filename.size() || filename.compare(pos, _extension.size(), _extension))
            continue;
        this->_libFilePath.push_back(this->mergeFilePath(_libPath, filename));
    }
    closedir(dir);
}

// throw LibLoadException
template <class T>
void DLManager<T>::generateLoaders(std::deque<std::string> const& libNames)
{
    std::string filepath;

    this->cleanLoaders();
    for (std::string const& filepath : _libFilePath) {
        if (std::find_if(
                libNames.begin(),
                libNames.end(),
                [filepath](std::string const& f) { return filepath.find(f) != filepath.size(); }
                ) == libNames.end()) {
            continue;
        }
        _libsLoader[filepath] = new DLLoader<T>(filepath);
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

template <class T>
std::deque<std::string> const& DLManager<T>::getAvailableLibs() const
{
    return _libFilePath;
}

template <class T>
T &DLManager<T>::getModule(std::string const& filepath)
{
    if (_libsLoader.find(filepath) == _libsLoader.end()) {
        throw LibNotFoundException(filepath + " : library not found");
    }
    return _libsLoader[filepath]->getInstance();
}

template <class T>
std::string DLManager<T>::mergeFilePath(std::string const& path, std::string const& file)
{
    std::string result = path;

    trim(result);
    if (result.size() > 0 && result.back() != '/') {
        result += '/';
    }
    result += file;
    return result;
}

template class DLManager<arcade::IDisplayModule>;
template class DLManager<arcade::IGameModule>;