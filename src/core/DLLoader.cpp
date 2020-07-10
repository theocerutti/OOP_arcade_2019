/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoader
*/

#include "DLLoader.hpp"

#ifndef DLLOADER_CPP_
#define DLLOADER_CPP_

template <class T>
DLLoader<T>::DLLoader(const std::string &libPath, const std::string &name)
    : _handler(nullptr),
     _lib(nullptr),
     _name(name)
{
    T *(*entryPoint)(void) = nullptr;

    checkLibraryValidity(libPath);
    _handler = dlopen(libPath.c_str(),  RTLD_LAZY | RTLD_GLOBAL);
    if (!_handler)
        throw CoreError(std::string(dlerror()) + " (dlerror)");
    *(void **)(&entryPoint) = dlsym(_handler, "entryPoint");
    if (!entryPoint)
        throw CoreError(libPath + ": doesn't contain entryPoint!");
    _lib = entryPoint();
    if (_lib == nullptr)
        throw CoreError(libPath + ": entryPoint doesn't return anything!");
}

template <class T>
DLLoader<T>::~DLLoader()
{
}

template <class T>
void DLLoader<T>::close() const
{
    dlclose(_handler);
}

template <class T>
T *DLLoader<T>::getInstance() const
{
    return (_lib);
}

template <class T>
const std::string &DLLoader<T>::getName() const
{
    return (_name);
}

template <class T>
void DLLoader<T>::checkLibraryValidity(const std::string &libPath) const
{
    std::smatch matchs;
    std::regex isLib("lib_arcade_([\\w]+)\\.so$");
    std::ifstream libFile(libPath);
    std::string first_line = "";

    if (!libFile.is_open())
        throw CoreError("DLLoader: " + libPath + " not found.");
    std::getline(libFile, first_line);
    if (!strcmp(first_line.c_str(), ELFMAG))
        throw CoreError("DLLoader: " + libPath + " is not an ELF file.");
    libFile.close();
    std::regex_search(libPath, matchs, isLib);
    if (matchs.str(1) == "")
        throw CoreError("DLLoader: " + libPath + " is not a valid library name.");
}

#endif