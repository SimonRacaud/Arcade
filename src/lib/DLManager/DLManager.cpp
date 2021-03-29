/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** DlManager.cpp.cc
*/

#include "DLManager.hpp"

using namespace DL;

template <class T>
DLManager<T>::DLManager(
    std::string const &libsPath, std::string const &extension)
    : _libPath(libsPath), _extension(extension)
{
}

template <class T> DLManager<T>::~DLManager()
{
    this->cleanLoaders();
}

/*
 * LibLoadingException
 */
template <class T>
void DLManager<T>::fetchAvailableLibs(std::deque<std::string> const &libNames)
{
    this->_libFilePath.clear();
    this->cleanLoaders();
    this->fetchLibFiles(libNames);
}

template <class T>
std::deque<std::string> const &DLManager<T>::getAvailableLibs() const
{
    return _libFilePath;
}

/**
 * LibNotFoundException
 * LibLoadingException
 */
template <class T> T &DLManager<T>::getModule(std::string const &fileName)
{
    if (_libsLoader.find(fileName) == _libsLoader.end()) {
        this->generateLoader(fileName);
    }
    if (_libsLoader.find(fileName) != _libsLoader.end()) {
        return _libsLoader[fileName]->getInstance();
    } else {
        throw LibLoadingException("&DLManager<T>::getModule Loader not found");
    }
}

/* --- Private --- */

template <class T>
void DLManager<T>::fetchLibFiles(std::deque<std::string> const &libNames)
{
    DIR *dir = opendir(_libPath.c_str());
    struct dirent *fileInfo;
    std::string filename;
    std::string filePath;
    size_t pos;

    if (dir == nullptr) {
        throw LibLoadingException("Fail to load lib directory");
    }
    while ((fileInfo = readdir(dir)) != nullptr) {
        if (fileInfo->d_type != DT_REG)
            continue;
        filename = fileInfo->d_name;
        pos = filename.find_last_of('.');
        if (pos == std::string::npos
            || filename.compare(pos, _extension.size(), _extension))
            continue;
        filePath = this->mergeFilePath(_libPath, filename);
        if (std::find(libNames.begin(), libNames.end(), filename)
            != libNames.end()) {
            this->_libFilePath.push_back(filePath);
        }
    }
    closedir(dir);
}

/**
 * LibNotFoundException
 */
template <class T>
void DLManager<T>::generateLoader(std::string const &fileName)
{
    auto it = std::find_if(_libFilePath.begin(), _libFilePath.end(),
        [fileName](std::string const &path) {
            return path.find(fileName) != std::string::npos;
        });

    if (it != _libFilePath.end()) {
        if (_libsLoader.find(fileName) != _libsLoader.end()) {
            return;
        }
        _libsLoader[fileName] = new DLLoader<T>(*it);
    } else {
        throw LibNotFoundException(
            fileName + " is not a whitelisted library name or is not found");
    }
}

template <class T> void DLManager<T>::cleanLoaders()
{
    while (this->_libsLoader.empty() == false) {
        delete this->_libsLoader.begin()->second;
        this->_libsLoader.erase(_libsLoader.begin());
    }
}

template <class T>
std::string DLManager<T>::mergeFilePath(
    std::string const &path, std::string const &file)
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