/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Sound
*/

#include "Sound.hpp"

Arcade::Sound::Sound()
{
}

Arcade::Sound::Sound(const std::string &path, size_t volume) :
    path(path),
    volume(volume)
{
    if (volume > 100)
        this->volume = 100;
}

Arcade::Sound::~Sound()
{
}

const std::string &Arcade::Sound::getSound() const
{
    return (this->path);
}

size_t Arcade::Sound::getVolume() const
{
    return (this->volume);
}