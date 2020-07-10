/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** CDir
*/

#include "CDir.hpp"

CDir::CDir() : _dir(nullptr), _ent(nullptr)
{
}

CDir::~CDir()
{
}

bool CDir::open(const std::string &directory)
{
    _dir = opendir(directory.c_str());
    return (_dir != nullptr);
}

void CDir::close()
{
    if (_dir)
        closedir(_dir);
}

bool CDir::getNextFileName(std::string &s)
{
    _ent = readdir(_dir);
    if (_ent) {
        s = std::string(_ent->d_name);
        return (true);
    } else {
        return (false);
    }
}