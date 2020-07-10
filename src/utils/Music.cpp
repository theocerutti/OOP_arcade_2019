/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Music
*/

#include "Music.hpp"

Arcade::Music::Music()
{
}

Arcade::Music::Music(const std::string &path, size_t volume, bool isLooping) :
    path(path),
    volume(volume),
    looping(isLooping)
{
    if (volume > 100)
        this->volume = 100;
}

Arcade::Music::~Music()
{
}

const std::string &Arcade::Music::getMusic() const
{
    return (this->path);
}

size_t Arcade::Music::getVolume() const
{
    return (this->volume);
}

bool Arcade::Music::isLooping() const
{
    return (this->looping);
}