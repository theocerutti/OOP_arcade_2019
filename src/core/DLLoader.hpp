/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <iostream>
#include <memory>
#include <dlfcn.h>
#include <fstream>
#include <regex>
#include <elf.h>
#include "../games/AGame.hpp"
#include "../graphicals/ILibGFX.hpp"

template <typename T>
class DLLoader {
    public:
        DLLoader(const std::string &libPath, const std::string &name);
        ~DLLoader();
        void close() const;
        void checkLibraryValidity(const std::string &libPath) const;
        const std::string &getName() const;
        T *getInstance() const;
    private:
        void *_handler;
        T *_lib;
        std::string _name;
};

#include "DLLoader.cpp"

#endif /* !DLLoader_HPP_ */